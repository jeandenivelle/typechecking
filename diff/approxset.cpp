
#include "approxset.h"

diff::approxset diff::approxset::empty( )
{
   approxset res;
   for( short int i = 0; i != arraysize; ++ i )
      res.occ[i] = false;
   return res;
}

diff::approxset diff::approxset::full( )
{
   approxset res;
   for( short int i = 0; i != arraysize; ++ i )
      res.occ[i] = true;
   return res;
}

diff::approxset diff::approxset::eq( )
{
   approxset res = empty( );
   res.occ[ max ] = true;
   return res;
}

diff::approxset diff::approxset::ne( )
{
   approxset res = full( );
   res.occ[ max ] = false;
   return res;
}

diff::approxset diff::approxset::lt( )
{
   approxset res;
   for( short int i = 0; i != max; ++ i )
      res.occ[i] = true;
   for( short i = max; i != arraysize; ++ i )
      res.occ[i] = false;

   return res;
}

diff::approxset diff::approxset::gt( )
{
   approxset res;
   for( short int i = 0; i != max + 1; ++ i )
      res.occ[i] = false;
   for( short i = max + 1; i != arraysize; ++ i )
      res.occ[i] = true;
   
   return res;
}

diff::approxset diff::approxset::le( )
{
   approxset res;
   for( short int i = 0; i != max + 1; ++ i )
      res.occ[i] = true;
   for( short i = max + 1; i != arraysize; ++ i )
      res.occ[i] = false;

   return res;
}

diff::approxset diff::approxset::ge( )
{
   approxset res;
   for( short int i = 0; i != max; ++ i )
      res.occ[i] = false;
   for( short i = max; i != arraysize; ++ i )
      res.occ[i] = true;

   return res;
}

diff::approxset 
diff::approxset::operator - ( ) const
{
   approxset res; 

   auto p = occ + arraysize;
   auto q = res. occ;
   while( p > occ )
      * q ++ = * -- p;

   return res;
}

diff::approxset
diff::operator + ( const approxset& set1, const approxset& set2 )
{
   constexpr short int max = approxset::max;

   auto res = diff::approxset::empty( );

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


bool diff::approxset::isempty( ) const
{
   for( auto p = occ; p != occ + arraysize; ++ p )
   {
      if( *p ) return false;
   }
   return true;
}

bool diff::approxset::isfull( ) const
{
   for( auto p = occ; p != occ + arraysize; ++ p )
   {
      if( ! *p ) return false;
   }
   return true;
}

bool diff::approxset::restrict( const approxset& other )
{
   bool change = false;

   for( short unsigned int i = 0; i < 2 * approxset::max + 1; ++ i )
   {
      if( occ[i] && !other.occ[i] )
      {
         change = true;
         occ[i] = false;
      }
   }

   return change;
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

