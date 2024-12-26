
#ifndef FIELDMAP_
#define FIELDMAP_

#include "prop/expr.h"
#include "exactident.h"

enum fieldtype { fld_scalar, fld_vector, fld_list };

const char* getcstring( fieldtype );

inline std::ostream& operator << ( std::ostream& out, fieldtype tp )
{
   out << getcstring( tp ); return out;
}

struct fielddef
{
   fieldtype tp;  
   prop::expr precond;  
      // postcondition is read off from the tuple. 
      // Our types are strictly extensional. 
   size_t ind; 

   fielddef( fieldtype tp, 
             const prop::expr& precond, 
             size_t ind ) 
      : tp( tp ),
        precond( precond ), 
        ind( ind )
   { }
   
   void print( std::ostream& out ) const; 
};


class fieldmap
{
   exactidentmap< fielddef > mp; 

public:
   fieldmap( ) noexcept = default;

   bool insert( exactident id, const fielddef& def );
      // True if the insertion happened, we refuse to overwrite. 

   void print( std::ostream& out ) const; 
};

#endif
 
