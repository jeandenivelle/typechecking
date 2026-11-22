
#ifndef ATM_CONVERSIONS_
#define ATM_CONVERSIONS_

#include "simple.h"
#include "regexp/defmap.h"
#include "convresult.h"

namespace atm
{

   struct brancher
   {
      state yes;
      state no;

      brancher( state yes, state no )
         : yes( yes ), no( no )
      { }
 
      state operator( ) ( bool b ) const
         { return b ? yes : no; }
   };

   using statemap = identifier::map< state > ;

   state add2simple( const builder& bld, simple& smp );
      // Add the conversion of bld to smp, and return the accepting state.

   statemap 
   create_states( const regexp::defmap& defs, simple& smp );
      // Create a new state for every definition.
      // statemap maps identifiers to the created states.

   state state_of( const convresult& res );
      // fails if res is an error or a builder.

   convresult conv2single( simple& smp, const convresult& res );

   convresult
   convert( simple& smp, const regexp::expr& e, 
            const regexp::defmap& defs, const statemap& acc );

   void 
   convert( simple& smp, const regexp::defmap& defs, const statemap& acc );

   std::ostream& operator << ( std::ostream& out, const statemap& acc );
}

#endif

