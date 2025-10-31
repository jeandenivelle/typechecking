#include "simulation.h"

#include <stdexcept>

atm::stateset simulation::operator() ( const data::tree& d ) {
   atm::stateset ss;

   switch( d. sel() ) {
   case data::tree_never:
   case data::tree_unit:
      ss. insert( atm. collapsed );
      break;
   
   case data::tree_bool:
      ss. insert( 
         atm. delta_bool( 
            d. view_bool(). b() ) );
      break;

   case data::tree_char:
      ss. insert(
         atm. delta_char( 
            d. view_char(). c() ) );
      break;
      
   case data::tree_usel:
      ss. insert(
         atm. delta_usel( 
            d. view_usel(). s() ) );
      break;
   
   case data::tree_u64:
      ss. insert(
         atm. delta_u64(
            d. view_u64(). i() ) );
      break;

   case data::tree_bigint:
      ss. insert(
         atm. delta_bigint( 
            d. view_bigint(). i() ) );
      break;

   case data::tree_double:
      ss. insert(
         atm. delta_double(
            d. view_double(). d() ) );
      break;

   case data::tree_tuple: {
      auto tuple = d. view_tuple();
      ss. insert( atm. empty_tup );
      atm::stateset ss_new;
      
      for( size_t i = 0; i < tuple. size(); ++i ) { 
         auto _ss = (*this)( tuple. val( i ) );
         for( auto s1 : ss ) {
            for( auto s2 : _ss ) {
               if( s2 == atm. collapsed )
                  continue;

               auto it1 = atm. delta_tup. find( s1 );
               if( it1 == atm. delta_tup. cend() )
                  continue;

               auto it2 = it1-> second. find( s2 );
               if( it2 == it1-> second. cend() )
                  continue;

               auto it3 = atm. delta_eps. find( it2-> second );
               if( it3 == atm. delta_eps. cend() ) {
                  ss_new. insert( it2-> second );
               } else {
                  ss_new. repr. insert( it3-> second. cbegin(), it3-> second. cend() );
               }
            }
         }
         
         if( ss_new. empty() ) {
            ss_new. insert( atm. collapsed );
            ss = ss_new;
            break;
         }

         ss = ss_new;
         ss_new = atm::stateset();
      }

      break;
   }

   case data::tree_array: {
      auto array = d. view_array();
      ss. insert( atm. empty_mset );
      atm::stateset ss_new;

      for( size_t i = 0; i < array. size(); ++ i ) {
         auto _ss = (*this)( array. val( i ) );

         for( auto s1 : ss ) {
            for( auto s2 : _ss ) {
               if( s2 == atm. collapsed )
                  continue;

               auto it1 = atm. delta_mset. find( s1 );
               if( it1 == atm. delta_mset. cend() )
                  continue;

               auto it2 = it1-> second. find( s2 );
               if( it2 == it1-> second. cend() )
                  continue;

               auto it3 = atm. delta_eps. find( it2-> second );
               if( it3 == atm. delta_eps. cend() ) {
                  ss_new. insert( it2-> second );
               } else {
                  ss_new. repr. insert( it3-> second. cbegin(), it3-> second. cend() );
               }
            }
         }
         
         if( ss_new. empty() ) {
            ss_new. insert( atm. collapsed );
            ss = ss_new;
            break;
         }

         ss = ss_new;
         ss_new = atm::stateset();
      }

      break;
   }

   default:
      throw std::runtime_error( "simulate(): error: unrecognizer data::selector instance\n" );
   }

   return ss;
}
