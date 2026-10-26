
#include "expr.h"

void 
regexp::expr::print( std::ostream& out ) const
{
   switch( sel( ) )
   {
   case type_never: 
   case type_unit: 
   case type_bool: 
   case type_char: 
   case type_sel:  
   case type_u64: 
   case type_iter:
   case type_integer: 
   case type_double:
      out << sel( );
      return; 

   case flt_bool:
      out << view_filter_bool( ). b( );
      return; 

   case flt_sel:
      out << view_filter_sel( ). fin( ); 
      return;

   case flt_char:
      out << view_filter_char( ). part( );
      return;

      case ident:
         out << view_ident( ). ident( ); 
         return;

      case tup_constr:
         {
            auto tup = view_tuple( ); 
            out << "tuple("; 
            for( size_t i = 0; i != tup. size( ); ++ i )
            {
               if(i) 
                  out << ", ";
               else
                  out << " ";
               out << tup. sub(i);
            }
            out << " )"; 
         }
         return; 

      case tup_concat:
         out << view_concat( ). first( ) << " @ " << view_concat( ). second( ); 
         return; 

      case log_or:
      case log_and:
         {
            auto log = view_logical( );
            out << sel( ) << "{";
            for( size_t i = 0; i != log. size( ); ++i )
            {
               if(i)  
                  out << ", ";
               else
                  out << " ";
               out << log. sub(i);
            }
            out << " }"; 
         }
         return; 

   case set_exists:
   case set_forall:
      {
         switch( sel( ))
         {
         case set_exists:
            out << "exists"; break;
         case set_forall:
            out << "forall"; break;
         default:
            out << "???"; break;
         }
         out << "( " << view_set( ). sub( ) << " )";
         return; 
      }
   }

}


