#include "state.h"

bool state::insert
( exactident key, const data::tree& val )
{
	if( !mp. contains( key. id ) )
	{
		state::mpmp_t mpmp;
		mpmp. insert( { key. ind, val } );
		auto res = mp. insert( { key. id, mpmp } );
		return res. second;
	}
	
	state::mpmp_t mpmp = mp. at( key. id );
	auto res = mpmp. insert( {key. ind, val } ); 
	return res. second;
}

bool state::insert
( exactident key, const data::tree&& val )
{ return insert( key, std::move(val) ); }

/* The find return a pair of iterator for outer map and iner map.
 * 
 * if key does not exists in outer map, it returns a pair of
 *  outer map end iterator and some arbitrary iterator (don't 
 *  sure where it points).
 *
 * if key does not exist in inner map, it returns a pair of
 *  a valid outer map iterator and inner map end iterator.
 *
 * The const find operates in the same way.
 */
state::iter_pair 
state::find( exactident key )
{
	state::iter1 it1 = mp. find( key. id );
	if( it1 == mp. end( ) )
		return { it1, state::iter2{} };

	state::iter2 it2 = it1-> second. find( key. ind );
	return { it1, it2 };
}

state::const_iter_pair 
state::find( exactident key ) const
{
	state::const_iter1 it1 = mp. find( key. id );
	if( it1 == mp. end( ) )
		return { it1, state::const_iter2{} };

	state::const_iter2 it2 = it1-> second. find( key. ind );
	return { it1, it2 };
}

void state::print
( std::ostream& out ) const
{
	out << "State:\n";
	for( const auto& vt1 : mp )
		for( const auto& vt2 : vt1. second )
		{
			out << '\t' << exactident( vt1. first, vt2. first );
			out << " := " << vt2. second << '\n';
		}
}
