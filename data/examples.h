
#ifndef DATA_EXAMPLES_
#define DATA_EXAMPLES_

#include <string_view>

#include "tree.h"

namespace data
{

   tree string( std::string_view str );

   tree variable( std::string_view str );
   tree debruijn( size_t ind );

   tree term( tree name, const std::vector< tree > & sub ); 
      // A first-order term.

   tree negate( const tree& sub );
      // 'not' is a reserved word.

   tree implies( const tree& sub1, const tree& sub2 );
   tree equiv( const tree& sub1, const tree& sub2 );

   tree conj( const std::vector< tree > & sub );
   tree disj( const std::vector< tree > & sub );
      // 'and' and 'or' are reserved words.

   tree zero( );
   tree succ( const tree& tr );

}

#endif
