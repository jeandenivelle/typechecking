
#include "focus.h"
#include "statemultiset.h"

namespace
{

   using namespace atm;

   // mset[ trans ] is the symbol for which we are currently trying to
   // find transitions.

   void addtransitions( simple& smp, size_t level, size_t trans,
                        const statemultiset& mset,
                        const std::vector< state > & statevect,
                        size_t index )
   {
      if( level == mset. size( ))
      {
         std::cout << "adding from " << index << "\n";
         return; 
      }

      size_t max = mset. at( level ). freq;
      if( level != trans )
         ++ max;      
      
      for( size_t i = 0; i != max; ++ i )
      {
         addtransitions( smp, level + 1, trans, mset, statevect, index );
         index += mset. at( level ). skip;
      }   
   }

}

   
atm::focus
atm::convert_word( simple& smp, std::vector< state > word )
{
   auto mset = statemultiset( word );
   std::cout << mset << "\n";

   // Now we have the word as a multiset, and we don't care
   // about 'word' anymore.

   word. clear( );   // To be sure.

   auto entry = smp. create_state( ); 
   auto accept = smp. create_state( );
   auto result = focus( entry, accept ); 
   for( size_t i = 0; i != mset. nrstates( ); ++ i )
      result. states. push_back( smp. create_state( )); 

   for( size_t trans = 0; trans != mset. size( ); ++ trans )
   {
      std::cout << "trans = " << trans << "\n";  
      addtransitions( smp, 0, trans, mset, result. states, 0 );
   }
   
   return result; 
}

