
#include "algorithms.h"
#include <queue>


void atm::close_eps( const simple& smp, stateset& set ) 
{
   std::queue< state > unchecked;
   for( auto s : set )
      unchecked. push(s);

   while( unchecked. size( ))
   {
      auto s = unchecked. front( );
      unchecked. pop( );
      auto rg = smp. delta_epsilon. equal_range(s);
      for( auto p = rg. first; p != rg. second; ++ p )
      {
         if( set. insert( p -> second ))
            unchecked. push( p -> second );
      }
   }
}


atm::stateset atm::apply_tuple( const simple& smp,
                                const stateset& tuple,
                                const stateset& single )
{
   stateset res;
   for( const auto& t : tuple )
   {
      for( const auto& s : single )
      {
         auto r = smp. delta_tuple. equal_range( { t, s } );
         for( auto p = r. first; p != r. second; ++ p )
            res. insert( p -> second );
      }
   }
   return res;
}


atm::stateset atm::apply_set( const simple& smp,
                              const stateset& set,
                              const stateset& element )
{
   stateset res; 
   for( const auto& s : set )
   {
      for( const auto& e : element ) 
      {
         auto r = smp. delta_set. equal_range( { s, e } );  
         for( auto p = r. first; p != r. second; ++ p )
            res. insert( p -> second );  
      }
   }
   return res; 
}

namespace
{
   using namespace atm;

   stateset statesinvector( const std::vector< state > & vect )
   {
      stateset res;
      for( const auto& s : vect )
         res. insert(s);
      return res;
   }
 
   template< typename D, typename R, typename C, typename E > 
   stateset
   apply( const std::vector< stepfunc<D,R,C,E>> & vect, const D& d )
   {
      stateset res;
      for( const auto& f : vect )
         res. insert( f. apply(d));
      return res;
   }

   template< typename D, typename R, typename H, typename E >
   stateset
   apply( const std::vector< finfunc<D,R,H,E>> & vect, const D& d )
   {
      stateset res;
      for( const auto& f : vect )
         res. insert( f. apply(d));
      return res;
   }

   template< typename D, typename R, typename C, typename E > 
   stateset
   getdefault( const std::vector< stepfunc<D,R,C,E>> & vect )
   {
      stateset res;
      for( const auto& f : vect )
         res. insert( f. initial );
      return res;
   }

   template< typename D, typename R, typename H, typename E >
   stateset
   getdefault( const std::vector< finfunc<D,R,H,E>> & vect )
   {
      stateset res;
      for( const auto& f : vect )
         res. insert( f. def );
      return res;
   }

}


atm::stateset atm::run( const simple& smp, const data::tree& tr ) 
{

   switch( tr. sel( )) 
   {
   case data::dat_unit:
      {
         stateset res = statesinvector( smp. delta_unit );
         close_eps( smp, res );
         return res;
      } 
   
   case data::dat_bool:
      {
         stateset res = apply( smp. delta_bool, tr. view_bool( ). b( ));
         close_eps( smp, res );
         return res;
      }
 
   case data::dat_char:
      {
         stateset res = apply( smp. delta_char, tr. view_char( ). c( ));
         close_eps( smp, res );  
         std::cout << tr << " -> " << res << "\n"; 
         return res;
      }

   case data::dat_sel:
      {
         stateset res = apply( smp. delta_sel, tr. view_usel( ). s( ));
         close_eps( smp, res );
         return res;
      }

   case data::dat_u64:
      {
         stateset res;
         for( const auto& u : smp. delta_u64 )
            res. insert( u. apply( tr. view_u64( ). u( )) );
         close_eps( smp, res );
         return res;
      }

   case data::dat_integer:
      {
         stateset res;
         for( const auto& u : smp. delta_integer )
            res. insert( u. apply( tr. view_integer( ). i( )) );
         close_eps( smp, res );
         return res;
      }

   case data::dat_double:
      {
         stateset res = statesinvector( smp. delta_double );
         close_eps( smp, res );
         std::cout << "double -> " << res << "\n";
         return res;
      }

   case data::dat_tuple:
      {
         auto tup = tr. view_tuple( );
         stateset res; res. insert( smp. empty_tuple );
         close_eps( smp, res );
 
         for( size_t i = 0; i != tup. size( ); ++ i ) 
         { 
            auto sub = run( smp, tup. val(i));
            res = apply_tuple( smp, res, sub ); 
            close_eps( smp, res ); 
         }
         std::cout << tr << " -> " << res << "\n";
         return res;
      }

   case data::dat_array: 
      {
         auto ar = tr. view_array( );
         stateset res; res. insert( smp. empty_set );
         close_eps( smp, res ); 

         for( size_t i = 0; i != ar. size( ); ++ i ) 
         {
            auto sub = run( smp, ar. val(i));
            res = apply_set( smp, res, sub ); 
            close_eps( smp, res );
         }
         std::cout << tr << " -> " << res << "\n";
         return res;
      }

   }
 
   std::cout << "run( ), unrecognized selector " << tr. sel( ) << "\n";
   throw std::logic_error( "atm::run()" );
}


atm::state atm::run_det( const simple& smp, const data::tree& tr ) 
{
   switch( tr. sel( )) 
   {
   case data::dat_unit:
      {
         if( smp. delta_unit. size( ) == 1 )
            return smp. delta_unit. front( ); 
         else
            return smp. trap;
      } 

   case data::dat_bool:
      {
         if( smp. delta_bool. size( ) == 1 ) 
            return smp. delta_bool. front( ). apply( tr. view_bool( ). b( )); 
         else
            return smp. trap; 
      }

   case data::dat_char:
      {
         if( smp. delta_char. size( ) == 1 )
            return smp. delta_char. front( ). apply( tr. view_char( ). c( ));
         else 
            return smp. trap; 
      }

   case data::dat_sel:
      {
         if( smp. delta_sel. size( ) == 1 )
            return smp. delta_sel. front( ). apply( tr. view_usel( ). s( ));
         else
            return smp. trap;
      }

   case data::dat_u64:
      {
         if( smp. delta_u64. size( ) == 1 )
            return smp. delta_u64. front( ). apply( tr. view_u64( ). u( )); 
         else 
            return smp. trap;  
      }

   case data::dat_integer:
      {
         if( smp. delta_integer. size( ) == 1 ) 
            return smp. delta_integer. front( ). apply( tr. view_integer( ). i( ));
         else
            return smp. trap; 
      }

   case data::dat_double:
      {
         if( smp. delta_double. size( ) == 1 ) 
            return smp. delta_double. front( );  
         else 
            return smp. trap;  
      }

   case data::dat_tuple:
      {
         auto tup = tr. view_tuple( );
         state q = smp. empty_tuple;
         for( size_t i = 0; i != tup. size( ); ++ i ) 
         { 
            state sub = run_det( smp, tup. val(i));
            auto it = smp. delta_tuple. find( { q, sub } );
            if( it != smp. delta_tuple. end( ))
               q = ( it -> second );
            else
               q = smp. trap;
         }
         return q;
      }

   case data::dat_array: 
      {
         auto ar = tr. view_array( );
         state q = smp. empty_set; 
         for( size_t i = 0; i != ar. size( ); ++ i ) 
         {
            state sub = run_det( smp, ar. val(i));
            auto it = smp. delta_set. find( { q, sub } ); 
            if( it != smp. delta_set. end( ))
               q = ( it -> second );
            else
               q = smp. trap; 
         }
         return q;
      }
   }

   std::cout << "run determinsitically( ), unrecognized " << tr. sel( ) << "\n";
   throw std::logic_error( "atm::run_det()" );
}


atm::state
atm::create_or_reuse( stateset set, 
                      const stateset::map< state > & checked, 
                      stateset::map< state > & unchecked, simple& det )
{
   state q = det. create_states(0);
      // We get the next state from det, but do not commit to it.

   auto it = checked. find( set );
   if( it != checked. end( ))
      return it -> second;  
 
   auto pr = unchecked. emplace( std::move( set ), q );
   if( pr. second )
   {
      det. create_states(1);
      return q; 
         // state is new, we commit to q, and return it.
   }
   else
      return pr. first -> second;  
}


namespace
{
   using namespace atm;

   state 
   merge( const std::vector< state > & statevector,
          const simple& nondet, simple& det,
          const stateset::map< state > & checked,
          stateset::map< state > & unchecked )
   {
      auto set = statesinvector( statevector );
      close_eps( nondet, set );
      auto q = create_or_reuse( std::move( set ), checked, unchecked, det ); 
      return q;
   }


   template< typename D, typename H, typename E >
   std::unordered_set<D,H,E> 
   getdomains( const std::vector< finfunc<D,state,H,E>> & funcvector )
   {
      std::unordered_set<D,H,E> domain;
      for( const auto& f : funcvector )
      {
         for( const auto& p : f )
            domain. insert( p. first );
      }
      return domain;
   }


   template< typename D, typename H, typename E >
   finfunc<D,state,H,E>  
   merge( const std::vector< finfunc<D,state,H,E> > & funcvector,
          const simple& nondet, simple& det, 
          const stateset::map< state > & checked,
          stateset::map< state > & unchecked )
   {
      auto defset = getdefault( funcvector );
      close_eps( nondet, defset );
      auto q = create_or_reuse( std::move( defset ), checked, unchecked, det );

      auto resfunc = finfunc<D,state,H,E> (q);

      auto domain = getdomains( funcvector );
      for( const auto& sel : domain )
      {
         auto targetset = apply( funcvector, sel );
         close_eps( nondet, targetset );
         q = create_or_reuse( std::move( targetset ), checked, unchecked, det );
         resfunc. assign( sel, q ); 
      }
      return resfunc;
   }


   template< typename D, typename C, typename E >
   std::set<D,C>
   getdomains( const std::vector< stepfunc<D,state,C,E>> & funcvector )
   {
      std::set<D,C> domain;
      for( const auto& f : funcvector )
      {
         for( const auto& p : f )
            domain. insert( p.d );
      }
      return domain;
   }


   template< typename D, typename C, typename E >
   stepfunc<D,state,C,E> 
   merge( const std::vector< stepfunc<D,state,C,E>> & funcvector,
          const simple& nondet, simple& det,
          const stateset::map< state > & checked,
          stateset::map< state > & unchecked )
   {
      auto defset = getdefault( funcvector );
      close_eps( nondet, defset );
      auto q = create_or_reuse( std::move( defset ), checked, unchecked, det );

      auto resfunc = stepfunc<D,state,C,E> (q);

      auto domain = getdomains( funcvector );
      for( const auto& c : domain )
      {
         auto targetset = apply( funcvector, c );
         close_eps( nondet, targetset );
         q = create_or_reuse( std::move( targetset ), checked, unchecked, det );
         resfunc. append( c, q );
      }
      return resfunc;
   }

}


atm::cluster
atm::make_deterministic( const cluster& clust )
{
   simple det;
   const simple& nondet = clust. common;

   stateset::map< state > checked;
   stateset::map< state > unchecked;
   {
      auto empty = stateset( );
      empty. insert( nondet. empty_tuple );
      close_eps( nondet, empty );
      auto p = unchecked. emplace( std::move( empty ), det. empty_tuple );
      det. empty_tuple = p. first -> second; 

      empty. clear( );
      empty. insert( nondet. empty_set );
      close_eps( nondet, empty );
      p = unchecked. emplace( std::move( empty ), det. empty_set );
      det. empty_set = p. first -> second;  // Unlikely, but who knows? 
   }

   det. delta_unit. push_back( 
           merge( nondet. delta_unit, nondet, det, checked, unchecked )); 
   det. delta_bool. push_back(
           merge( nondet. delta_bool, nondet, det, checked, unchecked )); 
   det. delta_char. push_back( 
           merge( nondet. delta_char, nondet, det, checked, unchecked ));
   det. delta_sel. push_back( 
           merge( nondet. delta_sel, nondet, det, checked, unchecked )); 
   det. delta_u64. push_back( 
           merge( nondet. delta_u64, nondet, det, checked, unchecked ));
   det. delta_integer. push_back(
           merge( nondet. delta_integer, nondet, det, checked, unchecked ));
   det. delta_double. push_back(
           merge( nondet. delta_double, nondet, det, checked, unchecked ));
   
   // We have binary transitions, so we need to use 
   // a resolution-like algorithm:

   while( unchecked. size( ))
   {
      auto given = unchecked. begin( );
      std::cout << "given = " << ( given -> first ) << "\n";

      for( auto p : checked )
      {
         auto res = apply_tuple( nondet, p. first, given -> first );
         if( res. size( ))
         { 
            close_eps( nondet, res );
            auto qres = create_or_reuse( std::move( res ),
                                checked, unchecked, det );
            det. delta_tuple. insert( {{ p. second, given -> second }, qres } );
         }

         res = apply_tuple( nondet, given -> first, p. first );
         if( res. size( ))
         {
            close_eps( nondet, res );
            auto qres = create_or_reuse( std::move( res ),
                                checked, unchecked, det );
            det. delta_tuple. insert( {{ given -> second, p. second }, qres } );
         }

         res = apply_set( nondet, p. first, given -> first );
         if( res. size( ))
         {
            close_eps( nondet, res );
            auto qres = create_or_reuse( std::move( res ),
                               checked, unchecked, det );  
            det. delta_set. insert( {{ p. second, given -> second }, qres } );  
         }

         res = apply_set( nondet, given -> first, p. first );
         if( res. size( ))
         {
            close_eps( nondet, res );
            auto qres = create_or_reuse( std::move( res ),
                               checked, unchecked, det );
            det. delta_set. insert( {{ given -> second, p. second }, qres } );
         }
      }

      checked. insert( unchecked. extract( given ));
   }

   std::cout << det << "\n";
   cluster res = std::move( det );

   std::cout << "backmap " << checked << "\n";
   for( const auto& ch : checked )
   {
      for( auto q : ch. first )
      {
         auto acc = clust. props_inv. find(q);
         if( acc != clust. props_inv. end( ))
         {
            for( const auto& id : acc -> second )
               res. add_accept( id, ch. second );   
         } 
      }   
   }
 
   return res;
}

std::ostream& 
atm::operator << ( std::ostream& out, 
                   const stateset::map< state > & collapse )
{
   out << "Subset Collapse:\n";
   for( const auto& p : collapse )
      out << "   " << p. first << " -> " << p. second << "\n";
   return out;
}

