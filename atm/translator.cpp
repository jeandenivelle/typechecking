
#include "translator.h"
#include "boolswitch.h"


identifier::set
atm::translator::insert( const regexp::defmap& defs ) 
{
   identifier::set failed;

   for( const auto& d : defs )
   {
      state acc = shared. create_states(1); 
      auto ins = accepting. emplace( d. first, acc );
      if( !ins. second )
         failed. insert( d. first ); 
   }

   for( const auto& d : defs )
   {
      convresult c = translate( d. second ); 
      if( c. sel( ) == atm_error )
         failed. insert( d. first );
      else
      {
         c = conv2single(c); 
         state acc = accepting. at( d. first );
         shared. delta_epsilon. insert( { c. getstate( ), acc } );
      }
   }   
   return failed;
}

atm::convresult 
atm::translator::translate( const regexp::expr& e )
{
   if constexpr( false )
   {
      std::cout << "translating:  " << e << "\n";
   }

   switch( e. sel( ))
   {
   case regexp::type_unit:
      {
         state q = shared. create_states(1);
         shared. delta_unit. push_back(q);
         return { atm_single, q };
      }

   case regexp::flt_bool:
      {
         state q = shared. create_states(1);
         auto trans = boolswitch( q, shared. trap );
         shared. delta_bool. push_back( e. view_filter_bool( ). func( ).
                                        transform_range( trans ));
         return { atm_single, q };
      }

   case regexp::flt_char:
      {
         state q = shared. create_states(1);
         auto trans = boolswitch( q, shared. trap );
         shared. delta_char. push_back( e. view_filter_char( ). func( ).
                                        transform_range( trans ));
         return { atm_single, q };
      }

   case regexp::flt_sel:
      {
         state q = shared. create_states(1);
         auto trans = boolswitch( q, shared. trap );
         shared. delta_sel. push_back( e. view_filter_sel( ). func( ).
                                       transform_range( trans ));
         return { atm_single, q };
      }

   case regexp::flt_u64:
      {
         state q = shared. create_states(1);
         auto trans = boolswitch( q, shared. trap );
         shared. delta_u64. push_back( e. view_filter_u64( ). func( ).
                                       transform_range( trans ));
         return { atm_single, q };
      }

   case regexp::flt_integer:
      {
         state q = shared. create_states(1);
         auto trans = boolswitch( q, shared. trap );
         shared. delta_integer. push_back( e. view_filter_integer( ). func( ).
                                           transform_range( trans ));
         return { atm_single, q };
      }

   case regexp::type_double:
      {
         state q = shared. create_states(1);
         shared. delta_double. push_back(q);
         return { atm_single, q };
      }

   case regexp::ref_ident:
      {
         auto p = accepting. find( e. view_reference( ). ident( ));
         if( p != accepting. end( ))
            return convresult( atm_single, p -> second ); 
         else
            return convresult( atm_error, "unknown identifier" );
      }

   case regexp::tup_constr:
      {
         auto tup = e. view_tuple( );
         std::vector< convresult > sub;
         for( size_t i = 0; i != tup. size( ); ++ i )
         {
            sub. push_back( conv2single( translate( tup. sub(i) )));
         }

         for( const auto& s : sub )
         {
            if( s. sel( ) == atm_error )
               return s;
         }

         auto q = shared. empty_tuple;
         for( const auto& s : sub )
         {
            auto qnext = shared. create_states(1);
            shared. delta_tuple. insert( 
                                   { { q, s. view_single( ). q( ) }, qnext } );
            q = qnext;
         }

         return convresult( atm_tuple, q, sub. size( ));
      }

   case regexp::tup_fill:
      {
         auto fl = e. view_fill( );
         convresult pref = translate( fl. prefix( ));
         if( pref. sel( ) != atm_tuple )
         {
            return convresult( atm_error,
                               "first argument of fill must be a tuple" );
         }

         std::vector< state > fillers;
         for( size_t i = 0; i != fl. size( ); ++ i )
         {
            auto cv = translate( fl. filler(i));
            if( cv. sel( ) == atm_error )
               return cv;
            cv = conv2single( cv );
            fillers. push_back( cv. getstate( ));
         }

         auto tupq = pref. view_tuple( ). q( );
         for( const auto& f : fillers )
            shared. delta_tuple. insert( { { tupq, f }, tupq } );

         auto resq = shared. create_states(1);
         shared. delta_epsilon. insert( { tupq, resq } );
         return convresult( atm_tuple, resq, pref. view_tuple( ). sz( ));
      }

   case regexp::log_or:
      {
         auto disj = e. view_disjunction( );

         std::vector< convresult > subresults;
         for( size_t i = 0; i != disj. size( ); ++ i )
            subresults. push_back( translate( disj. sub(i) ));

         std::cout << "disjunction:\n";
         for( const auto& s : subresults )
            std::cout << "   " << s << "\n";

         // If some of the subresults are a set, we convert them into a
         // single:

         for( auto& sub : subresults )
         {
            if( sub. sel( ) == atm_set )
               sub = conv2single( sub );

            if( sub. sel( ) == atm_error )
               return sub;
         }
         auto acc = shared. create_states(1);
         for( auto& s : subresults )
            shared. delta_epsilon. insert( { s. getstate( ), acc } );

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
            auto res = translate( wrd. smp(i));
            res = conv2single( res );
            if( res. sel( ) == atm_error )
               return res;

            sub. push_back( res. getstate( ));
         }

         return convresult( atm_set, oneword( sub ));
      }

   case regexp::set_linear:
   case regexp::set_circular:
      {
         auto mult = e. view_multiply( );
         auto set = translate( mult. set( ));
         if( set. sel( ) != atm_set )
         {
            return convresult( atm_error,
                      "first argument of linear/circular is not a set" );
         }

         std::vector< state > disj;
         for( size_t i = 0; i != mult. size( ); ++ i )
         {
            auto sub = translate( mult. disj(i));
            sub = conv2single( sub );
            if( sub. sel( ) == atm_error )
               return sub;

            disj. push_back( sub. getstate( ));
         }

         auto bld = set. view_set( ). extr_bld( );
         if( e. sel( ) == regexp::set_linear )
            bld. addlinear( disj, mult. factor( ));

         if( e. sel( ) == regexp::set_circular )
            bld. addcircular( disj, mult. factor( ));

         return convresult( atm_set, std::move( bld ));
      }

   }

   std::cout << "trying to translate: " << e. sel( ) << "\n";
   throw std::logic_error( "not implemented" );
}


atm::convresult
atm::translator::conv2single( const convresult& res )
{
   switch( res. sel( ))
   {
   case atm_single:
      return res;

   case atm_tuple:
      return convresult( atm_single, res. view_tuple( ). q( ));

   case atm_set:
      return translate2simple( res. view_set( ). bld( ));
   }

   // Actually, this cannot happen, unless res is already an error:

   return convresult( atm_error,
              std::string( "didn't know how to convert " ) +
                 getcstring( res. sel( )) + " to single" );
}


atm::convresult
atm::translator::translate2simple( const builder& bld )
{
   state entry = shared. create_states(1);
   shared. delta_epsilon. insert( { shared. empty_set, entry } );

   for( const auto& trans : bld. delta_set )
   {
      shared. delta_set. insert(
         { { entry + trans. from, trans. element }, entry + trans. to } );
   }

   for( const auto& eps : bld. delta_eps )
   {
      shared. delta_epsilon. insert( { entry + eps. from, entry + eps. to } );
   }

   // We know that bld. nrstates > 0.

   auto acc = entry + bld. nrstates;

   for( size_t i = 0; i != bld. nrstates; ++ i )
      shared. create_states(1);

   return convresult( atm_single, acc );
}

#if 0

void atm::cluster::info::print( std::ostream& out ) const
{
   out << acc;
   if( comments. size( ))
      out << "       // " << comments;
}


#endif

void atm::translator::print( std::ostream& out ) const
{
   out << "Translator:\n\n";
   shared. print( out );   

   out << "Accepting states:\n";
   for( const auto& acc : accepting )
   {
      out << "   " << acc.first << "  ->  " << acc.second << "\n";
   }

}


