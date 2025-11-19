#ifndef _ATM_STATEMAP_
#define _ATM_STATEMAP_

#include <map>
#include <iostream>
#include <string>

#include "state.h"
#include "util/print.h"

namespace atm
{

   struct statemap
   {

      std::map< std::string, state > map;
      
      using iterator = std::map< std::string, state >::iterator;
      using const_iterator = std::map< std::string, state >::const_iterator;

      statemap( ) noexcept = default;

      state& operator[] ( const std::string& name )
         { return map[ name ]; }
      
      std::pair< iterator, bool > insert( const std::string& name, const state& state ) 
         { return map. insert( std::pair( name, state ) ); }
      
      std::pair< iterator, bool > insert( const std::string&& name, const state& state ) 
         { return map. insert( std::pair( name, state ) ); }

      iterator begin( )
         { return map. begin( ); }

      iterator end( ) 
         { return map. end( ); }

      const_iterator begin( ) const
         { return map. begin( ); }

      const_iterator end( ) const 
         { return map. end( ); }

      iterator find( const std::string& name )
         { return map. find( name ); }
      
      const_iterator find( const std::string& name ) const
         { return map. find( name ); }

      iterator find( const state& state ) {
         for( auto it = map. begin( ); it != map. end( ); ++it ) {
            if( it-> second == state ) {
               return it;
            }
         }
      
         return map. end();
      }
      
      const_iterator find( const state& state ) const {
         for( auto it = map. begin( ); it != map. end( ); ++it ) {
            if( it-> second == state ) {
              return it;
            }
         }
      
         return map. end();
      }

      state at( const std::string& name ) const
         { return map. at( name ); }

      void print( std::ostream& out ) const;
   };

   std::string state2str( const state&, const statemap& );
}

#endif
