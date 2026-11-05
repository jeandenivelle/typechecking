
#ifndef ATM_ALGORITHMS_
#define ATM_ALGORITHMS_

#include "data/tree.h"
#include "atm/stateset.h"
#include "atm/simple.h"

namespace atm 
{
   void close_eps( const simple& smp, stateset& s );

   stateset apply_tuple( const simple& smp, 
                         stateset tuple, stateset single );

   stateset apply_set( const simple& smp, 
                       const stateset& set, const stateset& element );
      // We don't do the epsilon closure.

   stateset run( const simple& smp, const data::tree& tr );
}

#endif

