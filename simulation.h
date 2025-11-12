
#ifndef SIMULATION_
#define SIMULATION_

#include "data/tree.h"
#include "atm/stateset.h"
#include "atm/simple.h"

atm::stateset eps_closure( const atm::simple&, atm::stateset );
atm::stateset simulate( const atm::simple&, const data::tree& );

#endif
