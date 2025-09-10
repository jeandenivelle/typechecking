
#ifndef NEVER_ 
#define NEVER_

#include <iostream>
#include "util/hashbuilder.h" 

// Never is a type without elements.
// A never can be copied, assigned, but not constructed.

class never
{

public: 
   never( ) = delete;
   never( const never& ) noexcept = default;
   never& operator = ( const never& ) noexcept = default; 
   ~never( ) = default;

   bool operator == ( never n ) const 
      { return true; } 
   bool operator != ( never n ) const 
      { return true; } 

};

inline std::ostream& operator << ( std::ostream& out, never n )
{
   out << "(you are not seeing this)";
   return out;
}

inline util::hashbuilder& operator << ( util::hashbuilder& b, never n )
{
   b << 13;
   return b;
}

#endif

