#ifndef _APPROX_APPROXMAP_
#define _APPROX_APPROXMAP_

#include <ostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "approximator.h"
#include "approxterm.h"
#include "util/print.h"

namespace approx
{
	// TODO How to hask an instance of approx::term?
	//using Aset = std::unordered_set< term >;

	using Aset = std::vector< approxterm >;
	using Amap = std::unordered_map< approximator, Aset, approximator::hash, approximator::equal_to >;
	
	class approxmap
	{
		Amap mp;
	
	public:
		approxmap( ) noexcept = default;
	
		bool                 insert ( const approximator, const Aset& );	
		Amap::iterator       find   ( const approximator );
		Amap::const_iterator find   ( const approximator ) const;
		void                 print  ( std::ostream& ) const;
	};	
}

#endif
