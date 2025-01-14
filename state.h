#ifndef _STATE_
#define _STATE_

#include <ostream>

#include "exactident.h"
#include "data/tree.h"
#include "util/print.h"

class state
{	
	using mp_t = exactidentmap< data::tree >;
	using mpmp_t = mp_t::mapped_type;

	using iter1 = mp_t::iterator;
	using iter2 = mpmp_t::iterator;
	
	using const_iter1 = mp_t::const_iterator;
	using const_iter2 = mpmp_t::const_iterator;
	
	using iter_pair = std::pair< iter1, iter2 >;
	using const_iter_pair = std::pair< const_iter1, const_iter2 >;

	mp_t mp;

public:
	state( ) noexcept = default;
	
	size_t size( ) { return mp. size( ); }

	bool insert( exactident, const data::tree& );	
  	bool insert( exactident, const data::tree&& );

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
	iter_pair find( exactident );
	const_iter_pair find( exactident ) const;
	
	void print( std::ostream& ) const;
};

#endif
