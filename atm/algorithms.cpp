
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
         res. insert( f. def );
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

#if 0
   case data::tree_never:
      sset. insert( atm. collapsed );
      break;

   case data::tree_unit:
      sset. insert( atm. delta_unit );
      break;
   
   case data::tree_bool:
      sset. insert( atm. delta_bool( data. view_bool(). b() ) );
      break;
#endif

   case data::sel_char:
      {
         stateset res = apply( smp. delta_char, tr. view_char( ). c( ));
         close_eps( smp, res );  
         std::cout << tr << " -> " << res << "\n"; 
         return res;
      }

   case data::sel_usel:
      {
         stateset res = apply( smp. delta_sel, tr. view_usel( ). s( ));
         close_eps( smp, res );
         return res;
      }

   case data::sel_u64:
      {
         stateset res;
         for( const auto& u : smp. delta_u64 )
            res. insert( u. apply( tr. view_u64( ). u( )) );
         close_eps( smp, res );
         std::cout << tr << " -> " << res << "\n";
         return res;
      }

#if 0
   case data::tree_bigint:
      sset. insert( atm. delta_bigint( data. view_bigint(). i() ) );
      break;

   case data::tree_double:
      sset. insert( atm. delta_double( data. view_double(). d() ) );
      break;

#endif

   case data::sel_tuple:
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

   case data::sel_array: 
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


atm::simple::sel_func
atm::merge_sel( const simple& nondet, simple& det, 
                stateset::map<state> & backmap )
{
   std::unordered_set< usel, usel::hash, usel::equal_to > domain;
   for( const auto& d : nondet. delta_sel )
   {
      for( const auto& p : d )
         domain. insert( p. first );
   }

   auto def = getdefault( nondet. delta_sel );
   close_eps( nondet, def );
   auto q = det.create_states(0);
   auto p = backmap. emplace( std::move( def ), q );
   if( p. second )
      det. create_states(1);
   q = p. first -> second;

   atm::simple::sel_func func(q);
   for( const auto& sel : domain )
   {
      std::cout << "   " << sel << "\n";
      auto set = apply( nondet. delta_sel, sel );
      close_eps( nondet, set );
      std::cout << "--> " << set << "\n";
      auto q = det. create_states(0); 
         // No states are created, but we get a state.
      auto p = backmap. emplace( std::move( set ), q );
      if( p. second )
         det. create_states(1);
      q = p. first -> second;
      func. assign( sel, q ); 
      // auto q = backmap. insert( back );
   }

   std::cout << "returning\n";
}


