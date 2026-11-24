
#ifndef ATM_CLUSTER_
#define ATM_CLUSTER_

#include "identifier.h"
#include "stateset.h"
#include "simple.h"
#include "convresult.h"

#include "regexp/defmap.h"

// A cluster is a collection of types, centered around a common
// automaton. I hope this is the right class.

namespace atm
{
   struct cluster
   {

      struct info
      {
         stateset acc;           // Its stateset. 
         std::string comments;   // For example: errors.
 
         void print( std::ostream& out ) const; 

         info( ) noexcept = default;
      };

      atm::simple common;
         // The common automaton.

      identifier::map< info > props;
      std::map< state, identifier::set, state::less > props_inv;
 
      cluster( simple&& smp = simple( ))
         : common( std::move( smp ))
      { }

      void add_accept( const identifier& id, state q );

      void regexp2nondet( const regexp::defmap& defs );
         // The main function.

   private: 
      convresult regexp2nondet( const regexp::expr& e );
      convresult conv2single( const convresult& res );
      convresult makesimple( const builder& bld );

   public:
      void print( std::ostream& out ) const;
   };

   void make_deterministic( );
      // Make the automaton deterministic, and correct the state sets
      // accordingly.
      
}

#endif

