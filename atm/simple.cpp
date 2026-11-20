
#include "simple.h"


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

