
#ifndef ATM_STATESET_
#define ATM_STATESET_

#include <set>
#include <iostream>

#include "state.h"

namespace atm 
{
   using stateset = std::set< state, state::less > ;

   std::ostream& operator<< ( std::ostream& out, const stateset& set ); 

   bool operator == ( const stateset& s1, const stateset& s2 ); 
   bool operator != ( const stateset& s1, const stateset& s2 );

   bool subset( const stateset& s1, const stateset& s2 ); 
}

#endif

