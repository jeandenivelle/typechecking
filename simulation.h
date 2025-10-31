#ifndef _SIMULATION_
#define _SIMULATION_

#include "data/tree.h"
#include "atm/states.h"
#include "atm/automaton.h"

struct simulation {
   const atm::automaton atm;
   
   simulation() = delete;
   simulation( const atm::automaton& atm ):
      atm( atm ) {}

   atm::state_t operator() ( const data::tree& );
};

#endif
