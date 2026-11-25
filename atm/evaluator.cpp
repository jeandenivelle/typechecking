
#include "evaluator.h"
#include "nondeterminism.h"

atm::state atm::evaluator::run( const data::tree& tr ) const
{

   switch( tr. sel( ))
   {
   case data::dat_unit:
      {
         if( det. delta_unit. size( ) == 1 )
            return det. delta_unit. front( );
         else
            return det. trap;
      }

   case data::dat_bool:
      {
         if( det. delta_bool. size( ) == 1 )
            return det. delta_bool. front( ). apply( tr. view_bool( ). b( ));
         else
            return det. trap;
      }

     case data::dat_char:
      {
         if( det. delta_char. size( ) == 1 )
            return det. delta_char. front( ). apply( tr. view_char( ). c( ));
         else
            return det. trap;
      }

   case data::dat_sel:
      {
         if( det. delta_sel. size( ) == 1 )
            return det. delta_sel. front( ). apply( tr. view_usel( ). s( ));
         else
            return det. trap;
      }

   case data::dat_u64:
      {
         if( det. delta_u64. size( ) == 1 )
            return det. delta_u64. front( ). apply( tr. view_u64( ). u( ));
         else
            return det. trap;
      }

   case data::dat_integer:
      {
         if( det. delta_integer. size( ) == 1 )
            return det. delta_integer. front( ). apply( tr. view_integer( ). i( ));
         else
            return det. trap;
      }

   case data::dat_double:
      {
         if( det. delta_double. size( ) == 1 )
            return det. delta_double. front( );
         else
            return det. trap;
      }

   case data::dat_tuple:
      {
         auto tup = tr. view_tuple( );
         state q = det. empty_tuple;
         for( size_t i = 0; i != tup. size( ); ++ i )
         {
            state sub = run( tup. val(i));
            auto it = det. delta_tuple. find( { q, sub } );
            if( it != det. delta_tuple. end( ))
               q = ( it -> second );
            else
               q = det. trap;
         }
         return q;
      }

   case data::dat_array:
      {
         auto ar = tr. view_array( );
         state q = det. empty_set;
         for( size_t i = 0; i != ar. size( ); ++ i )
         {
            state sub = run( ar. val(i));
            auto it = det. delta_set. find( { q, sub } );
            if( it != det. delta_set. end( ))
               q = ( it -> second );
            else
               q = det. trap;
         }
         return q;
      }
   }

   std::cout << "evaluator::run, unrecognized " << tr. sel( ) << "\n";
   throw std::logic_error( "evaluator::run" );
}


void atm::evaluator::print( std::ostream& out ) const
{
   out << "Evaluator:\n";
   out << det << "\n";

   out << "Accepting States:\n";
   for( const auto& acc : accept )
      out << "   " << acc. first << " -> " << acc. second << "\n";
   out << "\n";
}


void 
atm::subsets::print( std::ostream& out ) const
{
   out << "checked:\n";
   for( const auto& c : checked )
      out << "   " << c. first << " -> " << c. second << "\n";

   out << "unchecked:\n";
   for( const auto& u : unchecked )
      out << "   " << u. first << " -> " << u. second << "\n";

}

atm::evaluator
atm::make_evaluator( const translator& trans )
{
   subsets sub; 

   evaluator eval = make_deterministic( sub, trans. shared );

   std::multimap< state, identifier, state::less > uses;

   for( const auto& acc : trans. accepting )
      uses. emplace( acc. second, acc. first );

   std::cout << sub << "\n\n";
   for( const auto& u : uses )
      std::cout << u. first << " " << u. second << "\n";
   std::cout << "\n\n";
   for( const auto& ch : sub. checked )
   {
      // We have S -> q. We iterator through S. 
      // If S accepts something, then q must accept it in the result.

      for( auto s : ch. first )
      {
         auto range = uses. equal_range(s); 
         for( auto p = range. first; p != range. second; ++ p )
            eval. accept. emplace( ch. second, p -> second );
      }
   }

   return eval;
}

