#ifndef ATM_STATES
#define ATM_STATES

#include <unordered_set>
#include <ostream>

namespace atm {
   
/*
   struct state_t {
      size_t s;
      state_t(): s(0) {};

      struct hash {
         size_t operator() ( const state_t& s ) {
            auto h = std::hash <size_t> {};
            return h( s.s );
         }
      };

      struct equal_to {
         bool operator() ( const state_t& s1, const state_t& s2 ) {
            auto q = std::equal_to <size_t> {};
            return q( s1.s, s2.s ); 
         }
      };
   
      void print( std::ostream& out ) const {
         out << '<' << s << '>';   
      }
   };

   inline std::ostream& operator<<( std::ostream& out, const state_t& s ) {
      s. print( out );
      return out;
   }
*/

   using state_t = size_t;
   using state_pair_t = std::pair< state_t, state_t >;

	struct state_pair_hash {
      std::size_t operator( ) ( const state_pair_t& p ) const {
         auto h = std::hash <size_t> {};
	      return h( p.first ) ^ ( h( p.second ) << 1 );
		}
	};
	
	struct state_pair_equal_to {
      std::size_t operator( ) ( const state_pair_t& p1, const state_pair_t& p2 ) const {
         auto q = std::equal_to <size_t> {};
         return q( p1. first, p2. first ) && q( p1. second, p2. second );
		}
   };

   inline std::ostream& operator<< ( std::ostream& out, const state_pair_t& state_pair ) {
      out << "< " << state_pair. first << ", " << state_pair. second << " >";
      return out;
   }

   struct states_t {
      state_t def;
      std::unordered_set< state_t, std::hash< state_t >, std::equal_to< state_t > > Q;
      
      using iterator = std::unordered_set< state_t, std::hash< state_t >, std::equal_to< state_t > >:: iterator;
      using const_iterator = std::unordered_set< state_t, std::hash< state_t >, std::equal_to< state_t > >:: const_iterator;

      states_t( ): def( 0 ) {}
      states_t( const state_t& def ): def( def ) {}
      states_t( const state_t&& def ): def( std::move( def ) ) {}
      
      state_t get_next_state( ) {
         state_t state = def;
         while( Q. find( state ) != Q. cend() ) {
            ++state;
         }
         Q. insert( state );
         return state;
      }
      
      size_t size( ) const {
         return Q. size( );
      }

      void print( std::ostream& out ) const {
         out <<" States = { ";
         for( const_iterator i = Q. begin(); i != Q. end(); ++i ) {
            if( i != Q. begin() ) out << ", ";
            out << *i;
         }
         out << " }";
      }
   };
   
   inline std::ostream& operator<< ( std::ostream& out, const states_t& states ) {
      states. print( out );
      return out;
   }
};

#endif
