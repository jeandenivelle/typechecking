
#ifndef ATM_STATE_
#define ATM_STATE_

#include <iostream>
#include "util/print.h"

namespace atm
{

   // It is better to form sets of states with ordered tree than
   // with hashmap, because it makes equality testing easier.

   struct state 
   {
      size_t s;

      state( ): 
         s(0) {};

      state& operator ++ ( )
         { ++ s; return *this; } 
      
      state operator ++ ( int )
         { auto res = *this; ++ *this; return res; }

      state operator + ( unsigned int i ) const
         { auto res = *this; res. s += i; return res; }

      state& operator += ( unsigned int i )
         { s += i; return *this; }

      bool operator == ( state other ) const
         { return s == other.s; }

      bool operator != ( state other ) const
         { return s != other.s; }

      struct less 
      {
         bool operator() ( state q1, state q2 ) const 
         {
            return q1.s < q2.s; 
         }
      };

      struct pair_less
      {
         bool operator( ) ( std::pair< state, state > p1,
                            std::pair< state, state > p2 ) const
         {
            if( p1.first.s != p2.first.s )
               return p1.first.s < p2.first.s;

            return p1. second. s < p2. second. s;
         }
      };

      void print( std::ostream& out ) const 
      {
         out << 'Q';
         if( s < 10 )
            out << '0';
         out << s;
      }
   };

   inline std::ostream& operator << ( std::ostream& out, state q ) 
      { q. print( out ); return out; } 

}

#endif

