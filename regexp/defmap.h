
// Written by Hans de Nivelle, July 2026.

#ifndef REGEXP_DEFMAP_
#define REGEXP_DEFMAP_

#include <unordered_map>
#include <iostream>

#include "identifier.h"
#include "expr.h"
#include "exprtype.h"

namespace regexp
{
   using defmap = identifier::map< expr > ; 

   inline std::ostream& operator << ( std::ostream& out,
                                      const defmap& mp ) 
   {
      out << "Definition Map:\n";
      for( const auto& def : mp )
      {
         out << "   " << def. first << " : " << def. second << "\n";
      }
      return out; 
   }

}


#endif
 
