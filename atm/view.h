
// A selected sub part of a simple automaton.

#ifndef ATM_VIEW_
#define ATM_VIEW_

// a* is represented by nr = 0, period = 1.
// (aa)* is represented by nr = 0, period = 2.
// a(aa)* is represented by nr = 1, period - 2.
// aaa is represented by nr = 3, period = 0

#include <vector>

#include "simple.h"

namespace atm
{
   struct view
   {
      state entry;
      state exit;

      std::vector< state > states; 

      view( state entry, state exit )
         : entry( entry ), exit( exit )
      { }

      void print( std::ostream& out ) const; 
   };

   view convert_word( simple& smp, std::vector< state > word );
   
   void merge_with( const view& other );
   void add_repetition( state s, size_t rep );

}

#endif

