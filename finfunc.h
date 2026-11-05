
#ifndef FINFUNC_
#define FINFUNC_ 

#include <iostream>
#include <vector>
#include <unordered_map>

template < typename D, typename R, 
           typename H = std::hash<D>, typename E = std::equal_to<D> >
struct finfunc
{
   R def;    // Default value.

   std::unordered_map<D,R,H,E> func;

   finfunc( ) = delete;

   finfunc( const R& def ) 
      : def( def )
   { }
 
   finfunc( const R& def,
            std::initializer_list<std::pair<const D, R>> init )
      : def( def ) 
   {
      func. reserve( init. size( ));
      for( auto p : init )
         assign( p. first, p. second );
   }

   bool assign( const D& d, const R& r )
   { 
      auto p = func.insert( std::pair<D,R> (d,r));
      return p. second; 
   }

   using iterator = typename std::unordered_map<D,R,H,E>::iterator;
   using const_iterator = 
         typename std::unordered_map<D,R,H,E>::const_iterator;

   iterator begin( ) { return func. begin(); }
   iterator end( ) { return func. end(); }

   const_iterator cbegin( ) const { return func. begin(); }
   const_iterator cend( ) const { return func. end(); }
   const_iterator begin( ) const { return func. begin(); }
   const_iterator end( ) const { return func. end(); }

   const R& apply( const D& d ) const
   {
      auto p = func. find(d);
      if( p != func. end( ))
         return p -> second;
      else
         return def;
   }


   void print( std::ostream& out ) const
   {
      out << "finfunc( <def> -> " << def;
      for( const auto& p : func )
      {
         out << ", ";
         out << p. first << " -> " << p. second;
      }
      out << " )";
   }

   void clear() { func. clear(); }
   size_t size() const { return func. size(); }
   bool empty() const { return func. empty( ); }
};



template< typename D, typename R, typename H, typename E > 
inline std::ostream& 
operator << ( std::ostream& out, const finfunc<D,R,H,E> & fin )
{ 
   fin. print( out ); 
   return out; 
}

#endif

