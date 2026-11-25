
// Everything that deals with nondeterminism.

#ifndef ATM_NONDETERMINISM_
#define ATM_NONDETERMINISM_

#include "data/tree.h"
#include "stateset.h"
#include "simple.h"

namespace atm 
{
   void close_eps( const simple& smp, stateset& s );

   stateset apply_tuple( const simple& smp, 
                         const stateset& tuple, const stateset& single );

   stateset apply_set( const simple& smp, 
                       const stateset& set, const stateset& element );
      // We don't do the epsilon closure on the result.

   stateset run( const simple& smp, const data::tree& tr );
      // non-deterministically.
  

   struct subsets
   {
      stateset::map< state > checked;
      stateset::map< state > unchecked;

      subsets( ) noexcept = default;
      subsets( subsets&& ) noexcept = default;
      subsets& operator = ( subsets&& ) noexcept = default;

      bool insert( stateset set, state q );
         // Insert into unchecked. True if it happened.

      state create_or_reuse( simple& det, stateset set );

      using iterator = stateset::map< state > :: iterator;

      void print( std::ostream& out ) const;
   };

   state 
   create_or_reuse( stateset set, 
                    const stateset::map< state > & checked,
                    stateset::map< state > & unchecked,
                    simple& det );
      // We create a state that is new in smp if needed.

   simple make_deterministic( subsets& sub, const simple& nondet );
}

#endif

