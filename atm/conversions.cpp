
#include "conversions.h"

atm::statemap 
atm::create_accepting( const regexp::defmap& defs, simple& smp )
{
   statemap acc;
   for( const auto& d : defs ) 
      acc. insert( { d. first, smp. create_state( ) } );
   return acc; 
}

atm::state
atm::conv_state( const simple& smp, state base, size_t i )
{
   if( i == 0 )
      return smp. empty_set;
   else
      return base + ( i - 1 );
}

atm::state
atm::add2simple( const builder& bld, simple& smp )
{
   // In bld, we match 0 to emptyset,
   // 1 to q + 0,
   // 2 to q + 1,
   // nrstates to q + ( nrstates - 1 ).
   // q + ( nrstates - 1 ) will be returned as accepting state.

   if( bld. nrstates == 0 )
   {
      // We treat the empty builder separately. Otherwise, we would 
      // have to make smp. empty_set an accepting state, which I think 
      // is problematic. 
      //    It may still happen during determinization, though. 

      auto q = smp. create_state( );
      smp. delta_epsilon. insert( { smp. empty_set, q } );
      return q;
   }

   state base = smp. create_state( );

   for( const auto& trans : bld. delta_set )
   {
      smp. delta_set. insert( 
         { { conv_state( smp, base, trans. from ), trans. element },
             conv_state( smp, base, trans. to ) } );
   }

   for( const auto& eps : bld. delta_eps )
   {
      smp. delta_epsilon. insert( 
         { conv_state( smp, base, eps. from ),  
           conv_state( smp, base, eps. to ) } );
   }

   // We know that bld. nrstates > 0.

   auto acc = conv_state( smp, base, bld. nrstates );

   for( size_t i = 0; i + 1 != bld. nrstates; ++ i )
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

   }

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

   case regexp::flt_sel:
      {
         state q = smp. create_state( ); 
         auto& u = smp. add_delta_usel( smp. trap ); 
         for( const auto& f : e. view_filter_sel( ). func( ))
            u. assign( f. first, q ); 
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
         auto dim = e. view_dimension( );
         auto bld = convert( smp, dim. set( ), defs, acc );   
         std::cout << "this is bld: " << bld << "\n"; 
         throw std::logic_error( "sadly unfinished" ); 
      }
   }

   std::cout << e << "\n";
   throw std::logic_error( "not implemented" ); 
}

std::ostream& atm::operator << ( std::ostream& out, const statemap& acc )
{
   out << "Statemap:\n";
   for( const auto& a : acc )
      out << "   " << a. first << " : " << a. second << "\n";
   out << "\n";
   return out;
}

