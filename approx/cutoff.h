
#ifndef APPROX_CUTOFF_
#define APPROX_CUTOFF_

#include <iostream>
#include "util/print.h"

namespace approx
{
 
   struct cutoff
   {
      size_t index;

      cutoff( ) noexcept 
         : index(0)
      { } 

      cutoff& operator ++ ( ) 
         { ++ index; return *this; }

      cutoff operator ++ ( int )
         { auto res = *this; ++ index; return res; }

      cutoff next( ) const
         { auto res = *this; ++ res. index; return res; }

      void print( std::ostream& out ) const
         { out << '$' << index; }

      struct equal_to
      {
         bool operator( ) ( cutoff ct1, cutoff ct2 ) const
            { return ct1. index == ct2. index; } 
      };

      struct hash
      {
         size_t operator( ) ( cutoff ct ) const
            { return ct. index; }
      };

   };

}

#endif


