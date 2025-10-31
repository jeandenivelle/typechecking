#ifndef ATM_NDA
#define ATM_NDA

#include "states.h"
#include "finitefunction.h"
#include "intervalfunction.h"

#include <unordered_set>
#include <iostream>

namespace atm{
   struct automaton{
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
   
      automaton() {
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
