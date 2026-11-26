
#ifndef INTERPRETER_BASICTYPES_
#define INTERPRETER_BASICTYPES_

#include <optional>
#include <string>
#include <iostream>

#include "identifier.h"
#include "data/tree.h"

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
      std::optional< data::tree > val;     // Exists when we are flav_val. 
      data::tree* pntr; 
         // We don't bother to put pntr in an optional, because
         // it's not owning.
   };

   struct property
   {
      identifier maintype;
      identifier subtype;
   };


   struct declaration
   {
      std::string var;
      flavour flav;
      bool isfixed;
      property precond; 
   };


}

#endif

