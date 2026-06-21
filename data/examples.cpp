
#include "examples.h"

data::tree data::string( std::string_view str )
{
   data::tree res = tree_array( { } );
   for( char c : str )
      res. view_array( ). push_back( data::tree( sel_char, c ));   

   return res; 
}

data::tree data::variable( const tree& sub )
{
   return tree_tuple( { tree_usel( usel( "var" )), sub } );
}

data::tree data::term( tree name, const std::vector< tree > & sub )
{
   return tree_tuple( { tree_usel( usel( "term" )), 
                        tree_array( sub. begin( ), sub. end( )) } );

}

data::tree data::implies( const tree& sub1, const tree& sub2 )
{
   return tree_tuple( { tree_usel( usel( "implies" )), sub1, sub2 } ); 
}

data::tree data::equiv( const tree& sub1, const tree& sub2 )
{
   return tree_tuple( { tree_usel( usel( "equiv" )), sub1, sub2 } );
}


