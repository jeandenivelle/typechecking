
#include "builder.h"

void atm::builder::addlinear( state aa, size_t nr ) 
{
   if( nr == 0 )
      return; 

   ++ nrstates; 
   const size_t orig_nrstates = nrstates;

   const size_t delta_set_size = delta_set. size( ); 
   const size_t delta_eps_size = delta_eps. size( );

   for( size_t i = 0; i != nr; ++ i )
   {
      copy_delta( delta_set_size, delta_eps_size ); 
      nrstates += orig_nrstates;
   }

   // It remains to add the aa transitions:

   for( size_t s = 0; s != orig_nrstates; ++ s )
   {
      for( size_t i = 0; i != nr; ++ i )
      {
         delta_set. push_back( { s + i * orig_nrstates, aa, 
                                 s + ( i + 1 ) * orig_nrstates } );
      }
   }

   -- nrstates;
}

void atm::builder::addcircular( state aa, size_t nr )
{
   ++ nrstates;
   const size_t orig_nrstates = nrstates;

   const size_t delta_set_size = delta_set. size( );
   const size_t delta_eps_size = delta_eps. size( );

   for( size_t i = 0; i != nr; ++ i )
   {
      copy_delta( delta_set_size, delta_eps_size );
      nrstates += orig_nrstates;
   }

   // It remains to add the aa transitions:

   for( size_t s = 0; s != orig_nrstates; ++ s )
   {
      for( size_t i = 0; i != nr; ++ i )
      {
         delta_set. push_back( { s + i * orig_nrstates, aa,
                                 s + ( i + 1 ) * orig_nrstates } );
      }
   }

   -- nrstates;
}


void atm::builder::copy_delta( const size_t delta_set_size, 
                               const size_t delta_eps_size )
{
   for( size_t tr = 0; tr != delta_set_size; ++ tr )
   {   
      auto trans = delta_set[tr];
      trans. from += nrstates;
      trans. to += nrstates;
      delta_set. push_back( trans );
   }

   for( size_t tr = 0; tr != delta_eps_size; ++ tr )
   {
      auto trans = delta_eps[tr];
      trans. from += nrstates;
      trans. to += nrstates;
      delta_eps. push_back( trans );
   }

}


void atm::builder::printstate( std::ostream& out, size_t s ) const
{
   if( s > nrstates )
      throw std::logic_error( "incorrect state" );
   out << '$'<< s;
}

void atm::builder::print( std::ostream& out ) const
{
   out << "Builder(" << nrstates << "):\n";

   out << "Delta:\n";
   for( const auto& tr : delta_set )
   {
      out << "   ";
      printstate( out, tr. from ); out << " * " << tr. element;
      out << " -> ";
      printstate( out, tr. to );
      out << "\n";
   }

   for( const auto& tr : delta_eps )
   {
      out << "   ";
      printstate( out, tr. from ); 
      out << " -> ";
      printstate( out, tr. to );
      out << "\n";
   }

}
