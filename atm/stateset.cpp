
#include "stateset.h"


#if 0
   struct states_t {
      std::unordered_set< state_t, std::hash< state_t >, std::equal_to< state_t > > Q;
      
      using iterator = std::unordered_set< state_t, std::hash< state_t >, std::equal_to< state_t > >:: iterator;
      using const_iterator = std::unordered_set< state_t, std::hash< state_t >, std::equal_to< state_t > >:: const_iterator;

      states_t( ): def( 0 ) {}
      states_t( const state_t& def ): def( def ) {}
      states_t( const state_t&& def ): def( std::move( def ) ) {}
      
      state_t get_next_state( ) {
         state_t state = def;
         while( Q. find( state ) != Q. cend() ) {
            ++state;
         }
         Q. insert( state );
         return state;
      }
      
      size_t size( ) const {
         return Q. size( );
      }


#endif

std::ostream& atm::operator << ( std::ostream& out, const atm::stateset& set )
{
   out <<'{';
   for( auto p = set. begin(); p != set. end(); ++ p ) 
   {
      if( p != set. begin() ) 
         out << ", ";
      else
         out << ' ';
      out << *p;
   }
   out << " }";
   return out;
}


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


bool atm::subset( const stateset& s1, const stateset& s2 )
{
   if( s1. size( ) > s2. size( ))
      return false;

   stateset::key_compare lt;

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

