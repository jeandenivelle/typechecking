
#ifndef INTERPRETER_FUNCDEF_
#define INTERPRETER_FUNCDEF_

#include <vector>
#include <map>

#include "identifier.h"
#include "basictypes.h"
#include "block.h"

namespace interpreter
{

   struct funcdef
   {

      std::vector< declaration > parameters;

      flavour resultflav;
      atm::stateset resultprops;
         // Not really needed.

      std::map< label, block > body;

   };

}

#endif

