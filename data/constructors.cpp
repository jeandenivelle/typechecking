
#include "constructors.h"

data::tree data::usel( const char* c )
{
   return tree( dat_sel, ::usel(c));
}

data::tree data::u64( size_t i )
{
   return tree( dat_u64, (size_t) i );
}

data::tree data::string( std::string_view str )
{
   data::tree res = tree( dat_array, { } );
   for( char c : str )
      res. view_array( ). push_back( data::tree( dat_char, c ));   

   return res; 
}

data::tree data::tuple( const std::vector< tree > & sub )
{
   data::tree res = tree( dat_tuple, { } );
   for( const auto& s : sub )
      res. view_tuple( ). push_back(s);

   return res;
}

data::tree data::array( const std::vector< tree > & sub )
{
   data::tree res = tree( dat_array, { } );
   for( const auto& s : sub )
      res. view_array( ). push_back(s);

   return res;
}

