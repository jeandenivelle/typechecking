
#ifndef FLOWGRAPH_LABEL_
#define FLOWGRAPH_LABEL_

#include <iostream>
#include <string>

namespace flowgraph
{
   // Labels identify blocks. 

   struct label
   {  
      std::string base;
      size_t index; 

      label( ) = delete;

      label( const std::string& base, size_t index )
         : base( base ), index( index )
      { }

      label( const char* base, size_t index )
         : base( base ), index( index )
      { }

      void print( std::ostream& out ) const
         { out << base << '_' << index; } 

      // We think that order is important, so we don't provide
      // a hashing function.
   };

   inline bool operator == ( label lab1, label lab2 )
   {
      return lab1.base == lab2.base && lab1.index == lab2.index;
   }

   inline bool operator != ( label lab1, label lab2 )
   {
      return lab1.base != lab2.base || lab1.index != lab2.index;
   }

   inline bool operator < ( label lab1, label lab2 )
   {
      return lab1.base < lab2.base ||
             ( lab1.base == lab2.base && lab1.index < lab2.index );
   }

   inline bool operator > ( label lab1, label lab2 )
   {
      return lab2 < lab1;
   }

   inline bool operator <= ( label lab1, label lab2 )
   {
      return lab1.base < lab2.base ||
            ( lab1.base == lab2.base && lab1.index <= lab2.index );
   }

   inline bool operator >= ( label lab1, label lab2 )
   {
      return lab2 <= lab1;
   }

}

#endif
 
