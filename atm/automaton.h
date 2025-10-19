#ifndef ATM_AUTOMATON
#define ATM_AUTOMATON

#include "finitefunction.h"
#include "borderfunction.h"
#include "states.h"

#include <limits>

namespace atm {
	struct dma {
		const state_t def;
		states_t states;

      /* tag types */
      finitefunction< bool, state_t > bool_transit;
		borderfunction< char, state_t > char_transit;
   	finitefunction< usel, state_t, usel::hash, usel::equal_to > usel_transit;
		
      /* index type u64 */
      borderfunction< size_t, state_t > u64_transit;
		
      state_t bigint_state;
		state_t double_state;
		state_t empty_mset_state;
		state_t empty_tupl_state;

		finitefunction< 
			state_pair_t, state_t, 
			state_pair_hash, 
			state_pair_equal_to
		> tupl_transit;

		finitefunction<
			state_pair_t, state_t, 
			state_pair_hash, 
			state_pair_equal_to
		> mset_transit;

		dma( ) = delete;
		dma( state_t&& def ):
			def( std::move( def ) ),
         states( states_t( this-> def ) ),
	  		bool_transit( finitefunction< bool, state_t >( this-> def ) ),
	  		char_transit( borderfunction< char, state_t >( this-> def ) ),
	  		usel_transit( finitefunction< usel, state_t, usel::hash, usel::equal_to >( this-> def ) ),
	  		u64_transit( borderfunction< size_t, state_t >( this-> def ) ),
			tupl_transit(
				atm::finitefunction<
               state_pair_t, state_t, 
               state_pair_hash, 
               state_pair_equal_to
				> ( this-> def )	
			),
			mset_transit(
				atm::finitefunction<
               state_pair_t, state_t, 
               state_pair_hash, 
               state_pair_equal_to
				> ( this-> def )	
			)
		{
			bool_transit. assign( true, states. get_next_state() );
			bool_transit. assign( false, states. get_next_state() );

			char_transit. append( 0, states. get_next_state() );
				
			u64_transit. append( 0, states. get_next_state() );
			u64_transit. append( 1, states. get_next_state() );

			bigint_state = states. get_next_state();
			double_state = states. get_next_state();
			empty_mset_state = states. get_next_state();
			empty_tupl_state = states. get_next_state();
		}

		state_t Q_A( const data::tree& d ) const {
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
				return bigint_state;

         case data::tree_double:
            return double_state;

			case data::tree_tuple:
				{
					auto tuple = d. view_tuple();
					state_t s1 = empty_tupl_state, s2;
					for( size_t i = 0; i < tuple. size(); ++i ) {
						s2 = Q_A( tuple. val( i ) );
						s1 = tupl_transit( std::pair( s1, s2 ) );
					}
					return s1;
				}

			case data::tree_array:
				{
					auto array = d. view_array();
					state_t s1 = empty_mset_state, s2;
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

			out << "Bigint Transitions:\n\tc --> " << bigint_state << "\n";
			out << "Double Transitions:\n\tc --> " << double_state << "\n";
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
