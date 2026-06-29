
#ifndef TESTS_
#define TESTS_

#include "fieldmap.h"
#include "regexp/defmap.h"

#include "intermediate/function.h"

namespace tests
{
   void add_nat( regexp::defmap& prp, fieldmap& flds );
   void add_fol( regexp::defmap& prp, fieldmap& flds );

   intermediate::function mixing( );
   intermediate::function arrayconv( ); 
   intermediate::function repeated( );

   // atm::simple prop( );
      // Produce a non-deterministic automaton that
      // recognizes propositional formulas.

    

}

#endif

