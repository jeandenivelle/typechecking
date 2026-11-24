
#include <unordered_map>
#include "basictypes.h"

namespace interpreter
{

   struct varmap
   {
      std::unordered_map< std::string, value > repr;

      void print( std::ostream& out ) const; 
   };

};

   
