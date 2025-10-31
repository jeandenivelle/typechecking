
#include "statemap.h"

void atm::statemap::print( std::ostream& out ) const
{
   out << "Statemap:\n";
   for( const auto& p : map )
      out << "   " << p. first << " : " << p. second << "\n";
   out << "\n";
}

