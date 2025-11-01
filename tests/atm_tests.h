#ifndef ATM_TESTS
#define ATM_TESTS

#include "data/tree.h"

#include "atm/states.h"
#include "atm/automaton.h"

#include "simulation.h"

#include <iostream>

#include "atm/state.h"
#include "atm/stateset.h"
#include "atm/statemap.h"
#include "atm/simple.h"

namespace atm {
   int test_simple() {
      return 0;
   }

   int test() {
      automaton atm;
   
      // define transition for a char 'a' 
      atm. char_transitions. assign( 'a', atm. states. get_next_state() );
      
      // define transitions for usel type
      atm. usel_transitions. assign( usel( "atom" ), atm. states. get_next_state() );
      atm. usel_transitions. assign( usel( "neg" ), atm. states. get_next_state() );
      atm. usel_transitions. assign( usel( "imply" ), atm. states. get_next_state() );
      atm. usel_transitions. assign( usel( "equiv" ), atm. states. get_next_state() );
      atm. usel_transitions. assign( usel( "or" ), atm. states. get_next_state() );
      atm. usel_transitions. assign( usel( "and" ), atm. states. get_next_state() );

      // define transitions for multiset of char
      const auto forall_char_state = atm. states. get_next_state();
      atm. multiset_transitions. assign( 
         state_pair_t{
            atm. empty_multiset_state,
            atm. char_transitions( 'a' ),
         },
         forall_char_state
      );
      atm. multiset_transitions. assign( 
         state_pair_t{
            forall_char_state,
            atm. char_transitions( 'a' ),
         },
         forall_char_state
      );
  
      // define transitions for atom prop
      const auto prop_state = atm. states. get_next_state();
      auto tmp_state = atm. states. get_next_state();
      atm. tuple_transitions. assign(
         state_pair_t(
            atm. empty_tuple_state,
            atm. usel_transitions( usel( "atom" ) ) 
         ),
         tmp_state
      );
      atm. tuple_transitions. assign(
         state_pair_t(
            tmp_state,
            forall_char_state
         ),
         prop_state
      );

      // define transitions for neg prop
      tmp_state = atm. states. get_next_state();
      atm. tuple_transitions. assign(
         state_pair_t(
            atm. empty_tuple_state,
            atm. usel_transitions( usel( "neg" ) ) 
         ),
         tmp_state
      );
      atm. tuple_transitions. assign(
         state_pair_t(
            tmp_state,
            prop_state
         ),
         prop_state
      );

      // define transitions for imply and equiv
      tmp_state = atm. states. get_next_state();
      atm. tuple_transitions. assign(
         state_pair_t(
            atm. empty_tuple_state,
            atm. usel_transitions( usel( "imply" ) ) 
         ),
         tmp_state
      );
      atm. tuple_transitions. assign(
         state_pair_t(
            atm. empty_tuple_state,
            atm. usel_transitions( usel( "equiv" ) ) 
         ),
         tmp_state
      );
      auto tmp_state_2 = atm. states. get_next_state();
      atm. tuple_transitions. assign(
         state_pair_t(
            tmp_state,
            prop_state
         ),
         tmp_state_2
      );
      atm. tuple_transitions. assign(
         state_pair_t(
            tmp_state_2,
            prop_state
         ),
         prop_state
      );

      // define transitions for multiset of prop
      const auto forall_prop_state = atm. states. get_next_state();
      atm. multiset_transitions. assign(
         state_pair_t{
            atm. empty_multiset_state,
            prop_state,
         },
         forall_prop_state
      );
      atm. multiset_transitions. assign( 
         state_pair_t{
            forall_prop_state,
            prop_state,
         },
         forall_prop_state
      );

      // define transitions for or/and props
      tmp_state = atm. states. get_next_state();
      atm. tuple_transitions. assign(
         state_pair_t(
            atm. empty_tuple_state,
            atm. usel_transitions( usel( "and" ) ) 
         ),
         tmp_state
      );
      atm. tuple_transitions. assign(
         state_pair_t(
            atm. empty_tuple_state,
            atm. usel_transitions( usel( "or" ) ) 
         ),
         tmp_state
      );
      atm. tuple_transitions. assign(
         state_pair_t(
            tmp_state,
            forall_prop_state
         ),
         prop_state
      );

      std::cout << atm << '\n';
      auto sim = simulation( atm );
      
      // test U64
      const auto u64_a = data::tree( data::tree_u64, (size_t) 0 );
      const auto u64_b = data::tree( data::tree_u64, (size_t) 1 );
      std::cout << u64_a << " : " << sim( u64_a ) << '\n';
      std::cout << u64_b << " : " << sim( u64_b ) << '\n';

      // test Bigint
      const auto bigint_a = data::tree( data::tree_bigint, bigint( -1 ) );
      const auto bigint_b = data::tree( data::tree_bigint, bigint( 0 ) ); 
      const auto bigint_c = data::tree( data::tree_bigint, bigint( 1 ) ); 
      std::cout << bigint_a << " : " << sim( bigint_a ) << '\n';
      std::cout << bigint_b << " : " << sim( bigint_b ) << '\n';
      std::cout << bigint_c << " : " << sim( bigint_c ) << '\n';

      // test Double
      const auto double_a = data::tree( data::tree_double, -1.5 );
      const auto double_b = data::tree( data::tree_double, 0.0 );
      const auto double_c = data::tree( data::tree_double, 1.5 );
      std::cout << double_a << " : " << sim( double_a ) << '\n';
      std::cout << double_b << " : " << sim( double_b ) << '\n';
      std::cout << double_c << " : " << sim( double_c ) << '\n';

      // test multiset of char
      const auto char_a = data::tree( data::tree_char, 'a' );
      const auto set_char_a = data::tree( data::tree_array, { char_a, char_a, char_a } ); 
      std::cout << char_a << " : " << sim( char_a ) << '\n';
      std::cout << set_char_a << " : " << sim( set_char_a ) << '\n';

      // test atom prop
      const auto usel_atom = data::tree( data::tree_usel, usel( "atom" ) );
      const auto prop_atom = data::tree( data::tree_tuple, { usel_atom, set_char_a } );
      std::cout << usel_atom << " : " << sim( usel_atom ) << '\n';
      std::cout << prop_atom << " : " << sim( prop_atom ) << '\n';

      // test neg prop
      const auto usel_neg = data::tree( data::tree_usel, usel( "neg" ) );
      const auto prop_neg = data::tree( data::tree_tuple, { usel_neg, prop_atom } );
      std::cout << usel_neg << " : " << sim( usel_neg ) << '\n';
      std::cout << prop_neg << " : " << sim( prop_neg ) << '\n';

      // test imply and equiv props
      const auto usel_imply = data::tree( data::tree_usel, usel( "imply" ) );
      const auto prop_imply = data::tree( data::tree_tuple, { usel_imply, prop_neg, prop_neg } );
      const auto usel_equiv = data::tree( data::tree_usel, usel( "equiv" ) );
      const auto prop_equiv = data::tree( data::tree_tuple, { usel_equiv, prop_neg, prop_neg } );
      std::cout << usel_imply << " : " << sim( usel_imply ) << '\n';
      std::cout << prop_imply << " : " << sim( prop_imply ) << '\n';
      std::cout << usel_equiv << " : " << sim( usel_equiv ) << '\n';
      std::cout << prop_equiv << " : " << sim( prop_equiv ) << '\n';
      
      // test multiset of props
      const auto array_prop = data::tree( data::tree_array, { prop_neg, prop_imply, prop_equiv } );
      std::cout << array_prop << " : " << sim( array_prop ) << '\n';
      
      // test and/or props
      const auto usel_and = data::tree( data::tree_usel, usel( "and" ) );
      const auto usel_or = data::tree( data::tree_usel, usel( "or" ) );
      const auto prop_and = data::tree( data::tree_tuple, { usel_and, array_prop } );
      const auto prop_or = data::tree( data::tree_tuple, { usel_or, array_prop } );
      std::cout << usel_and << " : " << sim( usel_and ) << '\n';
      std::cout << prop_and << " : " << sim( prop_and ) << '\n';
      std::cout << usel_or << " : " << sim( usel_or ) << '\n';
      std::cout << prop_or << " : " << sim( prop_or ) << '\n';

      return 0;  
   }
};

#endif
