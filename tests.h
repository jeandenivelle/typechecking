
#ifndef TESTS_
#define TESTS_

#include "regexp/defmap.h"
#include "data/tree.h"
#include "atm/simple.h"
#include "intermediate/function.h"
#include "interpreter/program.h"

namespace tests
{
   void add_nat( regexp::defmap& defs );
      // Add regular expressions for natural numbers, 
      // even and odd numbers, and other subtypes.

   void add_fol( regexp::defmap& defs, interpreter::program& prog );
      // Add regular expressions for first-order formula
      // and its subtypes.

   void add_modal( regexp::defmap& defs );
      // Add modal formulas.

   void add_basictypes( regexp::defmap& defs );
      // Add a few basic types.

   intermediate::function mixing( );
   intermediate::function arrayconv( ); 
   intermediate::function repeated( );

   data::tree formula( ); 
      // Produce a first-order formula.

   data::tree nat( unsigned int n );
      // Produce natural number n. 

   void add_subst( interpreter::program& prog );  
      // We try to add substitution and lifting.
}

#endif

