
#ifndef REGEXP_ALGORITHMS_
#define REGEXP_ALGORITHMS_

#include "expr.h"
#include "exprtype.h"
#include "defmap.h"


namespace regexp
{

   // This was a a type checking procedure for regexp, but I think 
   // it is longer needed. 

   void collect( const expr& e,
                 identifier::set& defs, size_t& c );
      // Main purpose is to get the defined identifiers used in e.

   identifier::map< identifier::set > dependencymap( const defmap& defs ); 

   exprtype join( exprtype tp1, exprtype tp2 );

   exprtype gettype( const defmap& defs, const expr& e );
   bool checktypes( defmap& defs );  
}

#endif

