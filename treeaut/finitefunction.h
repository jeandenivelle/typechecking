
#ifndef TREEAUT_FINITEFUNCTION_
#define TREEAUT_FINITEFUNCTION_ 

#include <iostream>
#include <vector>

namespace treeaut
{

   template < typename D, typename R, 
              typename H = std::hash<D>, typename E = std::equal_to<D>>

   struct finitefunction
   {
      R def;    // Default value.

      std::unordered_map<D,R,H,E > func;

      finitefunction( )
         : def( R( ))
      { }

      finitefunction( const R& def ) 
         : def( def )
      { }
 
      finitefunction( const R& def,
                      std::initializer_list<std::pair<const D, R>> init )
      {
         func. reserve( init. size( ));
         for( auto p : init )
            assign( p.first, p.second );
      }

      void assign( const D& d, const R& r )
      { 
         auto p = func. find(d);
         if( p != func. end( ))
         {
            throw std::logic_error( 
                           "finitefunction: reassignment not allowed" );
         }
         else
            func. insert( std::pair<D,R> ( d, r )); 
      }

      using iterator = typename std::unordered_map<D,R,H,E>::iterator;
      using const_iterator = 
         typename std::unordered_map<D,R,H,E>::const_iterator;

      iterator begin() { return func. begin(); }
      iterator end() { return func. end(); }

      const_iterator cbegin() const { return func. begin(); }
      const_iterator cend() const { return func. end(); }
      const_iterator begin() const { return func. begin(); }
      const_iterator end() const { return func. end(); }

      const R& operator( ) ( const D& d ) const
      {
         auto p = func. find(d);
         if( p != func. end( ))
            return p -> second;
         else
            return def;
      }

#if 0
      // Uses binary search : 

      const_iterator find( const C& c ) const 
      {
         const_iterator low = begin( );
         const_iterator upp = end( );

         while( low + 3 < upp )
         {
            const_iterator mid = low + (( upp - low ) >> 1 );

            if( mid -> first <= c )
               low = mid;
            else
               upp = mid;
         }

         // When the interval is small enough, we search backwards:

         while( upp > low )
         {
            -- upp;
            if( upp -> first <= c )
               return upp;
         }

         return end( );
      }

#endif

      void print( std::ostream& out ) const
      {
         out << "Finite Function:\n";
         out << "default = " << def << "\n";
         for( const auto& p : func )
            out << "   " << p. first << " --> " << p. second << "\n";
         out << "\n";
      }

      void clear() { func. clear(); }
      size_t size() const { return func. size(); }
      bool empty() const { return func. empty( ); }
   };


#if 0
   template< typename C, typename R, typename S1, typename S2, typename F >
   borderfunc<C,R> 
   transform( const borderfunc<C,S1> & m1, const borderfunc<C,S2> & m2, const F& f ) 
   {
      auto p1 = m1. begin( );
      auto p2 = m2. begin( );
      if( p1 == m1. end( ) || p2 == m2. end( ))
         throw std::runtime_error( "transform, size cannot be zero" );
      if( p1 -> first != p2 -> first )
         throw std::runtime_error( "transform, maps must start at same C" );

      borderfunc<C,R> res;
 
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

