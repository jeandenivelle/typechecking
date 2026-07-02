
#ifndef DATA_TREE_OPERATORS_
#define DATA_TREE_OPERATORS_

#include <vector>

namespace data 
{

   // Logic:

   inline tree atom( std::string_view name )
   {
      std::vector< tree > chr;
      for( char c : name )
         chr. push_back( tree( tree_char, c ));

      auto tr = tree( tree_array, chr. begin( ), chr. end( ));
      return tuple( "atom"_sel , tr ); 
   }      

   inline tree operator ! ( const tree& sub ) 
      { return tuple( "not"_sel, sub ); } 

}

#endif

