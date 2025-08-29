#include <iostream>
#include "tree.h"
#include "selector.h"

void
data::tree::print
( std::ostream& out ) const 
{
	switch( sel() ) {
	case tree_empty:
		break;

	case tree_bool:
		if( view_bool(). b() )
			out << "true" << std::endl;	
		else
			out << "false" << std::endl;
		break;

	case tree_char:
		out << view_char(). c() << std::endl;
		break;

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
		out << view_double(). d() << std::endl;
		break;

	case tree_tuple:
	{
		auto data_tuple = view_nary();
		
		out << "( ";
		for( size_t i = 0; i < data_tuple. size(); ++i ) {
			if( i ) out << " ,";
			out << data_tupe. vect(i);
		}
		out << " )";
	} break;

	case tree_array:
	{
		auto data_array = view_nary();
		
		out << "( ";
		for( size_t i = 0; i < data_array. size(); ++i ) {
			if( i ) out << " ,";
			out << data_array. vect(i);
		}
		out << " )";
	} break;

	default:
		std::cerr << "data::tree::print() : unrecognized selector : " << sel() << '\n' << std::endl;
		throw std::runtime_error( "data::tree::print() : unrecognized selector" );
	}
}
