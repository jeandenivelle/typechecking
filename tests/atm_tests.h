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
      std::cout << char_a << " : " << nda. data2state_t( char_a ) << '\n';
      std::cout << set_char_a << " : " << nda. data2state_t( set_char_a ) << '\n';

      // test atom prop
      const auto usel_atom = data::tree( data::tree_usel, usel( "atom" ) );
      const auto prop_atom = data::tree( data::tree_tuple, { usel_atom, set_char_a } );
      std::cout << usel_atom << " : " << nda. data2state_t( usel_atom ) << '\n';
      std::cout << prop_atom << " : " << nda. data2state_t( prop_atom ) << '\n';

      // test neg prop
      const auto usel_neg = data::tree( data::tree_usel, usel( "neg" ) );
      const auto prop_neg = data::tree( data::tree_tuple, { usel_neg, prop_atom } );
      std::cout << usel_neg << " : " << nda. data2state_t( usel_neg ) << '\n';
      std::cout << prop_neg << " : " << nda. data2state_t( prop_neg ) << '\n';

      // test imply and equiv props
      const auto usel_imply = data::tree( data::tree_usel, usel( "imply" ) );
      const auto prop_imply = data::tree( data::tree_tuple, { usel_imply, prop_neg, prop_neg } );
      const auto usel_equiv = data::tree( data::tree_usel, usel( "equiv" ) );
      const auto prop_equiv = data::tree( data::tree_tuple, { usel_equiv, prop_neg, prop_neg } );
      std::cout << usel_imply << " : " << nda. data2state_t( usel_imply ) << '\n';
      std::cout << prop_imply << " : " << nda. data2state_t( prop_imply ) << '\n';
      std::cout << usel_equiv << " : " << nda. data2state_t( usel_equiv ) << '\n';
      std::cout << prop_equiv << " : " << nda. data2state_t( prop_equiv ) << '\n';
      
      // test multiset of props
      const auto array_prop = data::tree( data::tree_array, { prop_neg, prop_imply, prop_equiv } );
      std::cout << array_prop << " : " << nda. data2state_t( array_prop ) << '\n';
      
      // test and/or props
      const auto usel_and = data::tree( data::tree_usel, usel( "and" ) );
      const auto usel_or = data::tree( data::tree_usel, usel( "or" ) );
      const auto prop_and = data::tree( data::tree_tuple, { usel_and, array_prop } );
      const auto prop_or = data::tree( data::tree_tuple, { usel_or, array_prop } );
      std::cout << usel_and << " : " << nda. data2state_t( usel_and ) << '\n';
      std::cout << prop_and << " : " << nda. data2state_t( prop_and ) << '\n';
      std::cout << usel_or << " : " << nda. data2state_t( usel_or ) << '\n';
      std::cout << prop_or << " : " << nda. data2state_t( prop_or ) << '\n';

      return 0;  
   }
};

#endif
