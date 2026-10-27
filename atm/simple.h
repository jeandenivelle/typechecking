
#ifndef ATM_SIMPLE_
#define ATM_SIMPLE_

#include <iostream>
#include <map>
#include <set>

#include "finfunc.h"
#include "partition.h"
#include "state.h"
#include "usel.h"
#include "util/bigint.h"

namespace atm 
{
   struct simple
   {

      state delta_unit; 

      state delta_bool_false;
      state delta_bool_true; 
      partition< char, state > delta_char;
      finfunc< usel, state, usel::hash, usel::equal_to > delta_usel;
      partition< size_t, state > delta_u64;
      partition< bigint, state > delta_integer;
      state delta_double;

      state collapsed;     // The state that forgets absolutely everything. 

      state empty_tup;
      state empty_mset;

      // In both cases, we assume right insertion, so that the
      // the first parameter is the state of the tuple/multiset, and
      // the second parameter is the appended or inserted element.

      std::map< state, std::map< state, state, state::less >, state::less >
         delta_tup;

      std::map< state, std::map< state, state, state::less >, state::less >
         delta_mset;

      // We do not store inverses of delta. Inverse indices
      // can be created when they are needed.

      std::map< state, std::set< state, state::less >, state::less > delta_eps;
         // If epsilon is empty, then the automaton is deterministic. 
    
      std::map< state, state::less, int > special;

      state nextstate;
 
      explicit simple( state nextstate ) noexcept 
         : delta_char( state( )), 
           delta_usel( state( )),  
           delta_u64( state( )),
           delta_integer( state( ))  
      { } 

      state newstate( ) 
         { return nextstate ++ ; }

      void addtuple( const std::vector< state > & tup, state goal );

      void print( std::ostream& out ) const; 
   };

}

#endif

