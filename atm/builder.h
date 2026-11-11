
// A builder can build only set automata. There are almost
// no operations on tuple automata, so they don't need 
// a dedicated builder class. 

#ifndef ATM_BUILDER_
#define ATM_BUILDER_

#include <vector>
#include <iostream>

#include "state.h"

namespace atm
{

   struct builder
   {
      size_t nrstates;
         // 0 is always entry, and nrstates itself is always the exit.
         // There can be no transitions from nrstates.
         
      static constexpr size_t empty_set = 
         std::numeric_limits< size_t > :: max( );

      struct transition
      {
         size_t from;
         state element;
         size_t to;

         transition( size_t from, state element, size_t to )
            : from( from ), element( element ), to( to )
         { } 

         transition moved( size_t dist ) const
            { return transition( from + dist, element, to + dist ); }
      };

      struct epsilon
      {
         size_t from;
         size_t to;

         epsilon( size_t from, size_t to )
            : from( from ), to( to )
         { } 

         epsilon moved( size_t dist ) const
            { return epsilon( from + dist, to + dist ); } 
      };

      std::vector< transition > delta_set;
      std::vector< epsilon > delta_eps;


      // Default is the automaton that accepts the empty set:

      builder( ) noexcept 
         : nrstates(0)
      { }

 

      void addlinear( state aa, size_t nr );
         // If nr == 0, nothing changes.
         // nr == 1 will add one copy, etc.

      void addcircular( state aa, size_t nr );
         // If nr == 0, then add circular will not add a copy, but
         // it will still add a circle with length 1.

 
      void printstate( std::ostream& out, size_t s ) const;
      void print( std::ostream& out ) const;

   private:
      void copy_delta( size_t delta_set_size, size_t delta_eps_size );

   };

   builder disjunction( const std::vector< builder > & disj );
      // Builds a disjunction.

}

#endif

