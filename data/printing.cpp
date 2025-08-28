#include <iostream>
#include "tree.h"
#include "selector.h"

void
data::tree::print
( std::ostream& out ) const 
{
	switch( sel() ) {
	case prim_empty:
		return;

	case prim_bool:
		if( view_bool(). b() )
			out << "true" << std::endl;	
		else
			out << "false" << std::endl;
		return;

	case prim_char:
		out << view_char(). c() << std::endl;
		return;

    case prim_sel:
		out << view_sel(). s() << std::endl;
		return;

	case prim_u64:
		out << view_u64(). i() << std::endl;
		return;

	case prim_int:
		out << view_int(). i() << std::endl;
		return;

	case prim_double:
		out << view_double(). d() << std::endl;
		return;

	default:
		std::cerr << "data::tree::print() : unrecognized selector : " << sel() << '\n' << std::endl;
		throw std::runtime_error( "data::tree::print() : unrecognized selector" );
	}
}
