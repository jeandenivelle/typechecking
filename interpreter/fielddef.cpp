
#include "fieldmap.h"

const char* getcstring( fieldtype tp )
{
   switch( tp )
   {
   case fld_scalar:
      return "scalar";
   case fld_vector:
      return "vector";
   case fld_list:
      return "list";
   }
   return "???"; 
}


void fielddef::print( std::ostream& out ) const
{
   out << tp << " on " << precond << " with index " << ind;
}


size_t fieldmap::insert( const identifier& ident, fielddef def )
{
   size_t s = fields. size( );
   overloads. add( ident, s );
   fields. push_back( std::move( def ));  
   return s; 
}

void fieldmap::print( std::ostream& out ) const
{
   out << "Fieldmap:\n";
   for( size_t i = 0; i != fields. size( ); ++ i )
      out << "   " << i << " : " << fields[i] << "\n";
   out << overloads << "\n";
}

 
