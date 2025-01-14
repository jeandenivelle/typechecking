#ifndef _RANGESTATE_
#define _RANGESTATE_

#include <ostream>
#include <list>
#include <vector>

#include "util/print.h"
#include "setterm/setterm.h"
#include "setterm/atom.h"


/*
 * TODO still think through the filter functions thing. Not sure yet it works. 
 */

class rangestate
{
	using st_t = std::list< setterm::atom >;
	using iter = st_t::iterator;
	using const_iter = st_t::const_iterator;
	using filter_func_t = bool (*) ( const st_t::value_type& );

	st_t st;

public:	
	rangestate( ) noexcept = default;

	size_t size( ) const { return st. size( ); }
	
	bool contains( const setterm::atom& ) const;

	bool insert( const setterm::atom& );

	iter find( filter_func_t );
	const_iter find( filter_func_t ) const;

	std::vector< iter > findall( filter_func_t );
	std::vector< const_iter > findall( filter_func_t ) const;

	void remove( iter );
	void removeall( std::vector< iter >& );

	void print( std::ostream& ) const;	
};
#endif
