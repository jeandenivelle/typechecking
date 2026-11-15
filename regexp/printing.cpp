
#include <stdexcept>

#include "expr.h"
#include "exprtype.h"


void 
regexp::expr::print( std::ostream& out ) const
{
   switch( sel( ))
   {
   
   case flt_bool:
      out << view_filter_bool( ). func( );
      return; 

   case flt_char:
      out << view_filter_char( ). func( );
      return;

   case flt_sel:
      out << view_filter_sel( ). func( ); 
      return;

   case flt_u64:
      out << view_filter_u64( ). func( );
      return;

   case ref_ident:
      out << view_reference( ). ident( ); 
      return;

   case tup_exact:
   case tup_prefix:
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
      {
         auto log = view_disjunction( );
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

   case set_word:
      {
         auto wrd = view_word( );
         out << sel( ) << "(";
         for( size_t i = 0; i != wrd. size( ); ++i ) 
         {
            if(i) 
               out << ", ";
            else
               out << " ";
            out << wrd. smp(i);  
         }
         out << " )"; 
         return;
      }

   case set_linear:
   case set_circular:
      {
         auto mult = view_multiply( );

         out << sel( ) << "( ";
         out << mult. set( ) << ", " << mult. factor( ) << ", {";
         for( size_t i = 0; i != mult. size( ); ++i )
         {
            if(i)   
               out << ", ";
            else
               out << " ";
            out << mult. disj(i);
         }
         out << " } )";   
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


