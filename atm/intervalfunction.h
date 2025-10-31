
#ifndef ATM_INTERVALFUNCTION_
#define ATM_INTERVALFUNCTION_ 

#include <iostream>
#include <vector>

// Border functions are nicer, but they don't work with the reals.
// With a border function, one cannot classify 
// lessthanzero, zero, exactlyzero.

namespace atm
{

   // C must be a usual less_than relation on D. 
   // E must be an equality relation on R. It is used for checking
   // whether two adjacent intervales go to the same r,
   // in which case they can be merged.

   template< typename D, typename R, 
             typename C = std::less<D>, typename E = std::equal_to<R> > 
   struct intervalfunction
   {
      C lt; 
      E eq; 

      R bot;    // The value below the first d. 

      struct interval
      {
         D d;
         R at;
         R after; 
      };

      std::vector< interval > table;
	// Must be sorted by increasing D.

      intervalfunction( const R& bot = R( ))
         : bot( bot )
      { }

      intervalfunction( const R& bot,
                        std::initializer_list<interval> init )
         : bot( bot ) 
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
                            "intervalfunction append: not increasing" );
            }

            // Check if the value is already there:

            if( eq( table. back( ). after, at ) && eq( at, after ))
               return; 
                  // Addition is redundant.
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
            return bot;

         const_iterator low = cbegin( );
         const_iterator upp = cend( );

         while( low + 3 < upp )
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
         out << "Interval Function:\n";
         out << "bottom = " << bot << "\n";
         for( const auto& p : table )
         {
            out << "   " << p. d;
            out << " --> [ " << p. at << "; " << p. after << " )\n";
         }
         out << "\n";
      } 

      void clear( ) { table. clear( ); }
      size_t size( ) const { return table. size( ); }
      bool empty( ) const { return table. empty( ); }
   };

#if 0

   template< typename C, typename R, typename S1, typename S2, typename F >
   stepfunction<C,R> 
   transform( const stepfunction<C,S1> & m1, const stepfunction<C,S2> & m2, const F& f ) 
   {
      auto p1 = m1. begin( );
      auto p2 = m2. begin( );
      if( p1 == m1. end( ) || p2 == m2. end( ))
         throw std::runtime_error( "transform, size cannot be zero" );
      if( p1 -> first != p2 -> first )
         throw std::runtime_error( "transform, maps must start at same C" );

      stepfunction<C,R> res;
 
      C c = p1 -> first;

      // c is the point that we are looking at.
      // p1,p2 are positions that determine the value of c.
      // p1,p2 reach the end at the same time.

      while( p1 != m1. end( ) || p2 != m2. end( ))
      {
         // std::cout << "c = " << c << "\n"; 
         // std::cout << "f = " << f( p1 -> second, p2 -> second ) << "\n";

         res. append( c, f( p1 -> second, p2 -> second ));
      
         ++ p1; 
         if( p1 == m1. end( ))
         {
            -- p1;
            ++ p2;
            if( p2 == m2. end( ))
               ++ p1;    // that's the end. 
            else
               c = p2 -> first;
         }
         else
         {
            ++ p2;
            if( p2 == m2. end( ))
            { 
               -- p2;
               c = p1 -> first;
            }
            else
            {
               if( p1 -> first == p2 -> first )
               {
                  c = p1 -> first;
               }
               else
               {
                  if( p1 -> first < p2 -> first )
                  {
                     -- p2;
                     c = p1 -> first;
                  }
                  else
                  {
                     -- p1;
                     c = p2 -> first;
                  }
               }
            }
         }
      }

      return res;
   }
#endif

}

#endif

