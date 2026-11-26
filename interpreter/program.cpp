
#include "program.h"


void interpreter::program::print( std::ostream& out ) const
{
   out << "Program:\n";

   if( fields. size( ))
   {
      out << "Fields:\n";
      for( const auto& fld : fields )
         out << "   " << fld. first << " : " << fld. second << "\n";
      out << "\n";
   }

}

