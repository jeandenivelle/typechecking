
#ifndef USEL_ 
#define USEL_

#include <string>
#include <unordered_set>
#include <iostream>
#include "util/hashbuilder.h"

// Written by Hans de Nivelle, January 2021. 
// Selector constants are printed with a '?' in front of them.
// We will not store the '?' inside this class and also not print it.

class usel
{
   using indextype = std::unordered_set< std::string > ;

   indextype :: const_iterator p;

public: 
   usel( const std::string& s )
   {
      static indextype index;
      auto val = index. insert(s);
      p = val. first;
   }
     
   usel( const char* c )
      : usel( std::string(c))
   { }
 
   const std::string& getstring( ) const
      { return *p; }

   bool operator == ( usel sel ) const 
      { return p == sel.p; } 
   bool operator != ( usel sel ) const 
      { return p != sel.p; } 

   void hash( util::hashbuilder& b ) const 
   { 
      std::hash< const std::string* > hh; 
      b << hh( & *p ); 
   }
 
};


inline std::ostream& operator << ( std::ostream& out, usel sel )
{
   out << sel. getstring( );
   return out;
}

inline util::hashbuilder& operator << ( util::hashbuilder& b, usel sel )
{
   sel. hash(b);
   return b;
}

#endif

