
#include "simple.h"

#include <optional>

void atm::simple::addtuple( const std::vector< state > & tup, state goal )
{
   std::cout << "adding tuple transition:";
   for( auto s : tup ) std::cout << s << " ";
   std::cout << " -> " << goal << "\n";
 
   state partial = empty_tup; 
   for( auto s : tup )
   {
      auto p = delta_tup. find( partial );
      if( p == delta_tup. end( ))
         p = delta_tup. try_emplace( partial ). first;

      auto q = p -> second. find( s );
      if( q != p -> second. end( ))
         partial = q -> second;
      else 
      {
         partial = newstate( );
         p -> second. insert( { s,  partial } );
      }
   } 

   // Now partial became total.

   std::cout << "reached " << partial << "\n";

   delta_eps[ partial ]. insert( goal );

   // We need to create an epsilon transition to goal. 
}

void atm::simple::print( std::ostream& out ) const
{
   out << "Simple Automaton:\n";
   out << "   collapsed = " << collapsed << "\n\n";
   out << "Selector transitions:\n";
   out << "   " << delta_usel << "\n"; 

   out << "\n";

   out << "Tuple transitions:\n";
   out << "Empty: " << empty_tup << "\n";
   for( const auto& set : delta_tup )
      for( const auto& ins : set. second )
      {
         out << "   " << set. first << " * " << ins. first;
         out << " -> " << ins. second << "\n";
      }
   out << "\n";
   out << "Multiset transitions:\n"; 
   out << "Empty: " << empty_mset << "\n";
   for( const auto& set : delta_mset )
      for( const auto& ins : set. second )
      {
         out << "   " << set. first << " + " << ins. first;
         out << " -> " << ins. second << "\n";
      }
   out << "\n";
   out << "Epsilon Transitions:\n"; 
   for( const auto& eps : delta_eps )
   {
      out << "   " << eps. first << " -> ";
      for( auto p = eps. second. begin( ); p != eps. second. end( ); ++ p )
      {
         if( p != eps. second. begin( ))
            out << ", ";
         out << *p;
      }
      out << "\n";
   }
  
}

