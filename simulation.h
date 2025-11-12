#ifndef _SIMULATION_
#define _SIMULATION_

#include "data/tree.h"
#include "atm/stateset.h"
#include "atm/simple.h"

atm::stateset eps_close ( const atm::simple&, const atm::stateset );
atm::stateset simulate ( const atm::simple&, const data::tree& );

#endif
