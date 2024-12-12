
#ifndef PROP_DEFMAP_
#define PROP_DEFMAP_

#include <unordered_map>
#include <iostream>

#include "exactident.h"

namespace prop
{
   struct defmap
   {
      exactidentmap< expr > mp;

      defmap( ) noexcept = default;

      bool contains( exactident id ) const;

      // True if the insertion happened. We refuse to overwrite:

      bool insert( exactident id, const expr& e )
      {
         auto& forid = mp[ id. id ];
         auto p = forid. insert( std::pair< size_t, expr > ( id. ind, e ));
         return p. second;
      }

      void print( std::ostream& out ) const
      {
         out << "Property definitions:\n";
         for( const auto& id : mp )
            for( const auto& ind : id. second )
            {
               out << "   ";
               out << exactident( id. first, ind. first );
               out << " := " << ind. second << "\n";
            }
      }

      size_t size( ) const { return mp. size( ); } 
   };
};

#endif
 
