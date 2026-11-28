
#include "program.h"
#include "configuration.h"

// Here are the print functions of small classes.
// I did not want to create a separate print file:

void interpreter::term::print( std::ostream& out ) const
{
   switch( sel( ))
   {
   case tm_variable:
      out << "$" << view_variable( ). var( );
      return;
      
   case tm_fieldof:
      {
         auto f = view_fieldof( );
         out << "( " << f. tm( ) << " ). " << f. fld( );
         return;
      }

   }

   std::cout << sel( ) << "\n";
   throw std::logic_error( "print: Don't know to print this term" ); 
}


void interpreter::instruction::print( std::ostream& out ) const
{
   switch( sel( ))
   {
   case ins_nop:
      out << "nop";
      return;

   case ins_branch:
      {
         auto br = view_branch( );
         out << "branch( "; 
         out << br. arg( );
         for( size_t i = 0; i != br. size( ); ++ i )
            out << ", " << br. prop(i) << " -> " << br. target(i); 
         out << " )";
      }
      return;
   }

   std::cout << sel( ) << "\n";
   throw std::logic_error( "print: Don't know to print this instruction" );
}


void interpreter::block::print( std::ostream& out ) const
{
   out << "Block:\n";
   for( size_t i = 0; i != instr. size( ); ++ i )
      out << "   " << i << " :   " << instr. at(i) << "\n";
}


interpreter::value
interpreter::program::exec( const funcdef& func, 
                            std::vector< value > values ) const
{
   if( func. parameters. size( ) != values. size( ))
      throw std::logic_error( "number of values is wrong" );

   auto conf = configuration( &func );
 
   for( size_t i = 0; i != func. parameters. size( ); ++ i )
      conf. variables. emplace( func. parameters[i]. first, values[i] );
}


void interpreter::program::print( std::ostream& out ) const
{
   out << "Program:\n\n";

   if( functions. size( ))
   {
      out << "Functions:\n";
      for( const auto& func : functions )
         out << func. first << ": " << func. second;
      out << "\n";
   }

   if( fields. size( ))
   {
      out << "Fields:\n";
      for( const auto& fld : fields )
         out << "   " << fld. first << ": " << fld. second << "\n";
      out << "\n";
   }

}

