
#ifndef ATM_STATESET_
#define ATM_STATESET_

#include <set>
#include <map> 
#include <iostream>

#include "state.h"

namespace atm 
{
   struct stateset
   {
      std::set< state, state::less > impl;

      stateset( ) = default;
      stateset( std::initializer_list< state > set ) 
         : impl( set )
      { }

      bool insert( state q ) 
         { return impl. insert(q). second; }

      using const_iterator = std::set< state, state::less > :: const_iterator;
      const_iterator begin( ) const { return impl. begin( ); }
      const_iterator end( ) const { return impl. end( ); }

      size_t size( ) const { return impl. size( ); }

      struct less
      {
         bool operator( ) ( const stateset& s1, const stateset& s2 ) const;
      };

      template< typename D > using map = std::map< stateset, D, less > ;

      void print( std::ostream& out ) const;
   };


   bool operator == ( const stateset& s1, const stateset& s2 ); 

   inline bool operator != ( const stateset& s1, const stateset& s2 )
      { return ! ( s1 == s2 ); } 
   
   bool subset( const stateset& s1, const stateset& s2 ); 
}

#endif

