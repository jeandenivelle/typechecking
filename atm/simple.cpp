
#include "simple.h"

void 
atm::simple::addtuple( const std::vector< state > & tup, state goal )
{
   std::cout << "adding tuple transition: ";
   for( auto s : tup ) std::cout << s << " ";
   std::cout << " -> " << goal << "\n";

   // In earlier versions, we tried to reuse states, but 
   // now we don't care: We just create a new path.

   state partial = empty_tuple; 
   for( auto s : tup )
   {
      state next = newstate( );
      delta_tuple. insert( { { partial, s }, next } );

      partial = next;
   } 

   std::cout << "reached " << partial << "\n";

   // We create an epsilon transition to goal:

   delta_epsilon. insert( { partial, goal } );
}


void atm::simple::print( std::ostream& out ) const
{
   out << "Simple Automaton:\n";
   out << "   trap = " << trap << "\n";
   out << "\n";

   if( comments. size( ))
   {
      out << "Comments:\n";
      for( const auto& c : comments )
         out << "   " << c. first << " : " << c. second << "\n";
      out << "\n";
   }
   
   if( delta_usel. size( )) 
   {
      out << "Delta (usel):\n";
      for( const auto& t : delta_usel )
         out << "   " << t << "\n";
      out << "\n";
   }

   out << "Tuple transitions:\n";
   out << "   <empty> -> " << empty_tuple << "\n";
   for( const auto& t : delta_tuple )
   {
      out << "   " << t. first. first << ", " << t. first. second; 
      out << " -> " << t. second << "\n";
   }
   out << "\n";

   out << "Set transitions:\n"; 
   out << "   <empty> -> " << empty_set << "\n";
   for( const auto& d : delta_set )
   {
      out << "   " << d. first. first << ", " << d. first. second;
      out << " -> " << d. second << "\n";
   }
   out << "\n";

   out << "Epsilon Transitions:\n"; 
   for( const auto& e : delta_epsilon )
      out << "   " << e. first << " -> " << e. second << "\n";
   out << "\n";

}

