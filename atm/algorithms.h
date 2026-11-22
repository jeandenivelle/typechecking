
#ifndef ATM_ALGORITHMS_
#define ATM_ALGORITHMS_

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
  
   state run_det( const simple& smp, const data::tree& tr );
      // Run deterministically. If the automaton is not deterministic,
      // a random path is picked.

   state 
   create_or_reuse( stateset set, 
                    const stateset::map< state > & checked,
                    stateset::map< state > & unchecked,
                    simple& det );
      // We create a state that is new in smp if needed.

   std::ostream& operator << ( std::ostream& out,
                               const stateset::map< state > & collapse );

   std::pair< simple, stateset::map< state >> 
      make_deterministic( const simple& nondet );
}

#endif

