
#ifndef DIFF_APPROXSET_
#define DIFF_APPROXSET_

#include <iostream>

namespace diff
{

   struct approxset
   {
      constexpr static short unsigned int max = 3;
         // We represent -inf, ... -max as one value,
         // then we have -max + 1, -1, 0, 1, max - 1 represented
         // accurately, and 
         // max, max+1, ... inf are again a single value. 
         // In the paper, we use max = 2. 
      bool occ[ 2 * max + 1 ];

      explicit approxset( bool val = false ) noexcept
      {
         for( unsigned int i = 0; i != 2 * max + 1; ++ i )
            occ[i] = val;
      }

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
 
   };

   approxset operator + ( const approxset& set1, const approxset& set2 );
   approxset operator - ( const approxset& set );
   approxset operator & ( const approxset& set1, const approxset& set2 );

   std::ostream& operator << ( std::ostream& out, const approxset& set );
}

#endif

