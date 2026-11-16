
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
      // We don't do the final epsilon closure.


   stateset run( const simple& smp, const data::tree& tr );

   simple::sel_func
   merge_sel( const simple& nondet, simple& det, 
              stateset::map< state > & backmap );

   // std::pair< simple, subsetmap > make_deterministic( const simple& smp );
}

#endif

