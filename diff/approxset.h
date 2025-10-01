
#ifndef DIFF_APPROXSET_
#define DIFF_APPROXSET_

#include <iostream>

namespace diff
{

   // This is a typical example where C++ fails, like with the rationals.

   class approxset
   {
   public:
      constexpr static short unsigned int max = 3;
         // We represent -inf, ... -max as one value,
         // then we have -max + 1, -1, 0, 1, max - 1 represented
         // accurately, and 
         // max, max+1, ... inf are again a single value. 
         // In the paper, we use max = 2. 

      constexpr static short arraysize = 2 * max + 1;

   private:
      bool occ[ arraysize ];

      // Does not initialize, hence it is private:

      approxset( ) noexcept
      { }

   public:
      static approxset empty( );  // Bottom of the lattice.
      static approxset full( );  // Top of the lattice. 
      static approxset eq( );
      static approxset ne( );
      static approxset lt( );
      static approxset gt( );
      static approxset le( );
      static approxset ge( );
 
 
      bool contains( short int i ) const
      {
         if( i >= max ) return occ[ 2 * max ];
         if( i <= -max ) return occ[0];
         return occ[ max + i ];
      }  

      void insert( short int i )
      {
         if( i >= max ) { occ[ 2 * max ] = true; return; }
         if( i <= -max ) { occ[0] = true; return; } 
         occ[ max + i ] = true;
      }

      approxset operator - ( ) const; 
   };

   approxset operator + ( const approxset& set1, const approxset& set2 );
   approxset operator & ( const approxset& set1, const approxset& set2 );

   std::ostream& operator << ( std::ostream& out, const approxset& set );
}

#endif

