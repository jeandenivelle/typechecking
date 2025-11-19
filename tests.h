
#ifndef TESTS_
#define TESTS_

#include "atm/simple.h"
#include "atm/statemap.h"

namespace tests
{
   atm::simple add_nat();
   void sim_nat();

   void gen_prop( atm::simple&, atm::statemap& );
      // Produce a non-deterministic automaton that
      // recognizes propositional formulas.
   void sim_prop();
}

#endif

