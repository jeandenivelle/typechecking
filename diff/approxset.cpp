
#include "approxset.h"

diff::approxset
diff::operator + ( const approxset& set1, const approxset& set2 )
{
   constexpr short int max = approxset::max;

   diff::approxset res; 
   for( int i1 = -max; i1 <= max; ++ i1 )
      for( int i2 = -max; i2 <= max; ++ i2 )
      {
         if( set1.contains(i1) && set2.contains(i2) )
         {
            res. insert( i1 + i2 );

            // Because max represents max-1, max-2, max-3, ...

            if( i1 == -max || i2 == -max )
            {
               for( int i = -max; i < i1 + i2; ++ i )
                  res. insert(i);
            }

            // Because max represents max+1, max+2, max+3, ...

            if( i1 == max || i2 == max )
            {
               for( int i = i1 + i2 + 1; i <= max; ++ i )
                  res. insert(i); 
            }
 
         }
      }
   return res; 
}

diff::approxset 
diff::operator & ( const approxset& set1, const approxset& set2 )
{
   auto res = set1;

   for( unsigned int i = 0; i < 2 * approxset::max + 1; ++ i )
   {
      res. occ[i] = ( set1.occ[i] & set2.occ[i] ); 
   }

   return res;
}


diff::approxset diff::operator - ( const approxset& set )
{
   auto res = set; 

   bool* p1 = res. occ; 
   bool* p2 = res. occ + 2 * approxset::max; 

   while( p1 < p2 )
   {
      std::swap( *p1, *p2 ); 
      ++ p1; -- p2;
   }

   return res;
}


std::ostream& 
diff::operator << ( std::ostream& out, const approxset& set )
{
   out << '{';
   unsigned int counter = 0;
   for( short int i = - approxset::max; i <= approxset::max; ++ i ) 
   {
      if( set.contains(i) )
      {
         if( counter == 0 )
            out << ' ';
         else
            out << ", ";
         out << i;
         if( i == -approxset::max || i == approxset::max )
            out << '*';

         ++ counter;
      }
   }
   out << " }";
   return out;
}

