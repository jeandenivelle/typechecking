
#include "simple.h"

void 
atm::simple:: addforall( const std::vector< state > & single, 
                         state goal )
{
   state loop = create_state( );
   delta_epsilon. insert( { empty_set, loop } );
   for( const auto& s : single )
      delta_set. insert( { { loop, s }, loop } );

   delta_epsilon. insert( { loop, goal } );
}


void 
atm::simple::addtuple( const std::vector< state > & tup, state goal )
{
   // In earlier versions, we tried to reuse states, but 
   // now we don't care: We just create a new path.

   state partial = empty_tuple; 
   for( auto s : tup )
   {
      state next = create_state( );
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
  
   if( delta_char. size( ))
   {
      out << "Delta (char):\n";
      for( const auto& p : delta_char )
         out << "   " << p << "\n";
      out << "\n";
   }

   if( delta_usel. size( )) 
   {
      out << "Delta (usel):\n";
      for( const auto& f : delta_usel )
         out << "   " << f << "\n";
      out << "\n";
   }

   if( delta_u64. size( ))
   {
      out << "Delta (u64):\n";
      for( const auto& p : delta_u64 )
         out << "   " << p << "\n";
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

