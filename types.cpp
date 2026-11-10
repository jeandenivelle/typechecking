
#include <iostream>

#include "data/constructors.h"
#include "usel.h"
#include "data/tree.h"

#include "stepfunc.h"
#include "finfunc.h"

#include "tests.h"
#include "overloadmap.h"

#include "atm/algorithms.h"
#include "atm/conversions.h"

#include "regexp/algorithms.h"
#include "atm/builder.h"

int main( int argc, char* arcgv[] ) 
{
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

   atm::state q0;
   atm::state q1 = q0 + 1;
   atm::state q2 = q0 + 2;
   atm::state q3 = q0 + 3;

   auto bld = atm::builder( );
   std::cout << bld << "\n";
   bld. addlinear( q0, 3 );
   bld. addlinear( q1, 2 );
   std::cout << bld << "\n";
   return 0;

  
   fieldmap flds;
   regexp::defmap defs;

   tests::add_nat( defs, flds );
   tests::add_fol( defs, flds );

   std::cout << flds << "\n";
 
   auto b = checktypes( defs );

   std::cout << "after checking " << defs << "\n";

   atm::simple trans;
   identifier::map< atm::state > acc;

   add_automaton( trans, defs. at( identifier( ) + "nat" ). e, defs, acc );
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
