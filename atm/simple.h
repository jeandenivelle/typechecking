
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

      std::vector< state > delta_unit; 
      std::vector< partition< bool, state >> delta_bool;
      std::vector< partition< char, state >> delta_char;
      std::vector< finfunc< usel, state, usel::hash, usel::equal_to >>
         delta_usel;
      std::vector< partition< size_t, state >> delta_u64;
      std::vector< partition< bigint, state >> delta_integer;
      std::vector< state > delta_double;

      state collapsed;     // The state that forgets absolutely everything. 

      state empty_tuple;
      state empty_set;

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
    
      std::map< state, state::less, std::string > comments;
         // One can attach comments to states. It's not obligatory.

      state nextstate;
 
      explicit simple( state firststate = state( )) noexcept
         : nextstate( firststate )  
      { 
         collapsed = nextstate ++ ;
         empty_tuple = nextstate ++ ;
         empty_set = nextstate ++ ;  
      } 

      state createstate( ) 
         { return nextstate ++ ; }

      
      void addtuple( const std::vector< state > & tup, state goal );

      void print( std::ostream& out ) const; 

   };

}

#endif

