#ifndef ATM_NDA
#define ATM_NDA

#include "states.h"
#include "finitefunction.h"
#include "intervalfunction.h"

#include <unordered_set>
#include <iostream>

namespace atm{
   struct nda_t{
      states_t states;
      
      /* trap state */
      state_t trap_state;
      
      /* transition functions for constants of a tag type */
      finitefunction <bool, state_t> bool_transitions;
      finitefunction <char, state_t> char_transitions;
      finitefunction <usel, state_t, usel::hash, usel::equal_to > usel_transitions; 
      
      /* transition fucntion for constants of u64, bigint, and double types */
      intervalfunction <size_t, state_t> u64_transitions;
      intervalfunction <bigint, state_t> bigint_transitions;
      intervalfunction <double, state_t> double_transitions;
      
      /* Empty tuple and multisets states */
      state_t empty_tuple_state;
      state_t empty_multiset_state;

      /* transition function for pairs of states */
      finitefunction <state_pair_t, state_t, state_pair_hash, state_pair_equal_to> tuple_transitions;
      finitefunction <state_pair_t, state_t, state_pair_hash, state_pair_equal_to> multiset_transitions;
   
      nda_t() {
         trap_state = states. get_next_state() ;

         bool_transitions. assign( true, states. get_next_state() ); 
         bool_transitions. assign( false, states. get_next_state() ); 
         
         u64_transitions = intervalfunction <size_t, state_t> ( states. get_next_state() );
         u64_transitions. append( 1, states. get_next_state(), states. get_next_state() );
        
         bigint_transitions = intervalfunction <bigint, state_t> ( states. get_next_state() );
         bigint_transitions. append( 0, states. get_next_state(), states. get_next_state() );
         bigint_transitions. append( 1, states. get_next_state(), states. get_next_state() );
         
         double_transitions = intervalfunction <double, state_t> ( states. get_next_state() );
         double_transitions. append( 0.0, states. get_next_state(), states. get_next_state() );
         double_transitions. append( 1.0, states. get_next_state(), states. get_next_state() );

         empty_tuple_state = states. get_next_state();
         empty_multiset_state = states. get_next_state();
      }
      
      state_t
      data2state_t( const data::tree& d ) const {
         switch( d. sel() ) {
         case data::tree_never:
         case data::tree_unit:
            return trap_state;
         
         case data::tree_bool:
            return bool_transitions( d. view_bool(). b() );

         case data::tree_char:
            return char_transitions( d. view_char(). c() );
            
         case data::tree_usel:
            return usel_transitions( d. view_usel(). s() );
         
         case data::tree_u64:
            return u64_transitions( d. view_u64(). i() );

         case data::tree_bigint:
            return bigint_transitions( d. view_bigint(). i() );

         case data::tree_double:
            return double_transitions( d. view_double(). d() );

         case data::tree_tuple: {
            auto tuple = d. view_tuple();
            auto res = empty_tuple_state;
            for( size_t i = 0; i < tuple. size(); ++i ) {
               auto tmp = data2state_t( tuple. val( i ) );
               res = tuple_transitions( state_pair_t( res, tmp ) );
               if( res == trap_state ) break;
            }
            return res;
         }

         case data::tree_array: {
            auto array = d. view_array();
            auto res = empty_multiset_state;
            for( size_t i = 0; i < array. size(); ++i ) {
               auto tmp = data2state_t( array. val( i ) );
               res = multiset_transitions( state_pair_t( res, tmp ) );
            }
            return res;
         }
 
         default:
            throw std::runtime_error( "atm::nda_t::data2state_t(): error: unrecognizer data::selector instance\n" );
         }
      }

      void print( std::ostream& out ) const {
         out << "Trap state: " << trap_state << "\n";
         
         out << "Transitions for constants of Bool type:\n";
         for( auto entry : bool_transitions ) {
            out << "\t" << entry. first << " --> " << entry. second << "\n";
         }

         out << "Transitions for constants of Char type:\n";
         for( auto entry : char_transitions ) {
            out << "\t" << entry. first << " --> " << entry. second << "\n";
         }
          
         out << "Transitions for constants of Usel type:\n";
         for( auto entry : usel_transitions ) {
            out << "\t" << entry. first << " --> " << entry. second << "\n";
         }

         out << "Transitions for constants of U64 type:\n";
         out << "\tbottom --> " << u64_transitions. bot << '\n';
         for( auto entry : u64_transitions ) {
            out << '\t' << entry. d;
            out << " --> [ " << entry. at << "; " << entry. after << " )\n";
         }
         
         out << "Transitions for constants of Bigint type:\n";
         out << "\tbottom --> " << bigint_transitions. bot << '\n';
         for( auto entry : bigint_transitions ) {
            out << '\t' << entry. d;
            out << " --> [ " << entry. at << "; " << entry. after << " )\n";
         }

         out << "Transitions for constants of Double type:\n";
         out << "\tbottom --> " << double_transitions. bot << '\n';
         for( auto entry : double_transitions ) {
            out << '\t' << entry. d;
            out << " --> [ " << entry. at << "; " << entry. after << " )\n";
         }
         
         out << "Transition for empty multiset states:\n";
         out << "\t{} --> " << empty_multiset_state << '\n';

         out << "Transition for the empty tuples:\n";
         out << "\t() --> " << empty_tuple_state << '\n';

         out << "Transitions tuples of states:\n";
         for( auto entry : tuple_transitions ) {
            out << "\t" << entry. first << " --> " << entry. second << "\n";
         }

         out << "Transitions multiset insertions:\n";
         for( auto entry : multiset_transitions ) {
            out << "\t" << entry. first << " --> " << entry. second << "\n";
         }
      }
   };
   inline std::ostream& operator<< ( std::ostream& out, const std::unordered_set <state_t> set ) {
      out << "{ ";
      for( auto i = set. begin(); i != set. end(); ++i ) {
         if( i != set. begin() ) out << " ,";
         out << *i;
      }
      out << " }";
      return out;
   }
};

#endif
