
#ifndef PARTITION_
#define PARTITION_

#include <iostream>
#include <vector>

// A partition partitions an ordered type using 
// an increasing set of values 
// d0, d1, ... dn.
// The partition is:  
// x < d0 
// x = d0 
// d0 < x < d1
// x = d1
// d1 < x < d2
// ....
// dn < x

// C must be a strict less_than relation on D. 

// The function does not need to be monotone.

template< typename D, typename R, 
          typename C = std::less<D>, 
          typename E = std::equal_to<R> >  
struct partition
{
   C lt; 
   E eq;       // Equality is on R.

   R below;    // The value below the first d. 

   struct interval
   {
      D d;
      R at;
      R after; 
   };

   std::vector< interval > table;
      // Must be sorted by increasing D.

   partition( ) = delete;

   partition( const R& below )
      : below( below )
   { }

   partition( const R& below,
                     std::initializer_list<interval> init )
      : below( below ) 
   {
      table. reserve( init. size( ));
      for( auto p : init )
         append( p.d, p.at, p.after );
   }

   // d must be strictly bigger than everything encountered so far.

   void append( const D& d, const R& at, const R& after )
   {
      if( !table. empty( ))
      {
         if( !lt( table. back( ). d, d ))
         {
            throw std::logic_error(  
               "partition append: not increasing" );
         }

         // Check if the value is already there:

         if( eq( table. back( ). after, at ) && eq( at, after ))
            return; 
               // Insertion is redundant.
      }

      table. push_back( interval( d, at, after ));
   }

   using iterator =
      typename std::vector< interval > :: iterator;

   using const_iterator =
      typename std::vector< interval > :: const_iterator;

   iterator begin( ) { return table.begin( ); }
   iterator end( ) { return table.end( ); }

   const_iterator cbegin( ) const { return table. begin( ); }
   const_iterator cend( ) const { return table. end( ); }
   const_iterator begin( ) const { return table. begin( ); }
   const_iterator end( ) const { return table. end( ); }

   // Uses binary search : 

   const R& operator( ) ( const D& d ) const 
   {
      if( table. empty( ) || lt( d, table. front( ). d ))
         return below;

      const_iterator low = cbegin( );
      const_iterator upp = cend( );

      while( low + 2 < upp )
      {
         const_iterator mid = low + (( upp - low ) >> 1 );

         if( lt( d, mid -> d ))
            upp = mid;
         else
            low = mid;
      }

      // std::cout << "d = " << d << "\n";
      // std::cout << "low " << low - table. begin( ) << "\n";
      // std::cout << "upp " << upp - table. begin( ) << "\n";

      // We search backwards:

      -- upp; 
      while( lt( d, upp -> d ))
         -- upp;

      if( lt( upp -> d, d ))
         return upp -> after;
      else 
         return upp -> at;
   }

   void print( std::ostream& out ) const
   { 
      out << "<below> -> " << below; 
      for( const auto& p : table )
      {
         out << ", " << p.d << " -> ";
         out << "[ first " << p. at << ", then " << p. after << " ]";
      }
      out << "\n";
   } 

   void clear( ) { table. clear( ); }
   size_t size( ) const { return table. size( ); }
   bool empty( ) const { return table. empty( ); }
};


template< typename D, typename R, typename C >
inline std::ostream&
operator << ( std::ostream& out, const partition<D,R,C> & part )
{
   part. print( out );
   return out;
}


#endif

