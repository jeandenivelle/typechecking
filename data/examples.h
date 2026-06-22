
#ifndef DATA_EXAMPLES_
#define DATA_EXAMPLES_

#include <string_view>

#include "tree.h"

namespace data
{

   tree string( std::string_view str );

   tree variable( const tree& sub );
   tree term( tree name, const std::vector< tree > & sub ); 
   tree not_( const tree& sub );
   tree implies( const tree& sub1, const tree& sub2 );
   tree equiv( const tree& sub1, const tree& sub2 );

   tree zero( );
   tree succ( const tree& tr );

}

#endif
