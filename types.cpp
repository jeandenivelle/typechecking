
#include <iostream>

#include "data/constructors.h"
#include "usel.h"
#include "data/tree.h"

#include "partition.h"
#include "finfunc.h"

#include "tests.h"
#include "overloadmap.h"

#include "atm/stateset.h"

#include "regexp/exprtype.h"

int main( int argc, char* arcgv[] ) 
{
   std::cout << regexp::exprtype( regexp::exprtype_tuple, 100 ) << "\n";

   std::cout << tests::formula( ) << "\n\n";

   auto e = regexp::expr( regexp::set_union,
      { 
         regexp::expr( regexp::tup_constr, 
            { regexp::expr( regexp::def_ident, identifier( ) + "hallo" ) } ),
         regexp::expr( regexp::tup_constr, 
            { regexp::expr( regexp::def_ident, identifier( ) + "world" ) } )
      }
   );

   e = regexp::expr( regexp::set_single, e ); 
   std::cout << e << "\n";

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
   regexp::defmap prp;

   tests::add_nat( prp, flds );
   tests::add_fol( prp, flds );

   std::cout << prp << "\n";
   std::cout << flds << "\n";
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
