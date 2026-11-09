
#include "view.h"
#include "statemultiset.h"

namespace
{
   using namespace atm;

   // mset. at( trans ) is the symbol for which we are currently trying to
   // find transitions.

   void addtransitions( simple& smp, size_t level, size_t trans,
                        const statemultiset& mset,
                        const std::vector< state > & statevect,
                        size_t index )
   {
      if( level == mset. size( ))
      {
         // A transition over state mset. at( trans ). s : 

         smp. delta_set. insert( 
            { { statevect. at( index ), mset. at( trans ). s }, 
              statevect. at( index + mset. at( trans ). skip ) } ); 
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

   
atm::view
atm::convert_word( simple& smp, std::vector< state > word )
{
   auto mset = statemultiset( word );
   std::cout << mset << "\n";

   // Now we have the word as a multiset, and we don't care
   // about 'word' any more.

   word. clear( );   // To be sure.

   auto entry = smp. create_state( ); 
   auto exit= smp. create_state( );
   auto result = view( entry, exit ); 
   for( size_t i = 0; i != mset. nrstates( ); ++ i )
      result. states. push_back( smp. create_state( )); 

   for( size_t trans = 0; trans != mset. size( ); ++ trans )
      addtransitions( smp, 0, trans, mset, result. states, 0 );

   smp. delta_epsilon. insert( { result. entry, result. states. front( ) } );
   smp. delta_epsilon. insert( { result. states. back( ), result. exit } ); 
   return result; 
}

void atm::view::print( std::ostream& out ) const
{
   out << "View( " << entry << ", " << exit;
   for( auto p = states. begin( ); p != states. end( ); ++ p )
   {
      if( p == states. begin( ))
         out << ";  ";
      else
         out << ", ";
      out << *p;
   }
   out << " )";
}

