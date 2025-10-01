#ifndef ATM_AUTOMATON
#define ATM_AUTOMATON

#include "atm/finitefunction.h"
#include "atm/borderfunction.h"

#include <concepts>
#include <type_traits>
#include <unordered_set>
#include <limits>

namespace atm {
	template< typename T >
	concept incrementable = requires( T t ) {
		{ ++t } -> std::same_as< T& >;
		{ t++ } -> std::same_as< T >;
		{ t=t };
	};

	template<
		incrementable T,
		typename H = std::hash< T >,
		typename E = std::equal_to< T >
	>
	struct pair_hash {
		 std::size_t operator( ) ( const std::pair< T, T >& p ) const {
			  return H{}( p.first ) ^ ( H{}( p.second ) << 1 );
		 }
	};
	
	template<
		incrementable T,
		typename H = std::hash< T >,
		typename E = std::equal_to< T >
	>
	struct pair_equal_to {
		 std::size_t operator( ) ( const std::pair< T, T >& p1, const std::pair< T, T >& p2 ) const {
			  return E{}(p1. first, p2. first) && E{}( p2. second, p2. second );
		 }
	};
	
	template<
		incrementable K,
		typename H = std::hash< K >,
		typename E = std::equal_to< K >
	>
	struct dma {
		const K def;
		std::unordered_set< K, H, E > states;

   	finitefunction< bool, K > 										bool_transit;
		borderfunction< char, K >                             char_transit;
   	finitefunction< usel, K, usel::hash, usel::equal_to > usel_transit;
		borderfunction< size_t, K > 									u64_transit;
		borderfunction< bigint, K > 									bigint_transit;
		// borderfunction< double, K > 									double_transit;
		K empty_mset_state;
		K empty_tupl_state;

		finitefunction< 
			std::pair< K , K >, K, 
			pair_hash< K >, 
			pair_equal_to< K > 
		> tupl_transit;

		finitefunction<
			std::pair< K, K >, K,
			pair_hash< K >,
			pair_equal_to< K > 
		> mset_transit;

		dma( ) = delete;
		dma( K& def ): 
			def( def ),
	  		bool_transit( finitefunction< bool, K >( this-> def ) ),
	  		char_transit( borderfunction< char, K >( this-> def ) ),
	  		usel_transit( finitefunction< usel, K, usel::hash, usel::equal_to >( this-> def ) ),
	  		u64_transit( borderfunction< size_t, K >( this-> def ) ),
	  		bigint_transit( borderfunction< bigint, K >( this-> def ) ),
	  		// double_transit( borderfunction< double, K >( this-> def ) ) 
			tupl_transit(
				finitefunction<
					std::pair< K, K >, K,
					atm::pair_hash< K >,
					atm::pair_equal_to< K > 
				> ( this-> def )	
			),
			mset_transit(
				atm::finitefunction<
					std::pair< K, K >, K,
					atm::pair_hash< K >,
					atm::pair_equal_to< K > 
				> ( this-> def )	
			)
		{
			bool_transit. assign( true, new_state( ) );
			bool_transit. assign( false, new_state( ) );

			char_transit. append( 0, new_state( ) );
				
			u64_transit. append( 0, new_state( ) );
			u64_transit. append( 1, new_state( ) );
			
			bigint_transit. append( bigint( INT64_MIN ), new_state( ) );
			bigint_transit. append( bigint( 0 ), new_state( ) );
			bigint_transit. append( bigint( 1 ), new_state( ) );
			
			empty_mset_state = new_state( );
			empty_tupl_state = new_state( );
		}
		
		dma( K&& def ):
			def( std::move( def ) ),
	  		bool_transit( finitefunction< bool, K >( this-> def ) ),
	  		char_transit( borderfunction< char, K >( this-> def ) ),
	  		usel_transit( finitefunction< usel, K, usel::hash, usel::equal_to >( this-> def ) ),
	  		u64_transit( borderfunction< size_t, K >( this-> def ) ),
	  		bigint_transit( borderfunction< bigint, K >( this-> def ) ),
	  		// double_transit( borderfunction< double, K >( this-> def ) )
			tupl_transit(
				atm::finitefunction<
					std::pair< size_t, size_t >,
					size_t,
					atm::pair_hash< size_t >,
					atm::pair_equal_to< size_t> 
				> ( this-> def )	
			),
			mset_transit(
				atm::finitefunction<
					std::pair< size_t, size_t >,
					size_t,
					atm::pair_hash< size_t >,
					atm::pair_equal_to< size_t> 
				> ( this-> def )	
			)
		{
			bool_transit. assign( true, new_state( ) );
			bool_transit. assign( false, new_state( ) );

			char_transit. append( 0, new_state( ) );
				
			u64_transit. append( 0, new_state( ) );
			u64_transit. append( 1, new_state( ) );

			bigint_transit. append( bigint( INT64_MIN ), new_state( ) );
			bigint_transit. append( bigint( 0 ), new_state( ) );
			bigint_transit. append( bigint( 1 ), new_state( ) );
			
			empty_mset_state = new_state( );
			empty_tupl_state = new_state( );
		}

		K new_state( ) {
			K state = def;
		  	while( states. find( state ) != states. end() ) {
				state++;
			}
			states. insert( state );
			return state;
		}

		K Q_A( const data::tree& d ) const {
			switch( d. sel() ) {
			case data::tree_bool:
				return bool_transit( d. view_bool(). b() );

			case data::tree_char:
				return char_transit( d. view_char(). c() );
			case data::tree_usel:
				return usel_transit( d. view_usel(). s() );

			case data::tree_u64:
				return u64_transit( d. view_u64(). i() );

			case data::tree_bigint:
				return bigint_transit( d. view_bigint(). i() );

			case data::tree_tuple:
				{
					auto tuple = d. view_tuple();
					K s1 = empty_tupl_state, s2;
					for( size_t i = 0; i < tuple. size(); ++i ) {
						s2 = Q_A( tuple. val( i ) );
						s1 = tupl_transit( std::pair( s1, s2 ) );
					}
					return s1;
				}

			case data::tree_array:
				{
					auto array = d. view_array();
					K s1 = empty_mset_state, s2;
					for( size_t i = 0; i < array. size(); ++i ) {
						s2 = Q_A( array. val( i ) );
						s1 = mset_transit( std::pair( s1, s2 ) );
					}
					return s1;
				}
			
			default:
				std::cerr << "Unrecognized data::selector instance: " << d. sel() << "\n";
				throw std::runtime_error( "Unrecognized data::selector instance\n" );
			}

			std::cerr << "data::selector instance fell though the switch cases: " << d. sel() << "\n";
			throw std::runtime_error( "data::selector instance fell through the switch cases\n" );
		}

		void print( std::ostream& out ) const {
			out << "Bool Transitions:\n";
			for( auto it = bool_transit. begin();
				  it != bool_transit. cend(); ++it )
			{
				out << "\t" << it-> first << " --> " << it-> second << "\n";
			}
			
			out << "Char Transitions:\n";
			for( auto it = char_transit. begin();
				  it != char_transit. cend(); ++it )
			{
				out << "\t" << it-> first << " --> " << it-> second << "\n";
			}
			
			out << "Usel Transitions:\n";
			for( auto it = usel_transit. begin();
				  it != usel_transit. cend(); ++it )
			{
				out << "\t" << it-> first << " --> " << it-> second << "\n";
			}
			
			out << "U64 Transitions:\n";
			for( auto it = u64_transit. begin();
				  it != u64_transit. cend(); ++it )
			{
				out << "\t" << it-> first << " --> " << it-> second << "\n";
			}

			out << "Bigint Transitions:\n";
			for( auto it = bigint_transit. begin();
				  it != bigint_transit. cend(); ++it )
			{
				out << "\t" << it-> first << " --> " << it-> second << "\n";
			}

			out << "Empty Tuple Transition:\n\t() --> " << empty_tupl_state << "\n";

			out << "Tuple Transitions:\n";
			for( auto it = tupl_transit. begin();
				  it != tupl_transit. cend(); ++it )
			{
				out << "\t(" << it-> first. first << " ; " << it-> first. second << ") --> " << it-> second << "\n";
			}

			out << "Empty Set Transition\n\t{} --> " << empty_mset_state << "\n";
			
			out << "Multi Set Transitions:\n";
			for( auto it = mset_transit. begin();
				  it != mset_transit. cend(); ++it )
			{
				out << "\t{" << it-> first. first << " : " << it-> first. second << "} --> " << it-> second << "\n";
			}
		}		
	};
	
};

#endif
