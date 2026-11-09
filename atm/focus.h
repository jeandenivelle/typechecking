
#ifndef ATM_FOCUS_
#define ATM_FOCUS_

// a* is represented by nr = 0, period = 1.
// (aa)* is represented by nr = 0, period = 2.
// a(aa)* is represented by nr = 1, period - 2.
// aaa is represented by nr = 3, period = 0

#include <vector>

#include "simple.h"

namespace atm
{
   struct focus
   {
      state entry;
      state accept;

      std::vector< state > states; 

      focus( state entry, state accept )
         : entry( entry ), accept( accept )
      { }

   };

   focus convert_word( simple& smp, std::vector< state > word );
   
   void merge_with( const focus& other );
   void add_repetition( state s, size_t rep );

}

#endif

