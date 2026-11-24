
#ifndef INTERPRETER_PROGRAM_
#define INTERPRETER_PROGRAM_

#include <map>

#include "funcdef.h"

namespace interpreter
{

   struct program
   {

      identifier::map< funcdef > functions; 

      program( ) noexcept = default;
      program( const program& ) = default;
      program& operator = ( const program& ) = default;


   };

}

#endif

