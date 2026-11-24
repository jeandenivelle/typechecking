
#ifndef INTERPRETER_BLOCK_
#define INTERPRETER_BLOCK_

#include "instruction.h"

namespace interpreter
{
   class block
   {
      std::vector< instruction > instr;
  
   public:
      block( ) noexcept = default;
      block( block&& ) noexcept = default;
      block& operator = ( block&& ) noexcept = default;
      ~block( ) noexcept = default;
         // Copying is disabled.

      size_t size( ) const
         { return instr. size( ); }

      const instruction& at( size_t i ) const
         { return instr. at(i); }

      instruction& at( size_t i )
         { return instr. at(i); }

      void append( instruction&& ins )
         { instr. push_back( std::move( ins )); }

      void print( std::ostream& out ) const;
   };

}

#endif

