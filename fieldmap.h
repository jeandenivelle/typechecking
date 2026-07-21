
#ifndef FIELDMAP_
#define FIELDMAP_

#include "overloadmap.h"
#include "regexp/expr.h"

enum fieldtype { fld_scalar, fld_vector, fld_list };

const char* getcstring( fieldtype );

inline std::ostream& operator << ( std::ostream& out, fieldtype tp )
{
   out << getcstring( tp ); return out;
}

struct fielddef
{
   fieldtype tp;  
   regexp::expr precond;  
      // postcondition is read off from the tuple. 
      // Our types are strictly extensional. 
   size_t ind; 

   fielddef( fieldtype tp, 
             const regexp::expr& precond, 
             size_t ind ) 
      : tp( tp ),
        precond( precond ), 
        ind( ind )
   { }
   
   void print( std::ostream& out ) const; 
};


class fieldmap
{
   std::vector< fielddef > fields;
   overloadmap overloads;

public:
   fieldmap( ) noexcept = default;

   size_t insert( const identifier& ident, fielddef def );

   void print( std::ostream& out ) const; 
};

#endif
 
