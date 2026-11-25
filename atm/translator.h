

#ifndef ATM_TRANSLATOR_
#define ATM_TRANSLATOR_

#include "identifier.h"
#include "stateset.h"
#include "simple.h"
#include "convresult.h"

#include "regexp/defmap.h"

// A translator merges regular expressions into a single
// non-deterministic automaton.
// Regular expressions come as a set of definitions that 
// recursively refer to each other. 
// We have to translate such a group of expressions at once together. 
// In order to do that, one must create a state for each expression, 
// and then translate
// the expressions. In the end, we contain one big, non-deterministc
// automaton.


namespace atm
{

   struct translator
   {

      atm::simple shared;
         // The shared, non-deterministic automaton.

      identifier::map< state > accepting;
 
      translator( simple&& smp = simple( ))
         : shared( std::move( smp ))
      { }

      size_t size( ) const { return accepting. size( ); }

      identifier::set insert( const regexp::defmap& defs );
         // The main function: Inserts the translated regular
         // expressions to the automaton. We return the names
         // that were not inserted.

   private: 
      convresult translate( const regexp::expr& e );

      convresult conv2single( const convresult& res );
      convresult translate2simple( const builder& bld );

   public:
      void print( std::ostream& out ) const;
   };

}

#endif

