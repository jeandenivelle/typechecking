#include <iostream>
#include "tree.h"
#include "selector.h"

void data::tree::print ( std::ostream& out ) const 
{
   switch( sel( )) 
   {
   case tree_never:
      out << view_never( ). n( ); 
      return;

   case tree_unit: 
      out << "trivial"; 
      return; 

   case tree_bool:
      if( view_bool( ). b( ))
         out << "true";	
      else
         out << "false";
      return; 

   case tree_char:
      out << '\'' << view_char(). c() << '\''; 
      return; 

   case tree_sel:
		out << view_sel(). s() << std::endl;
		break;

	case tree_u64:
		out << view_u64(). i() << std::endl;
		break;

	case tree_int:
		out << view_int(). i() << std::endl;
		break;

   case tree_double:
      out << view_double(). d( );
      return;

	case tree_tuple:
	{
		auto data_tuple = view_tuple();
		
		out << "( ";
		for( size_t i = 0; i < data_tuple. size(); ++i ) {
			if( i ) out << " ,";
			out << data_tuple. val(i);
		}
		out << " )";
	} break;

   case tree_array:
      {
         auto ar = view_array( );
		
         out << "[";
         for( size_t i = 0; i < ar. size(); ++ i ) 
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
