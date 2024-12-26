
#ifndef INTERMEDIATE_FUNCTION_
#define INTERMEDIATE_FUNCTION_

#include <vector>
#include "util/print.h"
#include "statement.h"

namespace intermediate
{
   struct function
   {
      statement body;
      prop::expr returntype;
      std::vector< prop::expr > parameters;   
         // Temporary solution.

      function( const statement& body, const prop::expr& returntype )
         : body( body ),
           returntype( returntype )
      { }
      
      void print( std::ostream& out ) const
      {
         out << "Function:\n";
         out << "   returntype: " << returntype << "\n";
         out << "\n";
         body. print( indentation(3), out );
      }

   };
}

#endif

