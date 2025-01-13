#include "setterm.h"
#include "atom.h"

bool
setterm::setterm::equal_to::operator()
( const setterm& s1,
  const setterm& s2 ) const 
{
	if( s1. sel( ) != s2. sel( ) )
		return false;

	switch( s1. sel( ) )
	{
	case  setterm_never:
	case  setterm_unit:
	return true;

	case setterm_bool:
	return s1. view_bool( ). b( ) == s2. view_bool( ). b( );

	case setterm_char:
	return s1. view_char( ). c( ) == s2. view_char( ). c( );
	
	case setterm_sel:
	return s1. view_sel( ). s( ) == s2. view_sel( ). s( );

	case setterm_u64:
	return s1. view_u64( ). i( ) == s2. view_u64( ). i( );

	case setterm_iter:
	return s1. view_iter( ). s( ) == s2. view_iter( ). s( );

	case setterm_integer:
	return s1. view_integer( ). i( ) == s2. view_integer( ). i( );
	
	case setterm_double:
	return s1. view_double( ). d( ) == s2. view_double( ). d( );

	case setterm_tuple:
	case setterm_set:
	{
		auto v1 = s1. view_repeated( );
		auto v2 = s2. view_repeated( );

		if( v1. size( ) != v2. size( ) )
			return false;

		for( size_t i = 0; i < v1. size( ); ++i )
			if( v1. sub( i ) != v2. sub( i ) )
			   return false;	
	}
	return true;
	}

	throw std::runtime_error( "unhandled setterm selector at setterm::equal_to::opeartor()\n" );
}

bool
setterm::atom::equal_to::operator() 
( const atom& a1, 
  const atom& a2 ) const
{
	if( a1. sel( ) != a2. sel( ) )
		return false;

	switch( a1. sel( ) )
	{
	case atom0:
	return true;

	case atom1:
	{
		auto v1 = a1. view_atom1( );
		auto v2 = a2. view_atom1( );
		
		return v1. v( ) == v2. v( ) &&
			   v1. s( ) == v2. s( );
	}

	case atom2:
	{
		auto v1 = a1. view_atom2( );
		auto v2 = a2. view_atom2( );
		
		return v1. v( ) == v2. v( ) &&
		       v1. i( ) == v2. i( ) &&	
			   v1. s( ) == v2. s( );
	}

	case atom3:
	{
		auto v1 = a1. view_atom3( );
		auto v2 = a2. view_atom3( );
		
		return v1. v( ) == v2. v( ) &&
		       v1. t1( ) == v2. t1( ) &&
		       v1. t2( ) == v1. t2( ) &&	   
			   v1. s( ) == v2. s( );
	}

	case atom4:
	{
		auto v1 = a1. view_atom4( );
		auto v2 = a2. view_atom4( );
		
		if( v1. t1( ) != v2. t1( ) ||
			v1. t2( ) != v1. t2( ) ||
			v1. size( ) != v2. size( ) )
			return false;

		for( size_t i = 0; i < v1. size( ); ++i )
			if( v1. s( i ) != v2. s( i ) )
				return false;
	}
	return true;
	}

	throw std::runtime_error( "unhandled atom selector at atom::equal_to::operator()\n" );
}
