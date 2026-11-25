
#ifndef ATM_EVALUATOR_
#define ATM_EVALUATOR_

#include "identifier.h"
#include "simple.h"
#include "translator.h"
#include "data/tree.h"

namespace atm 
{
   struct evaluator
   {
      simple det;
      std::multimap< state, identifier, state::less > accept;
 
      void minimize( );
         // Maybe not useful.

      evaluator( simple&& det ) noexcept 
         : det( std::move( det ))
      { }

      evaluator( evaluator&& ) noexcept = default;
      evaluator& operator = ( evaluator&& ) noexcept = default;

      state run( const data::tree& tr ) const;

      void print( std::ostream& out ) const; 
   };


   evaluator make_evaluator( const translator& trans );
}

#endif

