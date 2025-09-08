#include <iostream>
#include "state.h"

void
dma::state::print
( std::ostream& out ) const 
{
	switch( sel() ) {
	case state_emptyt:
	case state_emptys:
		break;
	
	case state_bool:
		if( view_bool(). b() )
			out << "q_bool( true )" << std::endl;
		else
			out << "q_bool( false )" << std::endl;
		break;

	case state_char:
		out << "q_char( " << view_char(). c() << " )" << std::endl;
		break;

	case state_sel:
		out << "q_sel( " << view_sel(). s() << " )" << std::endl;
	   	break;

	case state_u64:
		out << "q_u64( " << view_u64(). i() << " )" << std::endl;
		break;

	case state_int:
	   	out << "q_int( " << view_int(). i() << " )" << std::endl;
		break;

	case state_double:
		out << "q_double( " << view_double(). d() << " )" << std::endl;
		break;

	case state_tuple:
	{
		auto state_tuple = view_tuple();
		out << "( ";
		for( size_t i = 0; i < state_tuple. size(); ++i ) {
			if( i ) out << ", ";
			out << state_tuple. vect(i);
		}
		out << " )";
	} break;

	case state_mset:
	{
		auto state_mset = view_mset();
		out << "{ " << state_mset. scal1() << " : ";
		out << state_mset. scal2() << " }" << std::endl;
	} break;

	default:
		std::cerr << "dma::state::print() : unrecognized selector : " << sel() << std::endl;
		throw std::runtime_error( "dma::state::print() : unrecognized selector" );
	}
}

