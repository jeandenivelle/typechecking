
#ifndef REGEXP_ALGORITHMS_
#define REGEXP_ALGORITHMS_

#include "expr.h"
#include "exprtype.h"

namespace regexp
{

   void collect( const expr& e,
                 identifier::set& defs, size_t& c );
      // Main purpose is to get the definitions used in e.
 
   exprtype typecheck( const expr& e, 
                   identifier::map< exprtype >  defs );

   identifier::map< identifier::set > 
   dependencies( const identifier::map< expr > & defs ); 
}

#endif

