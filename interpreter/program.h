
#ifndef INTERPRETER_PROGRAM_
#define INTERPRETER_PROGRAM_

#include "identifier.h" 
#include "funcdef.h"
#include "fielddef.h"

#include "atm/evaluator.h"

namespace interpreter
{

   struct program
   {

      identifier::map< atm::evaluator > maintypes;
         // The main types are not subtypes of another type.

      identifier::multimap< fielddef > fields; 
      identifier::multimap< funcdef > functions; 

      program( ) noexcept = default;
      program( const program& ) = default;
      program& operator = ( const program& ) = default;

      void print( std::ostream& out ) const; 
   };

}

#endif

