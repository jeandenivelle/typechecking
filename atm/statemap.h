
#include <map>
#include <iostream>
#include <string>

#include "state.h"
#include "util/print.h"

namespace atm
{

   struct statemap
   {

      std::map< std::string, state > map;

      statemap( ) noexcept = default;

      state& operator[] ( const std::string& name )
         { return map[ name ]; }

      state at( const std::string& name ) const
         { return map. at( name ); }

      void print( std::ostream& out ) const;
   };

}


