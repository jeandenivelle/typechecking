#ifndef ATM_TESTS
#define ATM_TESTS

#include "data/tree.h"

#include "atm/states.h"
#include "atm/nda.h"

#include <iostream>

namespace atm {
   int test() {
      nda_t nda;
   
      // define transition for a char 'a' 
      nda. char_transitions. assign( 'a', nda. states. get_next_state() );
      
      // define transitions for usel type
      nda. usel_transitions. assign( usel( "atom" ), nda. states. get_next_state() );
      nda. usel_transitions. assign( usel( "neg" ), nda. states. get_next_state() );
      nda. usel_transitions. assign( usel( "imply" ), nda. states. get_next_state() );
      nda. usel_transitions. assign( usel( "equiv" ), nda. states. get_next_state() );
      nda. usel_transitions. assign( usel( "or" ), nda. states. get_next_state() );
      nda. usel_transitions. assign( usel( "and" ), nda. states. get_next_state() );

      // define transitions for multiset of char
      const auto empty_char_state = nda. states. get_next_state();
      const auto forall_char_state = nda. states. get_next_state();
      nda. empty_multiset_states. insert( empty_char_state );
      nda. multiset_transitions. assign( 
         state_pair_t{
            empty_char_state,
            nda. char_transitions( 'a' ),
         },
         forall_char_state
      );
      nda. multiset_transitions. assign( 
         state_pair_t{
            forall_char_state,
            nda. char_transitions( 'a' ),
         },
         forall_char_state
      );
  
      // define transitions for atom prop
      const auto prop_state = nda. states. get_next_state();
      auto tmp_state = nda. states. get_next_state();
      nda. tuple_transitions. assign(
         state_pair_t(
            nda. empty_tuple_state,
            nda. usel_transitions( usel( "atom" ) ) 
         ),
         tmp_state
      );
      nda. tuple_transitions. assign(
         state_pair_t(
            tmp_state,
            forall_char_state
         ),
         prop_state
      );

      // define transitions for neg prop
      tmp_state = nda. states. get_next_state();
      nda. tuple_transitions. assign(
         state_pair_t(
            nda. empty_tuple_state,
            nda. usel_transitions( usel( "neg" ) ) 
         ),
         tmp_state
      );
      nda. tuple_transitions. assign(
         state_pair_t(
            tmp_state,
            prop_state
         ),
         prop_state
      );

      // define transitions for imply and equiv
      tmp_state = nda. states. get_next_state();
      nda. tuple_transitions. assign(
         state_pair_t(
            nda. empty_tuple_state,
            nda. usel_transitions( usel( "imply" ) ) 
         ),
         tmp_state
      );
      nda. tuple_transitions. assign(
         state_pair_t(
            nda. empty_tuple_state,
            nda. usel_transitions( usel( "equiv" ) ) 
         ),
         tmp_state
      );
      auto tmp_state_2 = nda. states. get_next_state();
      nda. tuple_transitions. assign(
         state_pair_t(
            tmp_state,
            prop_state
         ),
         tmp_state_2
      );
      nda. tuple_transitions. assign(
         state_pair_t(
            tmp_state_2,
            prop_state
         ),
         prop_state
      );

      // define transitions for multiset of prop
      const auto empty_prop_state = nda. states. get_next_state();
      const auto forall_prop_state = nda. states. get_next_state();
      nda. empty_multiset_states. insert( empty_prop_state );
      nda. multiset_transitions. assign(
         state_pair_t{
            empty_prop_state,
            prop_state,
         },
         forall_prop_state
      );
      nda. multiset_transitions. assign( 
         state_pair_t{
            forall_prop_state,
            prop_state,
         },
         forall_prop_state
      );

      // define transitions for or/and props
      tmp_state = nda. states. get_next_state();
      nda. tuple_transitions. assign(
         state_pair_t(
            nda. empty_tuple_state,
            nda. usel_transitions( usel( "and" ) ) 
         ),
         tmp_state
      );
      nda. tuple_transitions. assign(
         state_pair_t(
            nda. empty_tuple_state,
            nda. usel_transitions( usel( "or" ) ) 
         ),
         tmp_state
      );
      nda. tuple_transitions. assign(
         state_pair_t(
            tmp_state,
            forall_prop_state
         ),
         prop_state
      );

      std::cout << nda << '\n';

      // test multiset of char
      const auto char_a = data::tree( data::tree_char, 'a' );
      const auto set_char_a = data::tree( data::tree_array, { char_a, char_a, char_a } ); 
      std::cout << nda. data2state_t( char_a ) << '\n';
      std::cout << nda. data2state_t( set_char_a ) << '\n';

      // test atom prop
      const auto usel_atom = data::tree( data::tree_usel, usel( "atom" ) );
      const auto prop_atom = data::tree( data::tree_tuple, { usel_atom, set_char_a });
      std::cout << nda. data2state_t( usel_atom ) << '\n';
      std::cout << nda. data2state_t( prop_atom ) << '\n';
      

/*
      // test the automaton
      using namespace data;
      {
         tree d_bool( tree_bool, true );
         std::cout << d_bool << " ==> " << nda. Q_A( d_bool ) << "\n";
         
         tree d_char( tree_char, 'a' );
         std::cout << d_char << " ==> " << nda. Q_A( d_char ) << "\n";
         
         tree d_usel_atom( tree_usel, usel( "atom" ) );
         tree d_usel_neg( tree_usel, usel( "neg" ) );
         tree d_usel_equiv( tree_usel, usel( "equiv" ) );
         tree d_usel_imply( tree_usel, usel( "imply" ) );
         tree d_usel_or( tree_usel, usel( "or" ) );
         tree d_usel_and( tree_usel, usel( "and" ) );
         std::cout << d_usel_atom << " ==> " << nda. Q_A( d_usel_atom ) << "\n";
         std::cout << d_usel_neg << " ==> " << nda. Q_A( d_usel_neg ) << "\n";
         std::cout << d_usel_imply << " ==> " << nda. Q_A( d_usel_imply ) << "\n";
         std::cout << d_usel_equiv << " ==> " << nda. Q_A( d_usel_equiv ) << "\n";
         std::cout << d_usel_or << " ==> " << nda. Q_A( d_usel_or ) << "\n";
         std::cout << d_usel_and << " ==> " << nda. Q_A( d_usel_and ) << "\n";
         
         tree d_u63_0( tree_u64, (size_t) 0 );
         tree d_u63_1( tree_u64, (size_t) 1 );
         tree d_u63_11( tree_u64, (size_t) 11 );
         std::cout << d_u63_0 << " ==> " << nda. Q_A( d_u64_0 ) << "\n";
         std::cout << d_u63_1 << " ==> " << nda. Q_A( d_u64_1 ) << "\n";
         std::cout << d_u63_11 << " ==> " << nda. Q_A( d_u64_11 ) << "\n";

         tree d_bigint_min( tree_bigint, bigint( -1112 ) );
         tree d_bigint_-1( tree_bigint,  bigint( 0 ) );
         tree d_bigint_max( tree_bigint,  bigint( 1110 ) );
         std::cout << d_bigint_min << " ==> " << nda. Q_A( d_bigint_min ) << "\n";
         std::cout << d_bigint_-1 << " ==> " << nda. Q_A( d_bigint_0 ) << "\n";
         std::cout << d_bigint_max << " ==> " << nda. Q_A( d_bigint_max ) << "\n";

         tree d_array_char( tree_array, { d_char, d_char, d_char } );
         tree d_array( tree_array, { d_char, d_bigint_-1, d_u64_0 } );
         std::cout << d_array_char << " ==> " << nda. Q_A( d_array_char ) << "\n";
         std::cout << d_array << " ==> " << nda. Q_A( d_array ) << "\n";

         tree d_atom( tree_tuple, { d_usel_atom, d_array_char } );
         std::cout << d_atom << " ==> " << nda. Q_A( d_atom ) << "\n";

         tree d_neg( tree_tuple, { d_usel_neg, d_atom } );
         std::cout << d_neg << " ==> " << nda. Q_A( d_neg ) << "\n";	

         tree d_imply0( tree_tuple, { d_usel_imply, d_atom, d_atom } );
         tree d_imply1( tree_tuple, { d_usel_imply, d_atom, d_char } );
         std::cout << d_imply0 << " ==> " << nda. Q_A( d_imply1 ) << "\n";
         std::cout << d_imply1 << " ==> " << nda. Q_A( d_imply2 ) << "\n";
         
         tree d_equiv0( tree_tuple, { d_usel_equiv, d_atom, d_atom } );
         tree d_equiv1( tree_tuple, { d_usel_equiv, d_atom, d_char } );
         std::cout << d_equiv0 << " ==> " << nda. Q_A( d_equiv1 ) << "\n";
         std::cout << d_equiv1 << " ==> " << nda. Q_A( d_equiv2 ) << "\n";

         tree d_prop_array( tree_array, { d_atom, d_atom, d_atom, d_atom } );
         std::cout << d_prop_array << " ==> " << nda. Q_A( d_prop_array ) << "\n";
         
         tree d_or0( tree_tuple, { d_usel_or, d_prop_array } );
         tree d_or1( tree_tuple, { d_usel_or, d_array_char } );
         std::cout << d_or0 << " ==> " << nda. Q_A( d_or1 ) << "\n";
         std::cout << d_or1 << " ==> " << nda. Q_A( d_or2 ) << "\n";
         
         tree d_and0( tree_tuple, { d_usel_and, d_prop_array } );
         tree d_and1( tree_tuple, { d_usel_and, d_array_char } );
         std::cout << d_and0 << " ==> " << nda. Q_A( d_and1 ) << "\n";
         std::cout << d_and1 << " ==> " << nda. Q_A( d_and2 ) << "\n";
      }
*/

      return 1;  
   }
};

#endif
