
#ifndef ATM_STATESET_
#define ATM_STATESET_

#include <set>
#include <iostream>

#include "state.h"

namespace atm 
{
   
   struct stateset
   {
      std::set< state, state::less > repr;

      stateset( ) noexcept = default;

      bool insert( state s )
         { return repr. insert(s). second; }

      void insert( const std::set<atm::state, atm::state::less> other_repr )
         { repr. insert( other_repr. cbegin(), other_repr. cend() ); }

      bool remove( state s )
         { return repr. erase(s); }       

      bool empty( ) const { return repr. empty( ); }
      size_t size( ) const { return repr. size( ); }

      using const_iterator = 
         std::set< state, state::less > :: const_iterator;

      const_iterator begin( ) const { return repr. begin( ); }
      const_iterator end( ) const { return repr. end( ); }

      void print( std::ostream& out ) const;
   };

   inline std::ostream& 
   operator<< ( std::ostream& out, const stateset& set ) 
   {
      set. print( out );
      return out;
   }

   bool operator == ( const stateset& s1, const stateset& s2 ); 
   bool subset( const stateset& s1, const stateset& s2 ); 
}

#endif

