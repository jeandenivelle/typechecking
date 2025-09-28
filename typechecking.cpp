
#include <iostream>

//#include "fieldmap.h"
//#include "identifier.h"
#include "usel.h"
//#include "exactident.h"

#include "data/tree.h"

//#include "tests.h"

//#include "intermediate/point.h"
//#include "intermediate/variable.h"
//#include "intermediate/flatterm.h"
//#include "intermediate/statement.h"

#include "atm/finitefunction.h"
#include "atm/borderfunction.h"
//#include "approx/approxmap.h"

//#include "state.h"
#include "diff/approxset.h"

int main( int argc, char* arcgv[] ) {

   diff::approxset set1;
   set1. insert( -2 );
   set1. insert( -3 );
   set1. insert( 0 );
   std::cout << set1 << "\n";

   diff::approxset set2;
   set2. insert( 1 );
   set2. insert( 2 );
   std::cout << set2 << "\n";

   std::cout << "sum : " << ( -set1 + set2 ) << "\n";
   std::cout << "inserset : " << ( -set1 & set2 ) << "\n";

   return 0;
 
   atm::finitefunction< usel, size_t, usel::hash, usel::equal_to > func
      ( 100, { { usel( "sel1" ), 20 }, { usel( "sel2" ), 30 } } );

   func. assign( usel( "something" ), 50 );
   func. assign( usel( "else" ), 200 );
   std::cout << func << "\n";
   std::cout << func( usel( "something" )) << "\n";

   atm::borderfunction< std::string, double > bord( 42 );
   bord. append( "aa", 31 );
   bord. append( "bb", 40 );
   bord. append( "cc", 100 );
   bord. append( "dd", 200 );
   bord. append( "ee", 300 );
   bord. append( "ff", 400 );
   bord. append( "gg", 200 );
   std::cout << bord << "\n\n";
   std::cout << bord( "a" ) << "\n";  
   for( const auto& p : bord )
      std::cout << bord( p. first + "A" ) << "\n";
 
   return 0;

   using namespace data;
   auto tr = tree( tree_array, 
      { tree( tree_unit ), 
        tree( tree_bool, true ), 
        tree( tree_char, 'a' ), 
        tree( tree_double, 3.14 ),
        tree( tree_usel, usel( "hello" ) ) } );
   tr = tree( tree_tuple, { tr, tree( tree_bigint, bigint( "999999999999999999" ) ), tree( tree_u64, 2222ul ) } );

   std::cout << tr << "\n";
   return 0;
}



#if 0
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
#endif
