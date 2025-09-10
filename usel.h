
#ifndef USEL_ 
#define USEL_

#include <string>
#include <iostream>
#include "util/normalized.h"

// Written by Hans de Nivelle, sept  2025. 
// Selector constants are normally printed with a '?' in front of them.
// In this class usel, we do not store the '?' inside this class 
// and also will not print it.

class usel
{
   util::normalized< std::string > val;

public: 
   usel( const std::string& s )
      : val( util::normalized(s)) 
   { }
     
   usel( const char* c )
      : usel( std::string(c))
   { }
 
   const std::string& getstring( ) const
      { return val. value( ); }

   bool operator == ( usel sel ) const 
      { return val == sel.val; } 
   bool operator != ( usel sel ) const 
      { return val != sel.val; } 

   size_t hash( ) const 
   { 
      util::normalized< std::string > :: hash hh; 
      return hh( val ); 
   }
 
};


inline std::ostream& operator << ( std::ostream& out, usel sel )
{
   out << sel. getstring( );
   return out;
}

#endif

