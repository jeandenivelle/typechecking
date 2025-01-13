#include "setterm.h"
#include "atom.h"

void
setterm::setterm::print
( std::ostream& out ) const
{
	switch( sel() )
	{
	case  setterm_never:
	case  setterm_unit:
	out << sel( );
	return;

	case setterm_bool:
	out << view_bool( ). b( );
	return;

	case setterm_char:
	out << view_char( ). c( );
	return;
	
	case setterm_sel:
	out << view_sel( ). s( );
	return;

	case setterm_u64:
	out << view_u64( ). i( );
	return;

	case setterm_iter:
	out << view_iter( ). s( );
	return;

	case setterm_integer:
	out << "bigint";
	return;	
	
	case setterm_double:
	out << view_double( ). d( );
	return;

	case setterm_tuple:
	case setterm_set:
	{
		if( sel( ) == setterm_set ) out << "set";
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

void
setterm::atom::print
( std::ostream& out ) const
{
	switch( sel( ) )
	{
	case atom0:
	return;

	case atom1:
	{
		auto a = view_atom1( );
		out << a. v( ) << '/' << a. s( ); 
	}
	return;

	case atom2:
	{
		auto a = view_atom2( );
		out << a. v( ) << '[' << a. i( ) << "]/" << a. s( );
	}
	return;

	case atom3:
	{
		auto a = view_atom3( );
		out << a. v( ) << '[' << a. t1( ) << " ... " << a. t2( ) << "]/"  << a. s( );
	}
	return;

	case atom4:
	{
		auto a = view_atom4( );
		out << "delta(" << a. t1( ) << ", " << a. t2( ) << '[';
	    for( size_t i = 0; i < a. size( ); ++i )
		{
			if( i ) out << ", ";
			out << a. s( i );
		}
		out << ']';
	}
	return;
	}

	out << "error: unhandled atom selector in print function: " << sel( ) << '\n';
	throw std::runtime_error( "stop" );
}
