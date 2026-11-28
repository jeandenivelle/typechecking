
#ifndef INTERPRETER_BASICTYPES_
#define INTERPRETER_BASICTYPES_

#include <optional>
#include <string>
#include <iostream>

#include "identifier.h"
#include "data/tree.h"

#include "atm/state.h"

namespace interpreter
{
   enum flavour { flav_val, flav_constval, flav_ref, flav_constref };
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

      identifier::map< atm::state > properties;
         // If we run an automaton on the value, we keep the resulting
         // state, for the case we need it again. 

      value( data::tree tr )
         : flav( flav_val ),
           val( std::move( tr )),
           pntr( nullptr )
      { }

      void print( std::ostream& out ) const;
   };


   struct property
   {
      identifier maintype;
      identifier subtype;

      void print( std::ostream& out ) const
         { out << maintype << " @ " << subtype; } 
   };


   struct declaration
   {
      flavour flav;
      bool isfixed;
      property precond; 

      void print( std::ostream& out ) const;
   };

}

#endif

