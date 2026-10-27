#include <iostream>
#include "tree.h"
#include "selector.h"

void data::tree::print ( std::ostream& out ) const 
{
   switch( sel( )) 
   {
   case sel_never:
      out << view_never( ). n( ); 
      return;

   case sel_unit: 
      out << "trivial"; 
      return; 

   case sel_bool:
      if( view_bool( ). b( ))
         out << "true";	
      else
         out << "false";
      return; 

   case sel_char:
      out << '\'' << view_char(). c( ) << '\''; 
      return; 

   case sel_usel:
      out << view_usel( ). s( );
      return;

   case sel_u64:
      out << view_u64( ). i( );
      return;

   case sel_bigint:
      out << view_bigint( ). i( );
      return;

   case sel_double:
      out << view_double(). d( );
      return;

   case sel_tuple:
      {
         auto t = view_tuple( );
		
         out << "(";
         for( size_t i = 0; i < t. size( ); ++ i ) 
         {
            if(i) 
               out << ", ";
            else
               out << " ";
            out << t. val(i);
         }
         out << " )";
         return;
      } 

   case sel_array:
      {
         auto ar = view_array( );
		
         out << "[";
         for( size_t i = 0; i < ar. size( ); ++ i ) 
         {
            if(i) 
               out << ", ";
            else
               out << ' ';
            out << ar. val(i);
         }
         out << " ]";
         return;
      }

   default:
      std::cerr << "data::tree::print() : unrecognized selector : " << sel() << '\n' << std::endl;
      throw std::runtime_error( "data::tree::print() : unrecognized selector" );
   }
}
