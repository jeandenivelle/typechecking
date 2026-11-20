
#ifndef REGEXP_ALGORITHMS_
#define REGEXP_ALGORITHMS_

#include "expr.h"
#include "defmap.h"

namespace regexp
{

   // This was a type checking procedure for regexp, but I think 
   // it is longer needed, because the conversion operators
   // check types during conversion. 

   void collect( const expr& e,
                 identifier::set& defs, size_t& c );
      // Main purpose is to get the defined identifiers used in e.

   identifier::map< identifier::set > dependencymap( const defmap& defs ); 
}

#endif

