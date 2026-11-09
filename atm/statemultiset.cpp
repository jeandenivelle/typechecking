
#include <algorithm>

#include "statemultiset.h"

atm::statemultiset::statemultiset( std::vector< state > word )
{
   std::sort( word. begin( ), word. end( ), state::less( ));

   for( auto it = word. begin( ); it != word. end( ); ++ it )
   {
      if( it == word. begin( ) || it[-1] != it[0] )
         repr. push_back( triple( *it, 1, 0 ));
      else
         ++ repr. back( ). freq;
   }

   prod = 1;
   for( auto& s : repr )
   {
      s. skip = prod;
      prod *= s. freq + 1;
   }
}


void atm::statemultiset::print( std::ostream& out ) const
{
   out << "Statemultiset( #" << prod; 
   for( auto p = repr. begin( ); p != repr. end( ); ++ p )
   {
      if( p == repr. begin( ))
         out << "; ";
      else
         out << ", ";
      out << *p;
   }
   out << " )";
}


