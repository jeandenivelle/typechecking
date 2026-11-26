
#ifndef INTERPRETER_FIELDDEF_
#define INTERPRETER_FIELDDEF_

#include "atm/evaluator.h"

namespace interpreter
{

   enum fieldcategory { fld_scalar, fld_vector, fld_list };

   const char* getcstring( fieldcategory );

   inline std::ostream& operator << ( std::ostream& out, fieldcategory cat )
   {
      out << getcstring( cat ); return out;
   }


   struct fielddef
   {
      fieldcategory cat;  
      size_t index; 
      property precond; 

      fielddef( fieldcategory cat, size_t index, 
                const property& precond )
         : cat( cat ), index( index ), 
           precond( precond ) 
      { }
   
      void print( std::ostream& out ) const; 
   };

}

#endif
 
