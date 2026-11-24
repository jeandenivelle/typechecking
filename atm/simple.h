
#ifndef ATM_SIMPLE_
#define ATM_SIMPLE_

#include <iostream>
#include <map>
#include <set>
#include <utility>

#include "finfunc.h"
#include "stepfunc.h"
#include "state.h"
#include "usel.h"
#include "util/bigint.h"

namespace atm 
{
   struct simple
   {
      using bool_func = stepfunc< bool, state > ; 
      using char_func = stepfunc< char, state > ; 
      using sel_func = finfunc< usel, state, usel::hash, usel::equal_to > ;
      using u64_func = stepfunc< size_t, state > ;
      using integer_func = stepfunc< bigint, state > ;

      std::vector< state > delta_unit; 
      std::vector< bool_func > delta_bool;
      std::vector< char_func > delta_char;
      std::vector< sel_func > delta_sel;
      std::vector< u64_func > delta_u64;
      std::vector< integer_func > delta_integer;
      std::vector< state > delta_double;

      state trap;   // No one has ever escaped from this state! 

      state empty_tuple;
      state empty_set;

      // In both cases, we assume right insertion, so that the
      // the first parameter is the state of the tuple/multiset, and
      // the second parameter is the appended or inserted element.
      // I am expecting that multimap is more efficient when the
      // automaton is deterministic.

      std::multimap< std::pair< state, state >, state, 
                     state::pair_less > delta_tuple;

      std::multimap< std::pair< state, state >, state, 
                     state::pair_less > delta_set;

      // We do not store inverses of delta. Inverse indices
      // can be created when they are needed.

      std::multimap< state, state, state::less > delta_epsilon;
    
      std::map< state, std::string, state::less > comments;
         // One can attach comments to states. It's not obligatory.

      state freestate;
 
      explicit simple( state firststate = state( )) noexcept
         : trap( firststate ),
           empty_tuple( firststate + 1 ),
           empty_set( firststate + 2 ),
           freestate( firststate + 3 ) 
      { } 

      simple( simple&& ) noexcept = default;
      simple& operator = ( simple&& ) = default;

      state create_states( size_t nr ) 
         { return std::exchange( freestate, freestate + nr ); }

      void comment( state s, const std::string& bla ) 
         { comments. insert( std::pair( s, bla )); }

      void print( std::ostream& out ) const; 

      bool isdeterministic( ) const;
   };

}

#endif

