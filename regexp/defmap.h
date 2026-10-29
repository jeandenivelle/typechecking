
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
   class defmap
   {
      struct value
      {
         expr e;
         exprtype tp;

         value( expr e, exprtype tp )
            : e( std::move(e)),
              tp( std::move(tp))
         { }
      };

      identifier::map< value > mp; 

   public:
      defmap( ) noexcept = default;

      bool contains( const identifier& ident ) const;

      // True if the insertion happened. We stubbornly refuse to overwrite:

      bool insert( const identifier& ident, expr e, exprtype tp );

      value& at( const identifier& id ) 
         { return mp. at( id ); }

      const value& at( const identifier& id ) const 
         { return mp. at( id ); }

      size_t size( ) const { return mp. size( ); } 

      using const_iterator = identifier::map< value > :: const_iterator;
      const_iterator begin( ) const { return mp. begin( ); }
      const_iterator end( ) const { return mp. end( ); }

      using iterator = identifier::map< value > :: iterator; 
      iterator begin( ) { return mp. begin( ); }
      iterator end( ) { return mp. end( ); }

      void print( std::ostream& out ) const;
   };

}

#endif
 
