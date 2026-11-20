
#include "algorithms.h"
#include <stdexcept>
#include <queue>

void 
regexp::collect( const expr& e,
                 identifier::set& defs, size_t& c )
{
   ++ c;

   switch( e. sel( ))
   {
   case type_never:
   case type_unit:
   case flt_bool:
   case flt_char:
   case flt_sel:
   case flt_u64:
   case flt_integer:
   case type_double:
      return;  
  
   case ref_ident:
      // Here we count an identifier!

      defs. insert( e. view_reference( ). ident( ));
      return;

   case tup_constr:
      {
         auto tup = e. view_tuple( );
         for( size_t i = 0; i != tup. size( ); ++ i )
            collect( tup. sub(i), defs, c ); 
         return;
      }

   case log_or:
      {
         auto log = e. view_disjunction( );
         for( size_t i = 0; i != log. size( ); ++ i )
            collect( log. sub(i), defs, c );
         return;
      }
#if 0
   case single2set:
      collect( e. view_single2set( ). elem( ), defs, c ); 
      return;

   case set2single:
      collect( e. view_set2single( ). sub( ), defs, c );
      return; 
#endif
   }

   std::cout << "unknown selector in regexp::collect:  " << e. sel( ) << "\n";
   throw std::logic_error( "regexp::collect" ); 
}


identifier::map< identifier::set > 
regexp::dependencymap( const defmap& defs )
{
   identifier::map< identifier::set > res;

   for( const auto& d : defs )
   {
      identifier::set used;
      size_t cntr = 0;
      collect( d. second, used, cntr );

      res. emplace( d.first, std::move( used )); 
   }

   return res; 
}


