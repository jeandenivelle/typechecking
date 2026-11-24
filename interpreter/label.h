
#ifndef INTERPRETER_LABEL_
#define INTERPRETER_LABEL_

#include <string>
#include <iostream>

namespace interpreter
{
   class label
   {
      std::string str;

      label( ) = delete;

   public:
      label( std::string_view str ); 
      label( std::string_view str, size_t index );
     
      bool operator == ( const label& lab ) const
         { return str == lab. str; }

      bool operator < ( const label& lab ) const
         { return str < lab. str; }
 
      void print( std::ostream& out ) const
         { out << str; } 
   };

   inline bool operator != ( const label& lab1, const label& lab2 )
      { return !( lab1 == lab2 ); }

   inline bool operator > ( const label& lab1, const label& lab2 )
      { return lab2 < lab1; }

   inline bool operator <= ( const label& lab1, const label& lab2 )
      { return ! ( lab1 > lab2 ); } 

   inline bool operator >= ( const label& lab1, const label& lab2 )
      { return ! ( lab1 < lab2 ); } 
 
}

#endif

