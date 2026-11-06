
#include "conversions.h"

identifier::map< atm::state >
atm::make_automata( const regexp::defmap& defs,
                    simple& smp );

atm::state atm::add_automaton( simple& smp, 
               const regexp::expr& e,
               const regexp::defmap& defs,
               const identifier::map< state > & accepting )
{

   std::cout << "translating " << e << "\n";

   switch( e. sel( ))
   {

   case regexp::log_or:
      {



      }
   }

   std::cout << e << "\n";
   throw std::logic_error( "not implemented" ); 

}



