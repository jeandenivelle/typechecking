
#ifndef USEL_ 
#define USEL_

#include <string>
#include <iostream>
#include "util/normalized.h"

// Written by Hans de Nivelle, sept  2025. 
// Selector constants are normally printed with a '?' in front of them.
// In this class usel, we do not store the '?' nowhere in this class 
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

   struct hash
   {
      util::normalized< std::string > :: hash hh;

      size_t operator( ) ( const usel sel ) const
         { return hh( sel. val ); } 
   };
   
   struct equal_to 
   {
      util::normalized< std::string > :: equal_to eq;

      bool operator( ) ( usel sel1, usel sel2 ) const
         { return eq( sel1. val, sel2. val ); }
   };

};


inline std::ostream& operator << ( std::ostream& out, usel sel )
{
   out << sel. getstring( );
   return out;
}

#endif

