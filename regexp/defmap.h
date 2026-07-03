
// Written by Hans de Nivelle, July 2026.

#ifndef REGEXP_DEFMAP_
#define REGEXP_DEFMAP_

#include <unordered_map>
#include <iostream>

#include "identifier.h"
#include "expr.h"

namespace regexp
{
   class defmap
   {
      using maptype = 
         std::unordered_map< identifier, expr, 
                             identifier::hash, identifier::equal_to > ;
      maptype mp; 

   public:
      defmap( ) noexcept = default;

      bool contains( const identifier& ident ) const;

      // True if the insertion happened. We stubbornly refuse to overwrite:

      bool insert( const identifier& ident, const expr& e );

      size_t size( ) const { return mp. size( ); } 

      void print( std::ostream& out ) const;

   };
};

#endif
 
