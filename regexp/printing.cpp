
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
   case tup_concat:
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

   case set_single:
   case set_repeat:
      out << sel( ) << "( " << view_set_unary( ). sub( ) << " )";
      return;

   case set_union:
      {
         out << sel( ) << "(";
         auto un = view_set_union( );
         for( size_t i = 0; i != un. size( ); ++i )
         {
            if(i)   
               out << ", ";
            else
               out << " ";
            out << un. sub(i);
         }
         out << " )";   
      }
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
   case exprtype_singleval:
      out << "singleval";
      return;
   case exprtype_tuple:
      out << "tuple(" << view_tuple( ). arity( ) << ")";
      return;
   case exprtype_set:
      out << "set";
      return;
   }

   std::cout << "printing exprtype, unknown selector: " << sel( ) << "\n";
   throw std::logic_error( "unknown selector" );
}

