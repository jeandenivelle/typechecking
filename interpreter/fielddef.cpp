
#include "fielddef.h"

const char* interpreter::getcstring( fieldcategory cat )
{
   switch( cat )
   {
   case fld_scalar:
      return "scalar";
   case fld_repeated:
      return "repeated";
   }
   return "???"; 
}

void interpreter::fielddef::print( std::ostream& out ) const
{
   out << cat << "( #" << index << " : " << precond << " )";
}


