
#include "cluster.h"
#include "boolswitch.h"

void atm::cluster::add_accept( const identifier& id, state q )
{
   props[ id ]. acc. insert(q);
   props_inv[q]. insert( id );
}

void atm::cluster::regexp2nondet( const regexp::defmap& defs ) 
{
   for( const auto& df : defs )
   {
      auto p = props. find( df. first ); 
      if( p != props. end( ))
         p -> second. comments. append( "added an automaton" ); 
      else
      { 
         auto q = common. create_states(1);
         add_accept( df. first, q );
      }
   }

   for( const auto& df : defs )
   {
      convresult c = regexp2nondet( df. second ); 
      c = conv2single(c);
      state q = * props. at( df. first ). acc. begin( ); 
         // Since each state in acc represents df. first,
         // it is sufficient to add an epsilon transition to the first.

      common. delta_epsilon. insert( { c. getstate( ), q } );
   }   
}


atm::convresult atm::cluster::regexp2nondet( const regexp::expr& e )
{
   std::cout << "converting:  " << e << "\n";

   switch( e. sel( ))
   {
   case regexp::type_unit:
      {
         state q = common. create_states(1);
         common. delta_unit. push_back(q);
         return { atm_single, q };
      }

   case regexp::flt_bool:
      {
         state q = common. create_states(1);
         auto trans = boolswitch( q, common. trap );
         common. delta_bool. push_back( e. view_filter_bool( ). func( ).
                                        transform_range( trans ));
         return { atm_single, q };
      }

   case regexp::flt_char:
      {
         state q = common. create_states(1);
         auto trans = boolswitch( q, common. trap );
         common. delta_char. push_back( e. view_filter_char( ). func( ).
                                        transform_range( trans ));
         return { atm_single, q };
      }

   case regexp::flt_sel:
      {
         state q = common. create_states(1);
         auto trans = boolswitch( q, common. trap );
         common. delta_sel. push_back( e. view_filter_sel( ). func( ).
                                       transform_range( trans ));
         return { atm_single, q };
      }

   case regexp::flt_u64:
      {
         state q = common. create_states(1);
         auto trans = boolswitch( q, common. trap );
         common. delta_u64. push_back( e. view_filter_u64( ). func( ).
                                       transform_range( trans ));
         return { atm_single, q };
      }

   case regexp::flt_integer:
      {
         state q = common. create_states(1);
         auto trans = boolswitch( q, common. trap );
         common. delta_integer. push_back( e. view_filter_integer( ). func( ).
                                           transform_range( trans ));
         return { atm_single, q };
      }

   case regexp::type_double:
      {
         state q = common. create_states(1);
         common. delta_double. push_back(q);
         return { atm_single, q };
      }

   case regexp::ref_ident:
      {
         auto p = props. find( e. view_reference( ). ident( ));
         if( p != props. end( ))
         {
            if( p -> second. acc. size( ) == 1 )
               return { atm_single, *( p -> second .acc. begin( )) }; 
            
            auto acc = common. create_states(1);
            for( auto q : p -> second. acc ) 
               common. delta_epsilon. insert( { q, acc } ); 
            return { atm_single, acc }; 
         }
         else
            throw std::logic_error( "trying to use unknown identifier" );
      }

   case regexp::tup_constr:
      {
         auto tup = e. view_tuple( );
         std::vector< convresult > sub;
         for( size_t i = 0; i != tup. size( ); ++ i )
         {
            sub. push_back( conv2single( regexp2nondet( tup. sub(i) )));
         }

         for( const auto& s : sub )
         {
            if( s. sel( ) == atm_error )
               return s;
         }

         auto q = common. empty_tuple;
         for( const auto& s : sub )
         {
            auto q1 = common. create_states(1);
            common. delta_tuple. insert( 
                                   {{ q, s. view_single( ). q( ) }, q1 } );
            q = q1;
         }

         return convresult( atm_tuple, q, sub. size( ));
      }

   case regexp::tup_fill:
      {
         auto fl = e. view_fill( );
         convresult pref = regexp2nondet( fl. prefix( ));
         if( pref. sel( ) != atm_tuple )
         {
            return convresult( atm_error,
                               "first argument of fill must be a tuple" );
         }

         std::vector< state > fillers;
         for( size_t i = 0; i != fl. size( ); ++ i )
         {
            auto cv = regexp2nondet( fl. filler(i));
            if( cv. sel( ) == atm_error )
               return cv;
            cv = conv2single( cv );
            fillers. push_back( cv. getstate( ));
         }

         auto tupq = pref. view_tuple( ). q( );
         for( const auto& f : fillers )
            common. delta_tuple. insert( { { tupq, f }, tupq } );

         auto resq = common. create_states(1);
         common. delta_epsilon. insert( { tupq, resq } );
         return convresult( atm_tuple, resq, pref. view_tuple( ). sz( ));
      }

 case regexp::log_or:
      {
         auto disj = e. view_disjunction( );

         std::vector< convresult > subresults;
         for( size_t i = 0; i != disj. size( ); ++ i )
            subresults. push_back( regexp2nondet( disj. sub(i) ));

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
         auto acc = common. create_states(1);
         for( auto& s : subresults )
            common. delta_epsilon. insert( { s. getstate( ), acc } );

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
            auto res = regexp2nondet( wrd. smp(i));
            res = conv2single( res );
            if( res. sel( ) == atm_error )
               return res;

            sub. push_back( res. getstate( ));
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
         auto set = regexp2nondet( mult. set( ));
         if( set. sel( ) != atm_set )
         {
            return convresult( atm_error,
                      "first argument of linear/circular is not a set" );
         }

         std::vector< state > disj;
         for( size_t i = 0; i != mult. size( ); ++ i )
         {
            auto sub = regexp2nondet( mult. disj(i));
            sub = conv2single( sub );
            if( sub. sel( ) == atm_error )
               return sub;

            disj. push_back( sub. getstate( ));
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

atm::convresult
atm::cluster::conv2single( const convresult& res )
{
   switch( res. sel( ))
   {
   case atm_single:
      return res;

   case atm_tuple:
      return convresult( atm_single, res. view_tuple( ). q( ));

   case atm_set:
      return makesimple( res. view_set( ). bld( ));
   }

   std::cout << "conv2single " << res << "\n";
   throw std::logic_error( "falling through" );

   return convresult( atm_error,
              std::string( "didn't know how to convert " ) +
                 getcstring( res. sel( )) + " to single" );
}


atm::convresult
atm::cluster::makesimple( const builder& bld )
{
   state entry = common. create_states(1);
   common. delta_epsilon. insert( { common. empty_set, entry } );

   for( const auto& trans : bld. delta_set )
   {
      common. delta_set. insert(
         { { entry + trans. from, trans. element }, entry + trans. to } );
   }

   for( const auto& eps : bld. delta_eps )
   {
      common. delta_epsilon. insert( { entry + eps. from, entry + eps. to } );
   }

   // We know that bld. nrstates > 0.

   auto acc = entry + bld. nrstates;

   for( size_t i = 0; i != bld. nrstates; ++ i )
      common. create_states(1);

   return convresult( atm_single, acc );
}


void atm::cluster::info::print( std::ostream& out ) const
{
   out << acc;
   if( comments. size( ))
      out << "       // " << comments;
}


void atm::cluster::print( std::ostream& out ) const
{
   out << "Cluster:\n";
   common. print( out );   

   for( const auto& p : props )
   {
      out << p.first << "  ->  " << p.second << "\n";
   }

   for( const auto& inv : props_inv )
   {
      out << inv. first << " : ";
      for( const auto& id : inv. second )
         out << "   " << id << "\n";
   }
}

