
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
      identifier::map< expr > mp; 

   public:
      defmap( ) noexcept = default;

      bool contains( const identifier& ident ) const;

      // True if the insertion happened. We stubbornly refuse to overwrite:

      bool insert( const identifier& ident, const expr& e );

      const expr& at( const identifier& id ) const 
         { return mp. at( id ); }

      size_t size( ) const { return mp. size( ); } 

      using const_iterator = identifier::map< expr > :: const_iterator;
      const_iterator begin( ) const { return mp. begin( ); }
      const_iterator end( ) const { return mp. end( ); }

      void print( std::ostream& out ) const;
   };

}

#endif
 
