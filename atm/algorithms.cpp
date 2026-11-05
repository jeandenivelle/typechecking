
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
      
#if 0
   stateset checked; 
   while( unchecked. size( ))
   {
      auto s1 = * ( unchecked. begin( ));
      unchecked. remove(s1);
      checked. insert(s1);

      auto it = atm. delta_eps. find( s1 );
      if( it != atm. delta_eps. end() ) {
         for( auto s2 : it -> second )
         {
            if( !checked. contains(s2) && !unchecked. contains(s2)) 
               unchecked. insert(s2); 
         }
      }
   }

   return checked;
#endif
   }
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


atm::stateset atm::run( const simple& smp, const data::tree& tr ) 
{
   std::cout << "running on " << tr << "\n";
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
         stateset res;
         for( const auto& f : smp. delta_char )
            res. insert( f. apply( tr. view_char( ). c( )) );
         close_eps( smp, res );  
         return res;
      }
   case data::sel_usel:
      {
         stateset res; 
         for( const auto& f : smp. delta_usel )
            res. insert( f. apply( tr. view_usel( ). s( )) ); 
         close_eps( smp, res );
         return res; 
      }
#if 0
   
   case data::tree_u64:
      sset. insert( atm. delta_u64( data. view_u64(). i() ) );
      break;

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
         stateset res = { smp. empty_tuple };
         close_eps( smp, res );
 
         for( size_t i = 0; i < tup. size( ); ++ i ) 
         { 
            auto sub = run( smp, tup. val(i));
            std::cout << "in a tuple received " << sub << "\n";

#if 0
            auto sset_at_i = run( smp, tup. val(i)); 
            stateset new_sset = set_delta( atm. delta_tup, sset, sset_at_i );
         sset = eps_closure( atm, std::move( new_sset ));
         if( sset. size() == 0 ) {
            sset. insert( atm. collapsed );
            return sset;
#endif
         }
      }
      throw std::logic_error( "unfinished" );
      break;

   case data::sel_array: 
      {
         auto ar = tr. view_array( );
         stateset res = { smp. empty_set };
         close_eps( smp, res ); 

         for( size_t i = 0; i < ar. size( ); ++ i ) 
         {
            auto sub = run( smp, ar. val(i));
            res = apply_set( smp, res, sub ); 
            close_eps( smp, res );
         }
         return res;
      }
   }
 
   std::cout << "run( ), unrecognized selector " << tr. sel( ) << "\n";
   throw std::logic_error( "atm::run()" );
}


