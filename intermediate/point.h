
// Written by Hans de Nivelle, Oct. 2024.

#ifndef INTERMEDIATE_POINT_
#define INTERMEDIATE_POINT_

namespace intermediate
{
   // Uniquely identifies each point in the flow graph.
   // Points are not used as jump labels, only for collection
   // properties.
 
   struct point
   {
      size_t ind;

      point( ) noexcept 
         : ind(0)
      { } 

      point& operator ++ ( ) 
      {
         ++ ind; 
         return *this;
      }
     
      point operator ++ ( int )
      {
         auto res = *this;
         ++ ind;
         return res;
      }
 
      void print( std::ostream& out ) const
         { out << '#' << ind; }
   };

   inline bool operator == ( point p1, point p2 )
   {
      return p1.ind == p2.ind;
   }

   inline bool operator != ( point p1, point p2 )
   {
      return p1.ind != p2.ind;
   }

}

#endif

