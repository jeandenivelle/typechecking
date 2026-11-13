
#include "builder.h"

void 
atm::builder::addlinear( const std::vector< state > & symbset, size_t nr ) 
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

   // It remains to add the transitions in symbset:

   for( size_t s = 0; s != orig_nrstates; ++ s )
   {
      for( size_t i = 0; i != nr; ++ i )
      {
         for( auto sym : symbset )
         {
            delta_set. push_back( { i * orig_nrstates + s, sym, 
                                    ( i + 1 ) * orig_nrstates + s } );
         }
      }
   }

   -- nrstates;
}

void 
atm::builder::addcircular( const std::vector< state > & symbset, size_t nr )
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

   // It remains to add the transitions in symbset:

   for( size_t s = 0; s != orig_nrstates; ++ s )
   {
      for( size_t i = 0; i != nr; ++ i )
      {
         for( auto sym : symbset ) 
         {
            delta_set. push_back( { i * orig_nrstates + s, sym,
                                    ( i + 1 ) * orig_nrstates + s } );
         }
      }
   }

   for( size_t s = 0; s != orig_nrstates; ++ s )
   {
      for( auto sym : symbset ) 
      {
         delta_set. push_back( { nr * orig_nrstates + s, sym, s } );
      }
   }

   delta_eps. push_back( { orig_nrstates - 1, nrstates } ); 
}

void atm::builder::copy_delta( const size_t delta_set_size, 
                               const size_t delta_eps_size )
{
   for( size_t tr = 0; tr != delta_set_size; ++ tr )
      delta_set. push_back( delta_set[ tr ]. moved( nrstates ));

   for( size_t tr = 0; tr != delta_eps_size; ++ tr )
      delta_eps. push_back( delta_eps[ tr ]. moved( nrstates ));
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


atm::builder 
atm::disjunction( const std::vector< builder > & disj )
{

   // The first state will have epsilon transitions to all the
   // first states of disj. In addition, every disjunct
   // needs an additional state (the original accepting state),
   // from which there will have an epsilon transition
   // to the accepting state of the result. 

   size_t finalstate = 1;
   for( const auto& dd : disj )
      finalstate += dd. nrstates + 1;

   builder res;
   res. nrstates = 1;

   for( const auto& dd : disj )
   {
      size_t diff = res. nrstates; 

      res. delta_eps. push_back( { 0, res. nrstates } );

      for( size_t tr = 0; tr != dd. delta_set. size( ); ++ tr )
         res. delta_set. push_back( dd. delta_set[ tr ]. moved( diff ));

      for( size_t tr = 0; tr != dd. delta_eps. size( ); ++ tr )
         res. delta_eps. push_back( dd. delta_eps[ tr ]. moved( diff ));

      res. nrstates += dd. nrstates;

      res. delta_eps. push_back( { res. nrstates, finalstate } );
      ++ res. nrstates; 
   }

   return res;
}

atm::builder atm::oneword( std::vector< state > word )
{
   std::cout << "OneWord:\n";
   std::sort( word. begin( ), word. end( ), state::less( ));

   auto bld = atm::builder( );

   auto it = word. begin( ); 
   while( it != word. end( ))
   {
      auto next = it;
      size_t freq = 0;
      while( next != word. end( ) && *it == *next )
      {
         ++ next;
         ++ freq;
      }

      std::cout << "   " << *it << " / " << freq << "\n";
      bld. addcircular( { *it }, freq );
      it = next;
   }

   return bld;
}

