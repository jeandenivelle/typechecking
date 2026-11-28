
#include "basictypes.h"

const char* interpreter::getcstring( flavour flav )
{
   if( flav == flav_val )
      return "val"; 
   if( flav == flav_constval )
      return "constval";

   if( flav == flav_ref )
      return "ref";
   if( flav == flav_constref )
      return "constref";

   return "???";
}


void 
interpreter::declaration::print( std::ostream& out ) const
{ 
   out << flav; 
   if( isfixed ) 
      out << " (fixed), ";
   else
      out << ", ";
   out << precond; 
}


