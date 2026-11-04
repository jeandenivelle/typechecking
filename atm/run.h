
#ifndef TYPECHECKING_RUN_
#define TYPECHECKING_RUN_

#include "data/tree.h"
#include "atm/stateset.h"
#include "atm/simple.h"

namespace atm 
{
   stateset eps_closure( const simple&, stateset );

   stateset run( const simple&, const data::tree& );
}

#endif

