#include "simulation.h"

#include <stdexcept>

atm::state_t simulation::operator() ( const data::tree& d ) {
   switch( d. sel() ) {
   case data::tree_never:
   case data::tree_unit:
      return atm. trap_state;
   
   case data::tree_bool:
      return atm. bool_transitions( d. view_bool(). b() );

   case data::tree_char:
      return atm. char_transitions( d. view_char(). c() );
      
   case data::tree_usel:
      return atm. usel_transitions( d. view_usel(). s() );
   
   case data::tree_u64:
      return atm. u64_transitions( d. view_u64(). i() );

   case data::tree_bigint:
      return atm. bigint_transitions( d. view_bigint(). i() );

   case data::tree_double:
      return atm. double_transitions( d. view_double(). d() );

   case data::tree_tuple: {
      auto tuple = d. view_tuple();
      auto res = atm. empty_tuple_state;
      for( size_t i = 0; i < tuple. size(); ++i ) {
         auto tmp = (*this)( tuple. val( i ) );
         res = atm. tuple_transitions( atm::state_pair_t( res, tmp ) );
         if( res == atm. trap_state ) break;
      }
      return res;
   }

   case data::tree_array: {
      auto array = d. view_array();
      auto res = atm. empty_multiset_state;
      for( size_t i = 0; i < array. size(); ++i ) {
         auto tmp = (*this)( array. val( i ) );
         res = atm. multiset_transitions( atm::state_pair_t( res, tmp ) );
      }
      return res;
   }

   default:
      throw std::runtime_error( "simulate(): error: unrecognizer data::selector instance\n" );
   }
}
