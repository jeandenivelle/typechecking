
#ifndef DIFF_MATRIX_
#define DIFF_MATRIX_

#include <unordered_map>
#include <queue>

#include "approxset.h"
#include "util/print.h"

namespace diff
{

   template< typename D, 
             typename H = std::hash<D>, typename E = std::equal_to<D>> 
   class matrix 
   {
      
      std::vector< std::vector< approxset >> matr;
      std::unordered_map< D, size_t, H, E > index; 
      std::vector<D> revindex;

   public:
      matrix( ) noexcept = default;

      void erase( const D& d )
      {
         size_t i = index. at(d); 

         // If is is not last, we swap with last:

         if( i + 1 < matr. size( ))
         {
            auto last = matr. size( ) - 1;
            for( auto& m : matr )
               std::swap( m[i], m[ last ] );
            std::swap( matr[i], matr[ last ] );

            index.at( revindex[ last ] ) = i;
            revindex[i] = revindex[ last ];  
         }

         // This is the actual erasure:

         matr. pop_back( ); 
         for( auto& m : matr )
            m. pop_back( );
         index. erase(d);       
      }

      void extend( const D& d )
      {
         auto p = index. insert( std::pair( d, matr. size( ))). first;
         if( p -> second < matr. size( ))
         {
            for( auto& v : matr )
               v[ p -> second ] = approxset::full( );
            for( auto& s : matr[ p -> second ] )
               s = approxset::full( ); 
         }
         else
         {
            for( auto& v : matr )
               v. push_back( approxset::full( ));
            matr. push_back( 
                         std::vector( p -> second + 1, approxset::full( ))); 
            revindex. push_back(d);
         }
      }
 
      approxset& at( const D& d1, const D& d2 ) 
         { return matr. at( index.at(d1)). at( index.at(d2)); } 

      const approxset& at( const D& d1, const D& d2 ) const
         { return matr. at( index.at(d1)). at( index.at(d2)); }

      size_t dim( ) const { return matr. size( ); } 

      void print( std::ostream& out ) const
      {
         out << "Matrix:\n";
         for( size_t i = 0; i != matr. size( ); ++ i )
         { 
            out << revindex[i] << ":\n";
            for( size_t j = 0; j != matr. size( ); ++ j ) 
               out << "   " << revindex[j] << " --> " << matr[i][j] << "\n";
         }
      }

      // Returns true if the result is consistent:
      // closing stops as soon as inconsistency is detected, because
      // there is no point in continuing.

      bool close( )
      {
         std::queue< std::pair< size_t, size_t >> change; 
            // Positions whose conjugate and concatenations must
            // be checked.

         for( size_t i = 0; i != matr. size( ); ++ i )
            for( size_t j = 0; j != matr. size( ); ++ j ) 
            {
               if( i == j )
                  matr[i][j] = approxset::eq( ); 
               else
               {
                  if( !matr[i][j]. isfull( ))
                     change. push( { i, j } );
               } 
            }

         while( change. size( ))
         {
            size_t i = change. front( ). first;
            size_t j = change. front( ). second;
            // std::cout << "checking: " << i << ", " << j << "\n";
            change. pop( );

            if( matr[i][j]. isempty( )) 
               return false; 

            {
               // We check the transposed position:

               auto rev = - matr[i][j];
               if( matr[j][i]. restrict( rev ))
                  change. push( { j, i } );  
            }

            for( size_t k = 0; k != matr. size( ); ++ k ) 
            {
               // Check (k,i) * (i,j): 

               if( k != i )
               {
                  auto sum = matr[k][i] + matr[i][j];
                  if( matr[k][j]. restrict( sum ))
                     change. push( { k, j } ); 
               }

               // Check (i,j) * (j,k): 

               if( k != j )
               {
                  auto sum = matr[i][j] + matr[j][k];
                  if( matr[i][k]. restrict( sum )) 
                     change. push( { i, k } );
               }
            } 
         }

         return true;
      }
   };

}

#endif

