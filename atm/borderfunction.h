
#include <iostream>
#include <vector>

#ifndef ATM_BORDERFUNCTION_
#define ATM_BORDERFUNCTION_ 

namespace atm
{

   // C must be a usual less_than relation on D. 
   // E is an equality relation on R. It is used for checking
   // whether two adjacent intervales go to the same r,
   // and can be merged.

   template< typename D, typename R, 
             typename C = std::less<D>, typename E = std::equal_to<R> > 
   struct borderfunction
   {
      C cmp; 
      E eq; 
      R def; 

      std::vector< std::pair< const D, R >> table;
	// Must be sorted by increasing D.

      borderfunction( const R& def = R( ))
         : def( def )
      { }

      borderfunction( const R& def,
                      std::initializer_list< std::pair<D,R> > init )
         : def( def ) 
      {
         table. reserve( init. size( ));
         for( auto p : init )
            append( p.first, p.second );
      }

      // d must be strictly bigger than everything encountered so far.

      void append( const D& d, const R& r )
      {
         if( !table. empty( ))
         {
            if( !cmp( table. back( ). first, d ))
            {
               throw std::logic_error( 
                            "borderfunction append: not increasing" );
            }

            // Check if the value is already there:

            if( eq( table. back( ). second, r ))
               return; 
                  // Same value as the last, so the addition is redundant.
         }

         table. push_back( std::pair<D,R> (d,r) );
      }

      using iterator =
         typename std::vector<std::pair<const D, R>> :: iterator;
      using const_iterator =
         typename std::vector<std::pair<const D, R>> :: const_iterator;

      iterator begin( ) { return table.begin( ); }
      iterator end( ) { return table.end( ); }

      const_iterator cbegin( ) const { return table. begin( ); }
      const_iterator cend( ) const { return table. end( ); }
      const_iterator begin( ) const { return table. begin( ); }
      const_iterator end( ) const { return table. end( ); }

      // Uses binary search : 

      const R& operator( ) ( const D& d ) const 
      {
         if( table. empty( ) || cmp( d, table. front( ). first ))
            return def;

         const_iterator low = cbegin( );
         const_iterator upp = cend( );

         while( low + 3 < upp )
         {
            const_iterator mid = low + (( upp - low ) >> 1 );

            if( cmp( d, mid -> first ))
               upp = mid;
            else
               low = mid;
         }

         // std::cout << "d = " << d << "\n";
         // std::cout << "low " << low - table. begin( ) << "\n";
         // std::cout << "upp " << upp - table. begin( ) << "\n";

         // We search backwards:

         -- upp; 
         while( cmp( d, upp -> first ))
            -- upp;

         return upp -> second;
      }

      void print( std::ostream& out ) const
      { 
         out << "Border Function:\n";
         out << "default = " << def << "\n";
         for( const auto& p : table )
            out << "   " << p. first << " --> " << p. second << "\n";
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

