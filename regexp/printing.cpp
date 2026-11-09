
#include <stdexcept>

#include "expr.h"
#include "exprtype.h"


void 
regexp::expr::print( std::ostream& out ) const
{
   switch( sel( ))
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

   case ref_ident:
      out << view_reference( ). ident( ); 
      return;

   case tup_constr:
      {
         auto tp = view_tuple( ); 
         out << sel( ) << "(";
         for( size_t i = 0; i != tp. size( ); ++ i )
         {
            if(i) 
               out << ", ";
            else
               out << " ";
            out << tp. sub(i);
         }
         out << " )"; 
      }
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

   case single2set:
      {
         auto sg = view_single2set( );
         if( sg. period( ) < 1000000 ) 
         {
            out << sel( ) << "( " << sg. elem( ) << ", ";
            out << sg. nr( ) << " mod " << sg. period( ) << " )";
         }
         else
            out << sel( ) << "( " << sg. elem( ) << ", " << sg. nr( ) << " )"; 
         return;
      }

   case concat:
      {
         out << sel( ) << "[";
         auto ch = view_concat( );
         for( size_t i = 0; i != ch. size( ); ++i )
         {
            if(i)   
               out << ", ";
            else
               out << " ";
            out << ch. sub(i);
         }
         out << " ]";   
      }
      return; 

   case set2single:
      out << sel( ) << "( " << view_set2single( ). sub( ) << " )";
      return;

   }

   std::cout << "printing a regexp, unknown selector: " << sel( ) << "\n";
   throw std::logic_error( "unknown selector" );
}


void 
regexp::exprtype::print( std::ostream& out ) const
{
   switch( sel( ))
   {     
   case exprtype_single:
      out << "single";
      return;
   case exprtype_set:
      out << "set";
      return;
   case exprtype_unknown:
      out << "unknown";
      return; 
   case exprtype_error:
      out << "error";
      return; 
   }

   std::cout << "printing exprtype, unknown selector: " << sel( ) << "\n";
   throw std::logic_error( "unknown selector" );
}


