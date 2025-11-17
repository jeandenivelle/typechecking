
#ifndef SIMULATION_
#define SIMULATION_

#include "data/tree.h"
#include "atm/stateset.h"
#include "atm/simple.h"

namespace atm {
   stateset eps_closure( const simple&, stateset );
   stateset simulate( const simple&, const data::tree& );
}

#endif
