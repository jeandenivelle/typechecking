
#ifndef ATM_CONVERSIONS_
#define ATM_CONVERSIONS_

#include "simple.h"
#include "regexp/defmap.h"
#include "convresult.h"

namespace atm
{
   using statemap = identifier::map< state > ;
   using resultmap = identifier::map< convresult > ;

   state add2simple( const builder& bld, simple& smp );
      // Add the conversion of bld to smp, and return the accepting state.

   statemap 
   accepting_states( const regexp::defmap& defs, simple& smp );
      // Create a state for every definition.
      // statemap maps identifiers to the created states.

   state state_of( const convresult& res );
      // fails if res is an error or a builder.

   convresult conv2single( simple& smp, const convresult& res );

   convresult
   convert( simple& smp, const regexp::expr& e, 
            const regexp::defmap& defs, const statemap& acc );

   void 
   convert( simple& smp, resultmap& results,
            const regexp::defmap& defs, const statemap& acc );

   std::ostream& operator << ( std::ostream& out, const statemap& acc );
}

#endif

