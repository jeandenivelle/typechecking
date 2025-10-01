
#include <iostream>

#include "usel.h"

#include "data/tree.h"

#include "atm/finitefunction.h"
#include "atm/borderfunction.h"
#include "atm/automaton.h"

#include "diff/approxset.h"

void test_atm () {
	// define an automaton
	atm::dma< size_t > automaton( 0 );
	
	// define transition fucntions for usel type
	automaton. usel_transit. assign( usel( "atom" ), automaton. new_state( ) );
	automaton. usel_transit. assign( usel( "neg" ), automaton. new_state( ) );
	automaton. usel_transit. assign( usel( "imply" ), automaton. new_state( ) );
	automaton. usel_transit. assign( usel( "equiv" ), automaton. new_state( ) );
	automaton. usel_transit. assign( usel( "or" ), automaton. new_state( ) );
	automaton. usel_transit. assign( usel( "and" ), automaton. new_state( ) );

	// define transition for atomic formula 
	{
		const auto forall_char_state = automaton. new_state( );
		for( auto it = automaton. char_transit. begin( );
			  it != automaton. char_transit. cend(); ++it )
		{
			automaton. mset_transit. assign( std::pair( automaton. empty_mset_state, it-> second ), forall_char_state );
			automaton. mset_transit. assign( std::pair( forall_char_state, it-> second ), forall_char_state );
		}

		const auto prop_state = automaton. new_state( );
		{
			const auto tmp_state = automaton. new_state( );
			automaton. tupl_transit. assign( std::pair( automaton. empty_tupl_state, automaton. usel_transit( "atom" ) ), tmp_state );
			automaton. tupl_transit. assign( std::pair( tmp_state, forall_char_state ), prop_state );
		}

		{
			const auto tmp_state = automaton. new_state( );
			automaton. tupl_transit. assign( std::pair( automaton. empty_tupl_state, automaton. usel_transit( "neg" ) ), tmp_state );
			automaton. tupl_transit. assign( std::pair( tmp_state, prop_state ), prop_state );	
		}

		{
			const auto tmp1_state = automaton. new_state( );
			automaton. tupl_transit. assign( std::pair( automaton. empty_tupl_state, automaton. usel_transit( "imply" ) ), tmp1_state );
			automaton. tupl_transit. assign( std::pair( automaton. empty_tupl_state, automaton. usel_transit( "equiv" ) ), tmp1_state );

			const auto tmp2_state = automaton. new_state( );
			automaton. tupl_transit. assign( std::pair( tmp1_state, prop_state ), tmp2_state );
			automaton. tupl_transit. assign( std::pair( tmp2_state, prop_state ), prop_state );
		}

		{
			const auto forall_prop_state = automaton. new_state( );
			automaton. mset_transit. assign( std::pair( automaton. empty_mset_state, prop_state ), forall_prop_state );
			automaton. mset_transit. assign( std::pair( forall_prop_state, prop_state ), forall_prop_state );

			const auto tmp_state = automaton. new_state( );
			automaton. tupl_transit. assign( std::pair( automaton. empty_tupl_state, automaton. usel_transit( "or" ) ), tmp_state );
			automaton. tupl_transit. assign( std::pair( automaton. empty_tupl_state, automaton. usel_transit( "and" ) ), tmp_state );
			automaton. tupl_transit. assign( std::pair( tmp_state, forall_prop_state ), prop_state );
		}
		
		std::cout << automaton;
	}

	// test the automaton
	using namespace data;
	{
		tree d_bool( tree_bool, true );
		std::cout << d_bool << " ==> " << automaton. Q_A( d_bool ) << "\n";
		
		tree d_char( tree_char, 'a' );
		std::cout << d_char << " ==> " << automaton. Q_A( d_char ) << "\n";
		
		tree d_usel_atom( tree_usel, usel( "atom" ) );
		tree d_usel_neg( tree_usel, usel( "neg" ) );
		tree d_usel_equiv( tree_usel, usel( "equiv" ) );
		tree d_usel_imply( tree_usel, usel( "imply" ) );
		tree d_usel_or( tree_usel, usel( "or" ) );
		tree d_usel_and( tree_usel, usel( "and" ) );
		std::cout << d_usel_atom << " ==> " << automaton. Q_A( d_usel_atom ) << "\n";
		std::cout << d_usel_neg << " ==> " << automaton. Q_A( d_usel_neg ) << "\n";
		std::cout << d_usel_imply << " ==> " << automaton. Q_A( d_usel_imply ) << "\n";
		std::cout << d_usel_equiv << " ==> " << automaton. Q_A( d_usel_equiv ) << "\n";
		std::cout << d_usel_or << " ==> " << automaton. Q_A( d_usel_or ) << "\n";
		std::cout << d_usel_and << " ==> " << automaton. Q_A( d_usel_and ) << "\n";
		
		tree d_u64_0( tree_u64, (size_t) 0 );
		tree d_u64_1( tree_u64, (size_t) 1 );
		tree d_u64_11( tree_u64, (size_t) 11 );
		std::cout << d_u64_0 << " ==> " << automaton. Q_A( d_u64_0 ) << "\n";
		std::cout << d_u64_1 << " ==> " << automaton. Q_A( d_u64_1 ) << "\n";
		std::cout << d_u64_11 << " ==> " << automaton. Q_A( d_u64_11 ) << "\n";

		tree d_bigint_min( tree_bigint, bigint( -1111 ) );
		tree d_bigint_0( tree_bigint,  bigint( 0 ) );
		tree d_bigint_max( tree_bigint,  bigint( 1111 ) );
		std::cout << d_bigint_min << " ==> " << automaton. Q_A( d_bigint_min ) << "\n";
		std::cout << d_bigint_0 << " ==> " << automaton. Q_A( d_bigint_0 ) << "\n";
		std::cout << d_bigint_max << " ==> " << automaton. Q_A( d_bigint_max ) << "\n";

		tree d_array_char( tree_array, { d_char, d_char, d_char } );
		tree d_array( tree_array, { d_char, d_bigint_0, d_u64_0 } );
		std::cout << d_array_char << " ==> " << automaton. Q_A( d_array_char ) << "\n";
		std::cout << d_array << " ==> " << automaton. Q_A( d_array ) << "\n";

		tree d_atom( tree_tuple, { d_usel_atom, d_array_char } );
		std::cout << d_atom << " ==> " << automaton. Q_A( d_atom ) << "\n";

		tree d_neg( tree_tuple, { d_usel_neg, d_atom } );
	  	std::cout << d_neg << " ==> " << automaton. Q_A( d_neg ) << "\n";	

		tree d_imply1( tree_tuple, { d_usel_imply, d_atom, d_atom } );
		tree d_imply2( tree_tuple, { d_usel_imply, d_atom, d_char } );
		std::cout << d_imply1 << " ==> " << automaton. Q_A( d_imply1 ) << "\n";
		std::cout << d_imply2 << " ==> " << automaton. Q_A( d_imply2 ) << "\n";
		
		tree d_equiv1( tree_tuple, { d_usel_equiv, d_atom, d_atom } );
		tree d_equiv2( tree_tuple, { d_usel_equiv, d_atom, d_char } );
		std::cout << d_equiv1 << " ==> " << automaton. Q_A( d_equiv1 ) << "\n";
		std::cout << d_equiv2 << " ==> " << automaton. Q_A( d_equiv2 ) << "\n";

		tree d_prop_array( tree_array, { d_atom, d_atom, d_atom, d_atom } );
		std::cout << d_prop_array << " ==> " << automaton. Q_A( d_prop_array ) << "\n";
		
		tree d_or1( tree_tuple, { d_usel_or, d_prop_array } );
		tree d_or2( tree_tuple, { d_usel_or, d_array_char } );
		std::cout << d_or1 << " ==> " << automaton. Q_A( d_or1 ) << "\n";
		std::cout << d_or2 << " ==> " << automaton. Q_A( d_or2 ) << "\n";
		
		tree d_and1( tree_tuple, { d_usel_and, d_prop_array } );
		tree d_and2( tree_tuple, { d_usel_and, d_array_char } );
		std::cout << d_and1 << " ==> " << automaton. Q_A( d_and1 ) << "\n";
		std::cout << d_and2 << " ==> " << automaton. Q_A( d_and2 ) << "\n";
	}
}


int main( int argc, char* arcgv[] ) {
	test_atm();
	return 0;

	diff::approxset set1 = diff::approxset::empty( );

   set1. insert( -2 );
   set1. insert( -3 );
   set1. insert( 0 );
   std::cout << set1 << "\n";

   diff::approxset set2 = diff::approxset::empty( );
   set2. insert( -1 );
   set2. insert( 3 );
   std::cout << set2 << "\n";

   std::cout << "sum : " << ( -set1 + set2 ) << "\n";
#if 0
   std::cout << "intersect : " << ( -set1 & set2 ) << "\n";
#endif
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
