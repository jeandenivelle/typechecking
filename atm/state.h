
#ifndef ATM_STATE_
#define ATM_STATE_

#include <utility>
#include <iostream>

namespace atm
{

   // It is better to form sets of states with ordered tree than
   // with hashmap, because it makes equality testing easier.

   struct state 
   {
      size_t s;

      state( ): 
         s(0) {};

      struct less 
      {
         bool operator() ( state s1, state s2 ) const 
         {
            return s1.s < s2.s; 
         }
      };

      state& operator ++ ( )
         { ++ s; return *this; } 
      
      state operator ++ ( int )
         { auto res = *this; ++ *this; return res; }

      state& operator -- ( )
         { -- s; return *this; }

      state operator -- ( int )
         { auto res = *this; -- *this; return res; } 

      bool operator == ( state other ) const
         { return s == other.s; }

      bool operator != ( state other ) const
         { return s != other.s; }

      void print( std::ostream& out ) const {
         out << 'Q';
         if( s < 10 )
            out << '0';
         out << s; 
      }
   };

   inline std::ostream& 
   operator<< ( std::ostream& out, const state& s ) {
      s. print( out );
      return out;
   }
}

#endif

