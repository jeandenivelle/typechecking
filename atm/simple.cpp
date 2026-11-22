
#include "simple.h"


namespace atm
{
   namespace
   {
      bool 
      isdeterministic( const std::multimap< std::pair< state, state >, state,
                       state::pair_less > & mp )
      {
         if( mp. size( ) > 1 )
         {
            auto p1 = mp. begin( );
            auto p2 = p1; ++ p2; 

            while( p2 != mp. end( ))
            {
               if( p1 -> first. first == p2 -> first. first &&
                   p1 -> first. second == p2 -> first. second )
               { 
                  if( p1 -> second != p2 -> second )
                     return false;
               }

               p1 = p2; ++ p2; 
            }
         }
         return true;
      }
   }
}


bool atm::simple::isdeterministic( ) const
{
   if( delta_unit. size( ) > 1 ) 
      return false;
   if( delta_bool. size( ) > 1 ) 
      return false;
   if( delta_char. size( ) > 1 ) 
      return false;
   if( delta_sel. size( ) > 1 ) 
      return false;
   if( delta_u64. size( ) > 1 ) 
      return false;
   if( delta_integer. size( ) > 1 ) 
      return false;
   if( delta_double. size( ) > 1 ) 
      return false;

   if( ! atm::isdeterministic( delta_tuple ))
      return false;
   if( ! atm::isdeterministic( delta_set ))
      return false;

   if( delta_epsilon. size( ))
      return false;

   return true;
}


namespace 
{
   template<typename D> 
   void printdelta( std::ostream& out, 
                    const std::vector<D> & delta, const char* c )
   {
      if( delta. size( ))
      {
         out << c << "\n";
         for( const auto& d : delta )
            out << "   " << d << "\n";
         out << "\n";
      }
   }
}
 
void atm::simple::print( std::ostream& out ) const
{
   out << "Simple Automaton:\n";
   out << "   <trap> = " << trap << "\n";
   out << "\n";

   if( comments. size( ))
   {
      out << "Comments:\n";
      for( const auto& c : comments )
         out << "   " << c. first << " : " << c. second << "\n";
      out << "\n";
   }

   printdelta( out, delta_unit, "Delta (unit)" );
   printdelta( out, delta_bool, "Delta (bool)" );
   printdelta( out, delta_char, "Delta (char)" );
   printdelta( out, delta_sel, "Delta (usel)" );
   printdelta( out, delta_u64, "Delta (u64)" );
   printdelta( out, delta_integer, "Delta (integer)" );
   printdelta( out, delta_double, "Delta (double)" );

   out << "Tuple transitions:\n";
   out << "   <empty> = " << empty_tuple << "\n";
   for( const auto& t : delta_tuple )
   {
      out << "   " << t. first. first << ", " << t. first. second; 
      out << " -> " << t. second << "\n";
   }
   out << "\n";

   out << "Set transitions:\n"; 
   out << "   <empty> = " << empty_set << "\n";
   for( const auto& d : delta_set )
   {
      out << "   " << d. first. first << ", " << d. first. second;
      out << " -> " << d. second << "\n";
   }
   out << "\n";

   out << "Epsilon Transitions:\n"; 
   for( const auto& e : delta_epsilon )
      out << "   " << e. first << " -> " << e. second << "\n";
   out << "\n";

}

