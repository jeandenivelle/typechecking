
#ifndef INTERPRETER_FUNCDEF_
#define INTERPRETER_FUNCDEF_

#include <vector>
#include <iostream>
#include <map>

#include "identifier.h"
#include "basictypes.h"
#include "block.h"

namespace interpreter
{

   struct funcdef
   {
      std::vector< std::pair< std::string, declaration >> parameters;

      flavour resultflav;
      property resultprop; 
         // Not really needed.

      std::map< label, block > body;

      void print( std::ostream& out ) const;
   };

}

#endif

