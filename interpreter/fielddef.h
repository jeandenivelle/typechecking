
#ifndef INTERPRETER_FIELDDEF_
#define INTERPRETER_FIELDDEF_

#include "basictypes.h"

namespace interpreter
{

   enum fieldcategory { fld_scalar, fld_repeated };

   const char* getcstring( fieldcategory );

   inline std::ostream& operator << ( std::ostream& out, fieldcategory cat )
      { out << getcstring( cat ); return out; }


   struct fielddef
   {
      fieldcategory cat;  
      size_t index; 
      property precond; 
         // postcondition is taken from the automaton. 
         // This is the essence of the approach.
         // In the interpreter, types are always recomputed anyway.
 
      fielddef( fieldcategory cat, size_t index, 
                const property& precond )
         : cat( cat ), index( index ), 
           precond( precond ) 
      { }
  
      fielddef( fieldcategory cat, size_t index,
                const identifier& maintype, const identifier& subtype )
         : cat( cat ), index( index ),
           precond( maintype, subtype )
      { }
  
      void print( std::ostream& out ) const;

   };

}

#endif
 
