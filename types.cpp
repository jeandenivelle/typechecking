
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
   auto tr = data::tuple( { data::tree( data::dat_unit ),
                            data::tree( data::dat_bool, true ),
                            data::tree( data::dat_u64, (uint64_t) 400 ), 
                            data::tree( data::dat_integer, bigint( 500 )),
                            data::tree( data::dat_double, 3.1415 ),
                            data::tree( data::dat_unit ) } );
   std::cout << tr << "\n";

   auto ex = regexp::tuple( { regexp::expr( regexp::type_unit ),
                              regexp::expr( regexp::flt_bool, 
                                 stepfunc<bool,bool>( false, {{ true, true }} )),
                              regexp::expr( regexp::flt_u64, 
                                 stepfunc< uint64_t, bool > ( false, {{400,true}} )),
                              regexp::expr( regexp::flt_integer,
                                 stepfunc< bigint, bool > ( false,
                                  {{ bigint(500), true }} )),
                              regexp::expr( regexp::type_double ) } );
   ex = regexp::expr( regexp::tup_fill, ex, 
                      { regexp::expr( regexp::flt_char,
                                 stepfunc< char, bool > ( false, {{ 'a', true }} )),
                        regexp::expr( regexp::type_double ) } );

   std::cout << ex << "\n";

   {
      regexp::defmap defs;
      defs. insert( { identifier( ) + "tuple", ex } );  

      atm::simple trans;
      atm::statemap acc = create_states( defs, trans );

      atm::resultmap conv;
      convert( trans, conv, defs, acc );
      std::cout << "Conversion Results:\n";
      for( const auto& c : conv )
         std::cout << "   " << c. first << " : " << c. second << "\n";

      std::cout << trans << "\n";
      std::cout << "nondet: " << run( trans, tr ) << "\n";
      return 0;
   }

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

#if 1
   atm::state q0;
   atm::state q1 = q0 + 1;
   atm::state q2 = q0 + 2;
   atm::state q3 = q0 + 3;

   auto bld1 = atm::builder( );
   bld1. addlinear( { q0 }, 3 );

   auto bld2 = atm::builder( ); 
   bld2. addlinear( { q2 }, 1 );
   std::cout << bld2 << "\n";

   auto bld3 = atm::builder( );
   bld3. addcircular( { q1, q2 }, 2 );
   std::cout << bld1 << "\n";
   std::cout << bld2 << "\n";
   std::cout << bld3 << "\n";
 
   // std::cout << atm::disjunction( { bld1, bld2, bld3 } ) << "\n";
#endif
  
   fieldmap flds;
   regexp::defmap defs;

   tests::add_nat( defs, flds );
   tests::add_fol( defs, flds );

   std::cout << defs << "\n";

   atm::simple trans;
   atm::statemap acc = create_states( defs, trans );  
   std::cout << acc << "\n";

   atm::resultmap conv;
   convert( trans, conv, defs, acc );
   std::cout << "Conversion Results:\n";
   for( const auto& c : conv )
      std::cout << "   " << c. first << " : " << c. second << "\n";

   std::cout << "NONDETERMINISTIC:\n";
   std::cout << trans << "\n";
 
   auto det = make_deterministic( trans ); 
   std::cout << "DETERMINISTIC:\n";
   std::cout << det. first << "\n";
   std::cout << det. second << "\n";

   std::cout << "\n";
   std::cout << "nondet: " << run( trans, tests::formula( )) << "\n";
   std::cout << "det:    " << run( det. first, tests::formula( )) << "\n";
   return 0;
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
