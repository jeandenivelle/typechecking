
#include "defmap.h"

bool regexp::defmap::contains( const identifier& ident ) const
{
   return mp. find( ident ) != mp. end( );
}

bool regexp::defmap::insert( const identifier& ident, const expr& e )
{
   auto p = mp. insert( std::pair( ident, e ));
   return p. second;
}

void regexp::defmap::print( std::ostream& out ) const
{
   out << "Regular Expression Definitions:\n";
   for( const auto& def : mp )
      out << "   " << def. first << " := " << def. second << "\n";
   out << "\n";
}


