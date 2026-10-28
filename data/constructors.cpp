
#include "constructors.h"

data::tree data::usel( const char* c )
{
   return tree( sel_usel, ::usel(c));
}

data::tree data::u64( size_t i )
{
   return tree( sel_u64, (size_t) i );
}

data::tree data::string( std::string_view str )
{
   data::tree res = tree( sel_array, { } );
   for( char c : str )
      res. view_array( ). push_back( data::tree( sel_char, c ));   

   return res; 
}

data::tree data::tuple( const std::vector< tree > & sub )
{
   data::tree res = tree( sel_tuple, { } );
   for( const auto& s : sub )
      res. view_tuple( ). push_back(s);

   return res;
}

data::tree data::array( const std::vector< tree > & sub )
{
   data::tree res = tree( sel_array, { } );
   for( const auto& s : sub )
      res. view_array( ). push_back(s);

   return res;
}

