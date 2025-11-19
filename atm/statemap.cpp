
#include "statemap.h"

void atm::statemap::print( std::ostream& out ) const
{
   out << "Statemap:\n";
   for( const auto& p : map )
      out << "   " << p. first << " : " << p. second << "\n";
   out << "\n";
}


std::string atm::state2str( const state& state, const statemap& smap ) {
   auto it = smap. find( state );
   if( it == smap. end() ) {
      return "";
   }
   return it-> first;
}
