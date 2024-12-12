
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
   out << tp << " " << precond << " / " << ind;
}

bool fieldmap::insert( exactident id, const fielddef& def )
{
   auto& forid = mp[ id. id ];
   auto p = forid. insert( { id. ind, def } );
   return p. second; 
}

void fieldmap::print( std::ostream& out ) const
{
   out << "Fieldmap:\n";
   for( const auto& id : mp )
   {
      for( const auto& ind : id. second )
      {
         out << "   ";
         out << exactident( id. first, ind. first );
         out << " : " << ind. second << "\n";
      }
   }
}

 
