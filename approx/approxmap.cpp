#include "approxmap.h"

bool 
approx::approxmap::insert
( approx::approximator a,
  const approx::Aset& st )
{
	auto res = mp. insert( {a, st} );
	return res. second;
}	

approx::Amap::iterator
approx::approxmap::find
( const approx::approximator a )
{ return  mp. find( a ); }

approx::Amap::const_iterator
approx::approxmap::find
( const approx::approximator a ) const
{ return mp. find( a ); }

void
approx::approxmap::print
( std::ostream& out ) const
{
	out << "Approximation Map\n";
	for( const auto& p : mp )
	{
		out << '\t' << p. first << '{';
		const auto aset = p. second;  
		for( approx::Aset::const_iterator iter =  aset. begin( );
		     iter != aset. end( ); iter++ )
		{
			if( iter != aset. begin( ) ) out << ", ";
			out << *iter;
		}
		out << "}\n";
	}
}
