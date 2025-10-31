
#include <iostream>

#include "usel.h"

#include "data/tree.h"

#include "diff/approxset.h"

#include "tests.h"

int main( int argc, char* arcgv[] ) {
   tests::add_nat();
   return 0;
/*
   diff::approxset set1 = diff::approxset::empty( );
   set1. insert( -2 );
   set1. insert( -1 );

   diff::approxset set2 = diff::approxset::empty( );
   set2. insert( -1 );
   set2. insert( 3 );
   set2. insert( -2 );
   std::cout << set1 << "\n";
   std::cout << set2 << "\n";
   bool b = set1. restrict( set2 );
   std::cout << "after restrict " << set1 << "\n";
   std::cout << "restrict returned " << b << "\n";

   diff::matrix< std::string > mat;
   mat. extend( "aa" );
   mat. extend( "bb" );
   mat. extend( "cc" );
   mat. extend( "aa" );

   std::cout << mat << "\n";
   mat. at( "aa", "bb" ) = diff::approxset::lt( );
   mat. at( "bb", "cc" ) = diff::approxset::lt( );
   mat. at( "aa", "cc" ) = diff::approxset::eq( );

   auto cl = mat. close( );
   std::cout << mat << "\n";
   std::cout << "closure returned " << cl << "\n";
   mat. erase( "aa" );
   std::cout << mat << "\n";
   std::cout << mat. at( "cc", "bb" ) << "\n";
   mat. erase( "bb" );
   std::cout << mat << "\n";
*/
    return 0;
}



#if 0
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
