
#include "defmap.h"

bool regexp::defmap::contains( const identifier& ident ) const
{
   return mp. find( ident ) != mp. end( );
}

bool regexp::defmap::insert( const identifier& ident, expr e, exprtype tp )
{
   auto p = mp. emplace( ident, value( std::move(e), std::move(tp)) );
   return p. second;
}

void regexp::defmap::print( std::ostream& out ) const
{
   out << "Regular Expression Definitions:\n";
   for( const auto& def : mp )
   {
      out << "   " << def. first << " := ";
      out << def. second. e << " : " << def. second. tp << "\n";
   }
   out << "\n";
}


