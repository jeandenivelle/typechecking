
#ifndef TESTS_
#define TESTS_

#include "fieldmap.h"
#include "regexp/defmap.h"
#include "data/tree.h"

#include "intermediate/function.h"

namespace tests
{
   void add_nat( regexp::defmap& defs, fieldmap& flds );
      // Add regular expressions for natural numbers, 
      // even and odd numbers:

   void add_fol( regexp::defmap& defs, fieldmap& flds );
      // Add regular expressions for first-order formula.

   intermediate::function mixing( );
   intermediate::function arrayconv( ); 
   intermediate::function repeated( );

   data::tree formula( ); 
      // Produce a first-order formula.

   data::tree nat( unsigned int x );
      // Produce a natural number. 

}

#endif

