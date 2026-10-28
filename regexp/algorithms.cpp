
#include "algorithms.h"
#include <stdexcept>

void 
regexp::collect( const expr& e,
                 identifier::set& defs, size_t& c )
{
   ++ c;

   switch( e. sel( ))
   {
   case type_never:
   case type_unit:
   case type_bool:
   case type_char: 
   case type_sel:
   case type_u64:
   case type_integer:
   case type_double:
   case type_iter:
      return;  
  
   case flt_sel:
      return;

   case ref_ident:
      // Here we count an identifier!

      defs. insert( e. view_reference( ). ident( ));
      return;

   case tup_constr:
   case tup_concat:
      {
         auto tup = e. view_tuple( );
         for( size_t i = 0; i != tup. size( ); ++ i )
            collect( tup. sub(i), defs, c ); 
         return;
      }

   case log_and:
   case log_or:
      {
         auto log = e. view_logical( );
         for( size_t i = 0; i != log. size( ); ++ i )
            collect( log. sub(i), defs, c );
         return;
      }
   case set_single:
   case set_repeat:
      collect( e. view_set_unary( ). sub( ), defs, c );
      return;
   }
   std::cout << "unknown selector in regexp::collect:  " << e. sel( ) << "\n";
   throw std::logic_error( "regexp::collect" ); 
}


