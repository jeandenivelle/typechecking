
#ifndef INTERPRETER_PROGRAM_
#define INTERPRETER_PROGRAM_

#include <vector>
#include <map>

#include "identifier.h" 
#include "funcdef.h"
#include "fielddef.h"

#include "atm/evaluator.h"

namespace interpreter
{

   struct program
   {

      identifier::map< atm::evaluator > toptypes;
         // The top types are not subtypes of another type.

      identifier::multimap< fielddef > fields; 

      identifier::multimap< funcdef > functions; 
      using func_iterator = 
            identifier::multimap< funcdef > :: const_iterator;

      program( ) noexcept = default;
      program( const program& ) = default;
      program& operator = ( const program& ) = default;

      value 
      exec( const funcdef& func, std::vector< value > values ) const;
         // values are the values of the actual parameters.

      void print( std::ostream& out ) const; 
   };

}

#endif

