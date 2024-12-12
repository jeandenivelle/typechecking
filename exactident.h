
#ifndef EXACTIDENT_
#define EXACTIDENT_

// A normalized identifier with an index.

#include "normident.h"
#include "util/print.h"

struct exactident
{
   normident id;
   size_t ind; 

   exactident( normident id, size_t ind )
      : id( id ), ind( ind )
   { }

   struct hash
   {
      hash( ) noexcept = default;

      size_t operator( ) ( exactident ex ) const
      {
         normident::hash h;
         auto val = h( ex. id );
         val = val ^ ( val << 3 );
         return val ^ ex. ind;
      } 
   };
 
   struct equal_to
   {
      equal_to( ) noexcept = default;

      bool operator( ) ( exactident ex1, exactident ex2 ) const  
      {
         return ex1.id == ex2.id && ex1.ind == ex2.ind; 
      }
   }; 

   void print( std::ostream& out ) const
   {
      out << id << '_' << ind;
   }

};

inline bool operator == ( exactident ex1, exactident ex2 )
{
   return ex1. id == ex2. id && ex1. ind == ex2. ind;
}

inline bool operator != ( exactident ex1, exactident ex2 )
{
   return ex1. id != ex2. id || ex1. ind != ex2. ind;
}

template< typename V > using exactidentmap = 
std::unordered_map< normident, std::unordered_map< size_t, V >,
          normident::hash, normident::equal_to > ;

#endif

