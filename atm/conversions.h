
#ifndef ATM_CONVERSIONS_
#define ATM_CONVERSIONS_

#include "simple.h"
#include "regexp/defmap.h"
#include "convresult.h"

namespace atm
{
   identifier::map< state > 
   make_automata( const regexp::defmap& defs, 
                  simple& smp );

                   
   convresult
   convert( simple& smp,
            const regexp::expr& e, 
            const regexp::defmap& defs,
            const identifier::map< state > & accepting );

}

#endif

