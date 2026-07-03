
#include "examples.h"

data::tree data::string( std::string_view str )
{
   data::tree res = tree_array( { } );
   for( char c : str )
      res. view_array( ). push_back( data::tree( sel_char, c ));   

   return res; 
}

data::tree data::variable( std::string_view str )
{
   return tree_tuple( { tree_usel( usel( "name" )), string( str ) } );
}

data::tree data::debruijn( size_t ind )
{
   return tree_tuple( { tree_usel( usel( "debruijn" )), tree( sel_u64, ind ) } );
}

data::tree data::term( tree name, const std::vector< tree > & sub )
{
   return tree_tuple( { tree_usel( usel( "term" )), 
                        tree_array( sub. begin( ), sub. end( )) } );

}

data::tree data::negate( const tree& sub )
{ 
   return tree_tuple( { tree_usel( "not" ), sub } ); 
}


data::tree data::implies( const tree& sub1, const tree& sub2 )
{
   return tree_tuple( { tree_usel( usel( "implies" )), sub1, sub2 } ); 
}

data::tree data::equiv( const tree& sub1, const tree& sub2 )
{
   return tree_tuple( { tree_usel( usel( "equiv" )), sub1, sub2 } );
}

data::tree data::conj( const std::vector< tree > & sub )
{
   return tree_tuple( { tree_usel( usel( "and" )), 
                        tree_array( sub. begin( ), sub. end( )) } );
}

data::tree data::zero( )
{ 
   return tree_tuple( { tree_usel( usel( "zero" )) } ); 
}

data::tree data::succ( const tree& tr )
{
   return tree_tuple( { tree_usel( usel( "succ" )), tr  } ); 
}


