
#include "conversions.h"

atm::statemap 
atm::create_accepting( const regexp::defmap& defs, simple& smp )
{
   statemap acc;
   for( const auto& d : defs ) 
      acc. insert( { d. first, smp. create_state( ) } );
   return acc; 
}

atm::convresult
atm::convert2single( simple& smp, const convresult& res )
{
   switch( res. sel( ))
   {
   case atm_single:
      return res;

   }

   return convresult( atm_error, 
              std::string( "didn't know how to convert " ) + 
                 getcstring( res. sel( )) + " to single" ); 
}

atm::convresult 
atm::convert( simple& smp, const regexp::expr& e,
              const regexp::defmap& defs, const identifier::map< state > & acc )
{

   std::cout << "converting: " << e << "\n";

   switch( e. sel( ))
   {
   case regexp::flt_sel:
      {
         state q = smp. create_state( ); 
         auto& u = smp. add_delta_usel( smp. trap ); 
         for( const auto& f : e. view_filter_sel( ). func( ))
            u. assign( f. first, q ); 
         return { atm_single, q };
      }

   case regexp::tup_exact:
   case regexp::tup_prefix:
      {
         auto tup = e. view_tuple( ); 
         std::vector< convresult > sub;
         for( size_t i = 0; i != tup. size( ); ++ i )
         {
            sub. push_back( 
               convert2single( smp, convert( smp, tup. sub(i), defs, acc )));
         }

         for( const auto& s : sub )
         {
            if( s. sel( ) == atm_error )
               return s; 
         }
        
         auto q = smp. empty_tuple;
         for( const auto& s : sub )
         {
            auto q1 = smp. create_state( );
            smp. delta_tuple. insert( { { q, s. view_single( ). q( ) }, q1 } );
            q = q1; 
         }
         
         if( e. sel( ) == regexp::tup_prefix )
            throw std::logic_error( "we need to add a cycle" );

         return convresult( atm_tuple, q, sub. size( )); 
      }

   case regexp::log_or:
      {
         auto disj = e. view_disjunction( ); 
         std::vector< convresult > subresults;
         for( size_t i = 0; i != disj. size( ); ++ i )
            subresults. push_back( convert( smp, disj. sub(i), defs, acc )); 
         throw std::logic_error( "or is not finished" );
      }
   }

   std::cout << e << "\n";
   throw std::logic_error( "not implemented" ); 

}

std::ostream& atm::operator << ( std::ostream& out, const statemap& acc )
{
   out << "Statemap:\n";
   for( const auto& a : acc )
      out << "   " << a. first << " : " << a. second << "\n";
   out << "\n";
   return out;
}

