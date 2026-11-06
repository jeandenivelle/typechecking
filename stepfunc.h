
#ifndef STEPFUNC_
#define STEPFUNC_

#include <iostream>
#include <vector>
#include <concepts>

// C must be a strict less_than relation on D. 

// The function does not need to be monotone (order preserving),
// the range type does not need to be ordered. 

template< typename D, typename R, 
          std::strict_weak_order<D,D> C = std::less<D>,
          std::equivalence_relation<R,R> E = std::equal_to<R> >  
struct stepfunc
{
   C lt; 
   E eq;   

   R initial;  // The value below the first d. 

   struct step
   {
      D d;
      R val; 
   };

   std::vector< step > table;
      // Must be sorted by increasing D.

   stepfunc( ) = delete;

   stepfunc( const R& initial )
      : initial( initial )
   { }

   stepfunc( const R& initial,
             std::initializer_list< step > init )
      : initial( initial ) 
   {
      table. reserve( init. size( ));
      for( auto p : init )
         append( p.d, p.at, p.after );
   }

   // d must be strictly greater than the values encountered
   // until now. 

   void append( const D& d, const R& val )
   {
      if( !table. empty( ))
      {
         if( !lt( table. back( ). d, d ))
         {
            throw std::logic_error(  
               "stepfunc append: domain not increasing" );
         }

         // Check if the lst value equals the new value:

         if( eq( table. back( ). val, val ))
            return; 
               // Insertion is redundant.
      }

      table. push_back( step( d, val ));
   }

   using iterator = typename std::vector< step > :: iterator;
   using const_iterator = typename std::vector< step > :: const_iterator;

   iterator begin( ) { return table. begin( ); }
   iterator end( ) { return table. end( ); }

   const_iterator cbegin( ) const { return table. begin( ); }
   const_iterator cend( ) const { return table. end( ); }

   const_iterator begin( ) const { return table. begin( ); }
   const_iterator end( ) const { return table. end( ); }

   // Uses binary search : 

   const R& apply( const D& d ) const 
   {
      if( table. empty( ) || lt( d, table. front( ). d ))
         return initial;

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

      return upp -> val;
   }

   void print( std::ostream& out ) const
   { 
      out << "stepfunc( ";
      out << "<initial> -> " << initial; 
      for( const auto& p : table )
      {
         out << ", " << p.d << " -> " << p. val;
      }
      out << " )";
   } 

   size_t size( ) const { return table. size( ); }
   bool empty( ) const { return table. empty( ); }
};


template< typename D, typename R, typename C >
inline std::ostream&
operator << ( std::ostream& out, const stepfunc<D,R,C> & part )
{
   part. print( out );
   return out;
}


#endif

