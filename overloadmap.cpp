
#include "overloadmap.h"


void overloadmap::add( const identifier& id, size_t ind )
{
   mp[ id ]. push_back( ind );
}

void overloadmap::print( std::ostream& out ) const
{
   out << "Overloads:\n";
   for( auto& id : mp )
   {
      out << "   " << id. first << " : { ";
      for( auto p = id. second. begin( ); p != id. second. end( ); ++ p )
      {
         if( p != id. second. begin( ))
            out << ", ";
         out << *p;
      }
      out << " }\n";
   }
}

