
#ifndef INTERPRETER_BASICTYPES_
#define INTERPRETER_BASICTYPES_

#include <optional>
#include <string>
#include <iostream>

#include "data/tree.h"
#include "atm/stateset.h"

namespace interpreter
{
   enum flavour
   {
      flav_val, flav_constval, flav_ref, flav_constref 
   };

   const char* getcstring( flavour );

   inline 
   std::ostream& operator << ( std::ostream& out, flavour flav )
      { out << getcstring( flav ); return out; }


   struct value
   {
      flavour flav;
      std::optional< data::tree > val;
      data::tree* pntr; 
         // We don't bother to put pntr in an optional, because
         // it's not owning.
   };


   struct declaration
   {
      std::string name; 
      flavour flav;
      bool isfixed;
      atm::stateset props;
   };

    
}

#endif

