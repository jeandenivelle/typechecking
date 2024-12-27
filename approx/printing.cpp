#include "approxterm.h"

void 
approx::approxterm::print
( std::ostream& out ) const
{
	switch( sel( ) )
	{
		case approxterm_empty:
		return;

		case approxterm_bool:
		out << view_bool( ). b( );
		return;

		case approxterm_char:
		out << view_char( ). c( );
		return;

		case approxterm_sel:
		out << view_sel( ). s( );
		return;

		case approxterm_u64:
		out << view_u64( ). i( );
		return;

		case approxterm_tuple:
		{
			const auto tuple = view_tuple( );
			out << '(';
			for( size_t i = 0; i < tuple. size( ); ++i )
			{
				if( i ) out << ", ";
				out << tuple. sub( i );
			}
			out << ')';
		}
		return;
	}
	
	out << "error: erratic::approxterm::print for " << sel( ) << " not implemented\n";
	throw std::runtime_error( "stop" );
}
