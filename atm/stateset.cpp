
#include "stateset.h"

bool atm::operator == ( const stateset& s1, const stateset& s2 )
{
   if( s1. size( ) != s2. size( ))
      return false;

   auto p1 = s1. begin( );
   auto p2 = s2. begin( );
   while( p1 != s1. end( ))
   {
      std::cout << *p1 << " " << *p2 << "\n";
      if( *p1 != *p2 )
         return false;
      ++ p1; ++ p2;
   }
   return true;
}

bool 
atm::stateset::less::operator( ) ( const stateset& s1, 
                                   const stateset& s2 ) const
{
   auto cmp = state::less( );

   auto p1 = s1. begin( );
   auto p2 = s2. begin( );

   while( p1 != s1. end( ) && p2 != s2. end( )) 
   {
      if( *p1 != *p2 )
         return cmp( *p1, *p2 );
      ++ p1;
      ++ p2;
   }

   if( p1 == s1. end( ))
      return p2 != s2. end( );
   
   return false;
}

bool atm::subset( const stateset& s1, const stateset& s2 )
{
   if( s1. size( ) > s2. size( ))
      return false;

   state::less lt;

   auto p1 = s1. begin( );
   auto p2 = s2. begin( );

   while( p1 != s1. end( )) 
   {
      while( p2 != s2. end( ) && lt( *p2, *p1 ))
         ++ p2;

      if( p2 == s2. end( ) || *p2 != *p1 ) 
         return false;

      ++ p1; ++ p2;
   }
   return true; 
}

void atm::stateset::print( std::ostream& out ) const
{
   out <<'{';
   for( auto p = begin(); p != end(); ++ p ) 
   {
      if( p != begin() ) 
         out << ", ";
      else
         out << ' ';
      out << *p;
   }
   out << " }";
}


