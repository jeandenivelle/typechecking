#include "simulation.h"

#include <map>
#include <stdexcept>


atm::stateset 
eps_closure( const atm::simple& atm, atm::stateset unchecked ) {
   atm::stateset checked; 
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
}


namespace
{

atm::stateset set_delta(
   const std::map< atm::state, std::map< atm::state, atm::state, atm::state::less >, atm::state::less > & delta,
   const atm::stateset& sset1,
   const atm::stateset& sset2 
) {
   atm::stateset new_sset;
   
   for( auto state1 : sset1 ) {
      auto itr1 = delta. find( state1 );
      if( itr1 != delta. end( ))
      {
         for( auto state2 : sset2 ) {
            auto itr2 = itr1-> second. find( state2 );
            if( itr2 != itr1-> second. end( )) {
               auto new_state = itr2-> second;
               new_sset. insert( new_state );
            }
         }
      }
   }

   return new_sset;
}
}


atm::stateset simulate
( const atm::simple& atm, const data::tree& data ) {
   atm::stateset sset;

   switch( data. sel() ) {
   case data::tree_never:
      sset. insert( atm. collapsed );
      break;

   case data::tree_unit:
      sset. insert( atm. delta_unit );
      break;
   
   case data::tree_bool:
      sset. insert( atm. delta_bool( data. view_bool(). b() ) );
      break;

   case data::tree_char:
      sset. insert( atm. delta_char( data. view_char(). c() ) );
      break;
      
   case data::tree_usel:
      sset. insert( atm. delta_usel( data. view_usel(). s() ) );
      break;
   
   case data::tree_u64:
      sset. insert( atm. delta_u64( data. view_u64(). i() ) );
      break;

   case data::tree_bigint:
      sset. insert( atm. delta_bigint( data. view_bigint(). i() ) );
      break;

   case data::tree_double:
      sset. insert( atm. delta_double( data. view_double(). d() ) );
      break;

   case data::tree_tuple:
   {
      auto tuple = data. view_tuple();

      /* initial set state */
      sset. insert( atm. empty_tup );
      sset = eps_closure( atm, std::move( sset ));
      
      for( size_t i = 0; i < tuple. size(); ++i ) { 
         auto sset_at_i = simulate( atm, tuple. val( i ) ); 
         atm::stateset new_sset = set_delta( atm. delta_tup, sset, sset_at_i );
         sset = eps_closure( atm, std::move( new_sset ));
         if( sset. size() == 0 ) {
            sset. insert( atm. collapsed );
            return sset;
         }
      }

      break;
   }

   case data::tree_array: {
      auto array = data. view_array();

      /* initial set state */
      sset. insert( atm. empty_mset );
      sset = eps_closure( atm, std::move( sset ));

      for( size_t i = 0; i < array. size(); ++ i ) {
         auto sset_at_i = simulate( atm, array. val( i ) );
         atm::stateset new_sset;
         new_sset = set_delta( atm. delta_mset, sset, sset_at_i );
         sset = eps_closure( atm, std::move( new_sset ));
         if( sset. size() == 0 ) {
            sset. insert( atm. collapsed );
            break;
         }
      }

      break;
   }

   default:
      throw std::runtime_error( "simulate(): error: unrecognized data::selector instance\n" );
   }

   sset = eps_closure( atm, std::move( sset ));
   return sset;
}
