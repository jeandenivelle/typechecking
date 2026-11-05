
#include <iostream>

#include "data/constructors.h"
#include "usel.h"
#include "data/tree.h"

#include "partition.h"
#include "finfunc.h"

#include "tests.h"
#include "overloadmap.h"

#include "atm/algorithms.h"

#include "regexp/algorithms.h"

int main( int argc, char* arcgv[] ) 
{
   auto f = tests::formula( );
   std::cout << f << "\n";

   auto a = tests::atm_fol( );
   std::cout << a << "\n";


   atm::stateset set = run( a, f );
   std::cout << set << "\n";
   
   return 0;

#if 0
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
#endif

   fieldmap flds;
   regexp::defmap defs;

   tests::add_nat( defs, flds );
   tests::add_fol( defs, flds );

   std::cout << flds << "\n";
 
   auto b = checktypes( defs );

   std::cout << "\n";
   std::cout << defs << "\n";
#if 0
   auto f = tests::mixing( );
   // auto f = tests::repeated( );
   std::cout << f << "\n";
   f = tests::arrayconv( );
   std::cout << f << "\n";
#endif

   return 0;

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
