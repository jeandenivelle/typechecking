
#include <iostream>
#include <list>

#include "fieldmap.h"
#include "identifier.h"
#include "usel.h"
#include "exactident.h"

#include "data/tree.h"

#include "tests.h"

#include "intermediate/point.h"
#include "intermediate/variable.h"
#include "intermediate/flatterm.h"
#include "intermediate/statement.h"

#include "approx/approximator.h"
#include "approx/approxterm.h"
#include "approx/approxmap.h"

#include "setterm/term.h"

int main( int argc, char* argv [] )
{
   auto flat = intermediate::flatterm( intermediate::flat_some_bool );
 
   std::cout << flat << "\n";
 
#if 0
   flowgraph::body bod;

   // test_scalar_list( );

#endif

#if 0
   parsing::parser prs( simpmap, compmap, adjmap, funcmap, 
                        errors, toplevelspace, filespace, tok ); 
 
   prs. debug = 3; 
   std::cout << "not even started\n";

   parsing::symbol sym = prs. parse( parsing::sym_File ); 
   std::cout << "parser returned " << sym << "\n";

   for( const auto& e : errors )
      std::cout << e << "\n";

   if( filespace ) 
      std::cout << "filespace = " << filespace. value( ) << "\n";
   else
      std::cout << "no filespace was set\n";

   tvm::printselectorenum( std::cout );

   return 0;
#endif
 
   fieldmap flds;
   prop::defmap prp;

   tests::add_nat( prp, flds );
   tests::add_fol( prp, flds );

   std::cout << prp << "\n";
   std::cout << flds << "\n";

   auto f = tests::mixing( );
   // auto f = tests::repeated( );
   std::cout << f << "\n";
   f = tests::arrayconv( );
   std::cout << f << "\n";

   return 0;

   // adj::overloadmap adjover;

   // natural( types, adjmap, fields, adjover );
   // firstorder( compmap, adjmap, fields, adjover );

   // std::cout << simpmap << "\n";
   // std::cout << compmap << "\n";
   // std::cout << adjmap << "\n";
   // std::cout << fields << "\n";
   //  std::cout << adjover << "\n";

#if 0
   types. insert( { "modal", modal( ) } ); 
   std::cout << types << "\n";
   return 0;

   auto nnf = exactname( "nnf" );

   adjmap. insert( { nnf, adj::def( new type::fullident( "fol" ), tr ) } );
#endif

   // modaladjectives( adjmap );

   return 0;	
}

