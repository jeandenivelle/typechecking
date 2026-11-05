
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
      using char_func = partition< char, state > ; 
      using usel_func = finfunc< usel, state, usel::hash, usel::equal_to > ;
      using u64_func = partition< size_t, state > ;

      std::vector< state > delta_unit; 
      std::vector< partition< bool, state >> delta_bool;
      std::vector< char_func > delta_char;
      std::vector< usel_func > delta_usel;
      std::vector< u64_func > delta_u64;
      std::vector< partition< bigint, state >> delta_integer;
      std::vector< state > delta_double;

      state trap;      // No escape from this state! 

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

      state newstate( ) 
         { return freestate ++ ; }

      void comment( state s, const std::string& bla ) 
         { comments. insert( std::pair( s, bla )); }

      char_func& add_delta_char( state def )
      {
         delta_char. push_back( def );
         return delta_char. back( );
      }

      usel_func& add_delta_usel( state def )
      {
         delta_usel. push_back( def ); 
         return delta_usel. back( );
      }

      u64_func& add_delta_u64( state def )
      {
         delta_u64. push_back( def ); 
         return delta_u64. back( );
      }


      void addtuple( const std::vector< state > & tuple, state goal );

      void print( std::ostream& out ) const; 

   };

}

#endif

