
// Written by Akhmetzhan Kussainov and Hans de Nivelle

#ifndef FLOWGRAPH_VARIABLE_
#define FLOWGRAPH_VARIABLE_

#include <utility> 
#include "util/print.h"

namespace flowgraph
{

   struct variable
   {
      char c; 
      size_t index; 

      variable( ) = delete;
 
      variable( char c, size_t index )
         : c(c), index( index )
      { } 

      void print( std::ostream& out ) const
      {
         out << c << index;
      }

      variable succ( ) const 
      {
         return variable( c, index + 1 );
      }

   };


   inline bool operator == ( variable v1, variable v2 )
   {
      return v1.c == v2.c && v1.index == v2.index;
   }

   inline bool operator != ( variable v1, variable v2 )
   {
      return v1.c != v2.c || v1.index != v2.index;
   }

}

#endif

