#include "term.h"

void
setterm::term::print
( std::ostream& out ) const
{
	switch( sel() )
	{
	case  prim_never:
	case  prim_unit:
	out << sel( );
	return;

	case prim_bool:
	out << view_bool( ). b( );
	return;

	case prim_char:
	out << view_char( ). c( );
	return;
	
	case prim_sel:
	out << view_sel( ). s( );
	return;

	case prim_u64:
	out << view_u64( ). i( );
	return;

	case prim_iter:
	out << view_iter( ). s( );
	return;

	case prim_integer:
	out << "bigint";
	return;	
	
	case prim_double:
	out << view_double( ). d( );
	return;

	case term_tuple:
	case term_set:
	{
		if( sel( ) == term_set ) out << "set";
		auto rep = view_repeated( );
		out << '(';
		for( size_t i = 0; i < rep. size( ); ++i )
		{
			if( i ) out << ", ";
			out << rep. sub( i );
		}
		out << ')';
	}
	return;
	}

	out << "error: unhandles setterm selector in print function: " << sel( ) << '\n';
	throw std::runtime_error( "stop" );	
}
