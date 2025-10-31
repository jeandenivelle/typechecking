#ifndef _SIMULATION_
#define _SIMULATION_

#include "data/tree.h"
#include "atm/stateset.h"
#include "atm/simple.h"

struct simulation {
   const atm::simple atm;
   
   simulation() = delete;
   simulation( const atm::simple& atm ):
      atm( atm ) {}

   atm::stateset operator() ( const data::tree& );
};

#endif
