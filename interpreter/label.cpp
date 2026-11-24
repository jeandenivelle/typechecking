
#include "label.h"

interpreter::label::label( std::string_view str )
   : str( std::string( str ))
{ }

interpreter::label::label( std::string_view str, size_t index )
   : str( std::string( str )) 
{
   size_t k = 1;
   while( k <= index )
      k *= 10;
   k /= 10;
   while(k)
   {
      this -> str. push_back( index / k + '0' );
      index = index % k; 
      k /= 10;
   }
}


