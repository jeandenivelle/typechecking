
#ifndef ATM_CONVERSIONS_
#define ATM_CONVERSIONS_

#include "simple.h"
#include "regexp/defmap.h"
#include "convresult.h"

namespace atm
{
   using statemap = identifier::map< state > ;

   statemap create_accepting( const regexp::defmap& defs, simple& smp );

   convresult convert2single( simple& smp, const convresult& res );
      // It might become an error too!

   convresult
   convert( simple& smp, const regexp::expr& e, 
            const regexp::defmap& defs, const statemap& acc );

   std::ostream& operator << ( std::ostream& out, const statemap& acc );

}

#endif

