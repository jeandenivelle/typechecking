
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

