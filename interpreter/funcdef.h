
#ifndef INTERPRETER_FUNCDEF_
#define INTERPRETER_FUNCDEF_

#include <vector>
#include <iostream>
#include <map>

#include "identifier.h"
#include "basictypes.h"
#include "block.h"

namespace interpreter
{

   struct funcdef
   {
      std::vector< std::pair< std::string, declaration >> parameters;

      flavour resultflav;
      property result; 
         // Not really needed at this point.

      std::map< size_t, block > body;
      using block_iterator = std::map< size_t, block > :: const_iterator;
      using iterator = std::map< size_t, block > :: iterator;
         // Start is always at #0.

      funcdef( flavour resultflav, const property& result )
         : resultflav( resultflav ),
           result( result )
      { }

      funcdef( ) = delete;
      funcdef( funcdef&& ) noexcept = default;
      funcdef& operator = ( funcdef&& ) noexcept = default;

      block& operator [] ( size_t i ) 
         { return body[i]; }

      std::pair< iterator, bool > emplace( size_t i, block bl )
         { return body. emplace( i, std::move( bl )); }
 
      void print( std::ostream& out ) const;
   };

}

#endif

