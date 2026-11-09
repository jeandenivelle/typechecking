
#ifndef ATM_STATEMULTISET_
#define ATM_STATEMULTISET_

#include <vector>
#include <iostream>

#include "state.h"

namespace atm
{

   // A word, represented as multiset.

   struct statemultiset
   {

      // 'triple' is not a good name, but the user should not access it
      // anyway.

      struct triple
      {
         state s;
         size_t freq;
         size_t skip; 
      
         triple( state s, size_t freq, size_t skip )
            : s(s), freq( freq ), skip( skip )
         { }

         void print( std::ostream& out ) const 
         {
            out << "( " << s << ", " << freq << ", " << skip << " )";
         }

      };

      std::vector< triple > repr;
      size_t prod;      // Of all the frequences

      statemultiset( std::vector< state > word );

      size_t size( ) const { return repr. size( ); } 
      size_t nrstates( ) const { return prod; }  

      const triple& at( size_t i ) const 
         { return repr. at(i); }
 
      void print( std::ostream& out ) const; 

   };

}

#endif

