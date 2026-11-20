#include <iostream>
#include "tree.h"
#include "selector.h"

void data::tree::print ( std::ostream& out ) const 
{
   switch( sel( )) 
   {
   case dat_never:
      out << view_never( ). n( ); 
      return;

   case dat_unit: 
      out << "trivial"; 
      return; 

   case dat_bool:
      if( view_bool( ). b( ))
         out << "true";	
      else
         out << "false";
      return; 

   case dat_char:
      out << '\'' << view_char(). c( ) << '\''; 
      return; 

   case dat_sel:
      out << view_usel( ). s( );
      return;

   case dat_u64:
      out << view_u64( ). u( );
      return;

   case dat_integer:
      out << view_integer( ). i( );
      return;

   case dat_double:
      out << view_double(). d( );
      return;

   case dat_tuple:
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

   case dat_array:
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
