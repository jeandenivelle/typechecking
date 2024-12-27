
#ifndef APPROX_CUTOFF_
#define APPROX_CUTOFF_

#include <iostream>
#include "util/print.h"

namespace approx
{
 
   struct approximator
   {
      size_t index;

      approximator( ) noexcept 
         : index(0)
      { } 

      approximator& operator ++ ( ) 
         { ++ index; return *this; }

      approximator operator ++ ( int )
         { auto res = *this; ++ index; return res; }

      approximator next( ) const
         { auto res = *this; ++ res. index; return res; }

      void print( std::ostream& out ) const
         { out << '$' << index; }

      struct equal_to
      {
         bool operator( ) ( approximator ct1, approximator ct2 ) const
            { return ct1. index == ct2. index; } 
      };

      struct hash
      {
         size_t operator( ) ( approximator ct ) const
            { return ct. index; }
      };

   };

   inline bool operator == ( approximator a, approximator b )
   { return a. index == b. index; }

   inline bool operator != ( approximator a, approximator b )
   { return a. index != b. index; }


}

#endif


