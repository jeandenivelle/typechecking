#include "rangestate.h"
#include <utility>

bool rangestate::contains
( const setterm::atom& at1 ) const
{
	setterm::atom::equal_to eq;
	for( const auto& at2 : st )
		if( eq( at1, at2 ) ) 
			return true;
	return false;
}

bool rangestate::insert
( const setterm::atom& at )
{ 
	if( contains( at ) )
		return false;

	st. push_back( at );
	return true;
}

rangestate::iter
rangestate::find( filter_func_t filter )
{
	for( iter it = st. begin( ); it != st. end( ); ++it )
		if( filter( *it ) ) return it;
	return st. end( );
}

rangestate::const_iter
rangestate::find( filter_func_t filter ) const
{
	for( const_iter it = st. begin( ); it != st. end( ); ++it )
		if( filter( *it ) ) return it;
	return st. end( );
}


std::vector< rangestate::iter >
rangestate::findall( filter_func_t filter )
{
	std::vector< iter > res;
	
	for( iter it = st. begin( ); it != st. end( ); ++it )
		if( filter( *it ) ) res. push_back( it );
	
	return res;
}

std::vector< rangestate::const_iter >
rangestate::findall( filter_func_t filter ) const
{
	std::vector< const_iter > res;

	for( const_iter it = st. begin( ); it != st. end( ); ++it )
		if( filter( *it ) ) res. push_back( it );

	return res;
}

void rangestate::remove( iter it )
{ st. erase( it ); }

void rangestate::removeall
( std::vector< iter >& vec )
{ for( iter& it : vec ) st. erase( it ); }

void rangestate::print
( std::ostream& out ) const
{
	out << "Range State:\n";
	for( const auto& at : st )
		out << '\t' << at << '\n';	
}
