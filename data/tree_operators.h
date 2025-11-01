
#ifndef DATA_TREE_OPERATORS_
#define DATA_TREE_OPERATORS_

#include <vector>

namespace data 
{

   inline tree operator "" _sel( const char* c, size_t len )
      { return tree( tree_usel, usel(c)); }

   inline tree tuple( const tree& tr1 )
      { return tree( tree_tuple, { tr1 } ); } 

   inline tree tuple( const tree& tr1, const tree& tr2 )
      { return tree( tree_tuple, { tr1, tr2 } ); }

   inline tree zero( )
      { return tuple( "zero"_sel ); }

   tree succ( const tree& tr )
      { return tuple( "succ"_sel, tr ); }

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

