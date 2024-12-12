
#ifndef FLOWGRAPH_BODY_
#define FLOWGRAPH_BODY_

#include <map>
#include <vector>
#include "util/print.h"
#include "label.h"
#include "statement.h"

namespace flowgraph
{
   struct body
   {
      std::map< label, statement > code;

      body( ) noexcept = default;

#if 0
		transition( const programpoint& pred,
					const statement&   stmnt,
					const programpoint& succ ):
			pred( pred ), stmnt( stmnt ), succ( succ ) { }

		void print( std::ostream& ) const;
	};
	
#endif


      void print( std::ostream& out ) const
      {
         for( const auto& p : code )
         {
            out << p. first << ":\n";
            p. second. print( indentation(3), out );
            out << "\n";
         }
      }
   };
}

#endif
