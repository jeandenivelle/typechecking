
#ifndef OVERLOADMAP_
#define OVERLOADMAP_

#include <unordered_map>
#include <vector>
#include <iostream>
#include "identifier.h" 

class overloadmap
{
   using maptype = 
      std::unordered_map< identifier, std::vector< size_t >, 
                          identifier::hash, identifier::equal_to > ;

   maptype mp;

public:
   overloadmap( ) noexcept = default;
   overloadmap( overloadmap&& ) noexcept = default;
   overloadmap& operator = ( overloadmap&& ) = default;

   void add( const identifier& id, size_t nr );
      // We don't check uniqueness, and always add.

   void print( std::ostream& out ) const;
};

#endif    

