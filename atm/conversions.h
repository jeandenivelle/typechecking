
#ifndef ATM_CONVERSIONS_
#define ATM_CONVERSIONS_

#include "simple.h"
#include "regexp/defmap.h"
#include "convresult.h"

namespace atm
{
   using statemap = identifier::map< state > ;

   state conv_state( const simple& smp, state base, size_t i );

   state add2simple( const builder& bld, simple& smp );
      // Add bld to smp, and return the accepting state.

   statemap create_accepting( const regexp::defmap& defs, simple& smp );

   state state_of( const convresult& res );
      // fails if res is an error or a builder.

   convresult conv2single( simple& smp, const convresult& res );
      // It might become an error too!

   convresult
   convert( simple& smp, const regexp::expr& e, 
            const regexp::defmap& defs, const statemap& acc );

   std::ostream& operator << ( std::ostream& out, const statemap& acc );
}

#endif

