
#ifndef ATM_SIMPLE_
#define ATM_SIMPLE_

#include <iostream>
#include <map>
#include <set>

#include "finitefunction.h"
#include "intervalfunction.h"
#include "state.h"
#include "usel.h"
#include "util/bigint.h"

namespace atm 
{
   struct simple
   {

      // Types that have no natural order:

      finitefunction<bool,state> delta_bool;
      finitefunction<usel,state, usel::hash, usel::equal_to> delta_usel;

      // Ordered types:
      
      state delta_unit; 
      intervalfunction< char, state > delta_char;
      intervalfunction< size_t, state > delta_u64;
      intervalfunction< bigint, state > delta_bigint;
      intervalfunction< double, state > delta_double;

      state collapsed;     // The state that forgets absolutely everything. 
      state empty_tup;
      state empty_mset;

      // In both cases, we assume right insertion, so the
      // the first parameter is the tuple of multiset, and
      // the second parameter is the appended or inserted element.

      std::map< state, std::map< state, state, state::less >, state::less >
         delta_tup;

      std::map< state, std::map< state, state, state::less >, state::less >
         delta_mset;

      // We do not store inverses of delta. They can be created when they are
      // needed.

      std::map< state, std::set< state, state::less >, state::less > delta_eps;
         // If epsilon is empty, then the automaton is deterministic. 
    
      std::map< state, state::less, int > special;

      state nextstate;
 
      explicit simple( state nextstate ) noexcept 
         : collapsed( nextstate ++ ),
           empty_tup( nextstate ++ ),
           empty_mset( nextstate ++ ),
           nextstate( nextstate )
      { } 

      state newstate( ) 
         { return nextstate ++ ; }

      void addtuple( const std::vector< state > & tup, state goal );
      void addforall( state q, state goal );

      void print( std::ostream& out ) const; 
   };

}

#endif

