
#ifndef INTERPRETER_CONFIGURATION_
#define INTERPRETER_CONFIGURATION_

#include "funcdef.h"

namespace interpreter
{

   // We use the C++ recursion for function calls. Because
   // of this, we have no stack. I we are ever going to compile
   // this language, we will do the same. We will compile into C.

   struct configuration
   {
      program::functio;
      funcdef::block_iterator blk;
      size_t index; 

      std::unordered_map< std::string, value > variables;
      bool tracing;

      configuration( const funcdef* func )
         : func( func ),
           blk( func -> body. find(0)),  
           tracing( false ) 
      { }  

      bool wellformed( ) const
         { return index < blk -> second. size( ); }

      const instruction& getinstruction( ) const
         { return blk -> second. at( index ); }

      void printposition( std::ostream& out ) const
      {
         out << "In function " << func -> first;
         out << " at position " << blk -> first << index;
      }

      void printeverything( std::ostream& out ) const
      {
         printposition( out ); 
         out << "\n";
#if 0
         for( const auto& r : variables )
            out << "   " << r. first << " / " << r. second << "\n";
#endif
      }

      void step( )  
         { ++ index; }

   }; 
       
}

#endif

