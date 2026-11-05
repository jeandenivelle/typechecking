
#include "simple.h"

void 
atm::simple::addtuple( const std::vector< state > & tup, state goal )
{
   std::cout << "adding tuple transition:";
   for( auto s : tup ) std::cout << s << " ";
   std::cout << " -> " << goal << "\n";

#if 0 
   state partial = empty_tuple; 
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
#endif

   // Now partial became total.
#if 0
   std::cout << "reached " << partial << "\n";

   // We create an epsilon transition to goal:

   delta_eps[ partial ]. insert( goal );
#endif
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
   }

   if( delta_usel. size( )) 
   {
      out << "Delta (usel):\n";
      for( const auto& t : delta_usel )
         out << "   " << t << "\n";
      out << "\n";
   }

#if 0
   out << "Tuple transitions:\n";
   out << "Empty: " << empty_tuple << "\n";
   for( const auto& set : delta_tup )
      for( const auto& ins : set. second )
      {
         out << "   " << set. first << " * " << ins. first;
         out << " -> " << ins. second << "\n";
      }
   out << "\n";
#endif
   out << "Set transitions:\n"; 
   out << "   <empty> -> " << empty_set << "\n";
   for( const auto& d : delta_set )
   {
      out << "   " << d. first. first << ", " << d. first. second;
      out << " -> " << d. second << "\n";
   }
   out << "\n";
#if 0
   out << "Epsilon Transitions:\n"; 
#endif

#if 0
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
#endif
}

