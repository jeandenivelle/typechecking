
#ifndef DATA_CONSTRUCTORS_
#define DATA_CONSTRUCTORS_

#include <string_view>

#include "tree.h"

namespace data
{
   tree usel( const char* c );

   tree u64( size_t ind );

   tree tuple( const std::vector< tree > & sub );
   tree array( const std::vector< tree > & sub );

   tree string( std::string_view v );
      // A string is just an array of characters.
}

#endif

