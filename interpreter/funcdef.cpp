
#include "funcdef.h"

void interpreter::funcdef::print( std::ostream& out ) const
{
   out << "Function:\n";
   for( const auto& par : parameters )
   {
      out << "   " << par. first << " : " << par. second << "\n";
   }
   out << "\n";

   out << "Body:\n";
   for( size_t i = 0; i != body. size( ); ++ i )
   {
      out << '#' << i << ": " << body. at(i) << "\n";
   }
}


