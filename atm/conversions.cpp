
#include "conversions.h"

atm::statemap 
atm::accepting_states( const regexp::defmap& defs, simple& smp )
{
   statemap acc;
   for( const auto& d : defs ) 
      acc. insert( { d. first, smp. create_state( ) } );
   return acc; 
}

atm::state
atm::add2simple( const builder& bld, simple& smp )
{
   state entry = smp. create_state( );
   smp. delta_epsilon. insert( { smp. empty_set, entry } );

   for( const auto& trans : bld. delta_set )
   {
      smp. delta_set. insert( 
         { { entry + trans. from, trans. element }, entry + trans. to } );
   }

   for( const auto& eps : bld. delta_eps )
   {
      smp. delta_epsilon. insert( { entry + eps. from, entry + eps. to } );
   }

   // We know that bld. nrstates > 0.

   auto acc = entry + bld. nrstates;

   for( size_t i = 0; i != bld. nrstates; ++ i )
      smp. create_state( );

   return acc;
}


atm::convresult
atm::conv2single( simple& smp, const convresult& res )
{
   switch( res. sel( ))
   {
   case atm_single:
      return res;

   case atm_tuple:
      return convresult( atm_single, res. view_tuple( ). q( ));

   case atm_set:
      {
         state acc = add2simple( res. view_set( ). bld( ), smp );
         return convresult( atm_single, acc );
      }
   }

   std::cout << "conv2single " << res << "\n";
   throw std::logic_error( "falling through" );

   return convresult( atm_error, 
              std::string( "didn't know how to convert " ) + 
                 getcstring( res. sel( )) + " to single" ); 
}


atm::state
atm::state_of( const convresult& res )
{
   switch( res. sel( ))
   {
   case atm_single:
      return res. view_single( ). q( );
   case atm_tuple:
      return res. view_tuple( ). q( );
   }
   std::cout << res << "\n\n";
   throw std::logic_error( "cannot find state" ); 
}

atm::convresult 
atm::convert( simple& smp, const regexp::expr& e,
              const regexp::defmap& defs, const identifier::map< state > & acc )
{

   std::cout << "converting: " << e << "\n";

   switch( e. sel( ))
   {
   case regexp::ref_ident:
      {
         auto p = acc. find( e. view_reference( ). ident( ));
         if( p != acc. end( ))
            return convresult( atm_single, p -> second );
         else
            throw std::logic_error( "unknown identifier" );
      }

   case regexp::flt_char:
      {
         state q = smp. create_state( );
         auto trans = stateswitch( q, smp. trap );
         smp. delta_char. push_back( e. view_filter_char( ). func( ).
                                     transform_range( trans ));
         return { atm_single, q };
      }

   case regexp::flt_sel:
      {
         state q = smp. create_state( ); 
         auto trans = stateswitch( q, smp. trap ); 
         smp. delta_sel. push_back( e. view_filter_sel( ). func( ).
                                    transform_range( trans ));  
         return { atm_single, q };
      }

   case regexp::flt_u64:
      {
         state q = smp. create_state( );
         auto trans = stateswitch( q, smp. trap ); 
         smp. delta_u64. push_back( e. view_filter_u64( ). func( ). 
                                    transform_range( trans ));
         return { atm_single, q };
      }

   case regexp::tup_exact:
   case regexp::tup_prefix:
      {
         auto tup = e. view_tuple( ); 
         std::vector< convresult > sub;
         for( size_t i = 0; i != tup. size( ); ++ i )
         {
            sub. push_back( 
               conv2single( smp, convert( smp, tup. sub(i), defs, acc )));
         }

         for( const auto& s : sub )
         {
            if( s. sel( ) == atm_error )
               return s; 
         }
        
         auto q = smp. empty_tuple;
         for( const auto& s : sub )
         {
            auto q1 = smp. create_state( );
            smp. delta_tuple. insert( { { q, s. view_single( ). q( ) }, q1 } );
            q = q1; 
         }
         
         if( e. sel( ) == regexp::tup_prefix )
            throw std::logic_error( "we need to add a cycle" );

         return convresult( atm_tuple, q, sub. size( )); 
      }

   case regexp::log_or:
      {
         auto disj = e. view_disjunction( ); 

         std::vector< convresult > subresults;
         for( size_t i = 0; i != disj. size( ); ++ i )
            subresults. push_back( convert( smp, disj. sub(i), defs, acc ));

         std::cout << "disjunction:\n";
         for( const auto& s : subresults )
            std::cout << "   " << s << "\n"; 

         // If some of the subresults are a set, we convert them into a
         // single:

         for( auto& sub : subresults )
         {
            if( sub. sel( ) == atm_set )
               sub = conv2single( smp, sub );

            if( sub. sel( ) == atm_error )
               return sub; 
         }

         auto acc = smp. create_state( );
         for( auto& s : subresults )
            smp. delta_epsilon. insert( { state_of(s), acc } ); 

         bool allaretuples = true; 
         size_t shortest = std::numeric_limits< size_t > :: max( ); 
         for( auto& sub : subresults )
         {
            if( sub. sel( ) == atm_tuple ) 
            {
               if( sub. view_tuple( ). sz( ) < shortest )
                  shortest = sub. view_tuple( ). sz( ); 
            }
            else
               allaretuples = false;
         }
         std::cout << "allaretuples = " << allaretuples << "\n";
         std::cout << "shortest = " << shortest << "\n";
         std::cout << "state = " << acc << "\n";
         if( allaretuples && subresults. size( ) != 0 )
            return convresult( atm_tuple, acc, shortest );
         else
            return convresult( atm_single, acc );
      }

   case regexp::set_word:
      {
         auto wrd = e. view_word( );
         std::vector< state > sub;  
         for( size_t i = 0; i != wrd. size( ); ++ i )
         {
            auto res = convert( smp, wrd. smp(i), defs, acc );
            res = conv2single( smp, res );
            if( res. sel( ) == atm_error )
               return res;

            sub. push_back( state_of( res )); 
         }

         std::cout << "Word:\n";
         for( const auto& w : sub )
            std::cout << "   " << w << "\n";

         return convresult( atm_set, oneword( sub )); 
      }

   case regexp::set_linear:
   case regexp::set_circular:
      {
         auto mult = e. view_multiply( );
         auto set = convert( smp, mult. set( ), defs, acc );   
         std::cout << "this is set: " << set << "\n"; 
         if( set. sel( ) != atm_set )
         { 
            return convresult( atm_error, 
                      "first argument of linear/circular is not a set" ); 
         }

         std::vector< state > disj; 
         for( size_t i = 0; i != mult. size( ); ++ i )
         {
            auto sub = convert( smp, mult. disj(i), defs, acc );
            sub = conv2single( smp, sub );
            if( sub. sel( ) == atm_error )
               return sub;

            disj. push_back( state_of( sub ));
         }
         std::cout << "This is the transformation disjunction:\n";
         for( const auto& d : disj )
            std::cout << "   " << d << "\n";

         auto bld = set. view_set( ). extr_bld( );
         if( e. sel( ) == regexp::set_linear )
            bld. addlinear( disj, mult. factor( ));

         if( e. sel( ) == regexp::set_circular )
            bld. addcircular( disj, mult. factor( ));

         return convresult( atm_set, std::move( bld ));
      }
   }

   std::cout << "trying to convert: " << e. sel( ) << "\n";
   throw std::logic_error( "not implemented" ); 
}


void 
atm::convert( simple& smp, resultmap& results,
              const regexp::defmap& defs, const statemap& acc )
{
   for( const auto& d : defs )
   {
      if( !results. contains( d. first ))
      {
         std::cout << "converting " << d. first << "\n";
         auto c = convert( smp, d. second, defs, acc );
         c = conv2single( smp, c );
         smp. delta_epsilon. insert( { state_of(c), acc. at( d. first ) } );
         results. insert( { d. first, std::move(c) } );
      }
   }
}


std::ostream& atm::operator << ( std::ostream& out, const statemap& acc )
{
   out << "Statemap:\n";
   for( const auto& a : acc )
      out << "   " << a. first << " : " << a. second << "\n";
   out << "\n";
   return out;
}

