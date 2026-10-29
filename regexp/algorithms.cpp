
#include "algorithms.h"
#include <stdexcept>
#include <queue>

void 
regexp::collect( const expr& e,
                 identifier::set& defs, size_t& c )
{
   ++ c;

   switch( e. sel( ))
   {
   case type_never:
   case type_unit:
   case type_bool:
   case type_char: 
   case type_sel:
   case type_u64:
   case type_integer:
   case type_double:
   case type_iter:
      return;  
  
   case flt_sel:
      return;

   case ref_ident:
      // Here we count an identifier!

      defs. insert( e. view_reference( ). ident( ));
      return;

   case tup_constr:
   case tup_concat:
      {
         auto tup = e. view_tuple( );
         for( size_t i = 0; i != tup. size( ); ++ i )
            collect( tup. sub(i), defs, c ); 
         return;
      }

   case log_and:
   case log_or:
      {
         auto log = e. view_logical( );
         for( size_t i = 0; i != log. size( ); ++ i )
            collect( log. sub(i), defs, c );
         return;
      }

   case set_constr:
   case set_merge:
      {
         auto set = e. view_set( );
         for( size_t i = 0; i != set. size( ); ++ i )
            collect( set. sub(i), defs, c );
         return;
      }

   case set_repeat:
      collect( e. view_repeat( ). sub( ), defs, c );
      return;

   case conv_tuple2single:
   case conv_set2single:
      collect( e. view_conv( ). sub( ), defs, c );
      return; 
   }

   std::cout << "unknown selector in regexp::collect:  " << e. sel( ) << "\n";
   throw std::logic_error( "regexp::collect" ); 
}


identifier::map< identifier::set > 
regexp::dependencymap( const defmap& defs )
{
   identifier::map< identifier::set > res;

   for( const auto& d : defs )
   {
      identifier::set used;
      size_t cntr = 0;
      collect( d.second.e, used, cntr );

      res. emplace( d.first, std::move( used )); 
   }

   return res; 
}

regexp::exprtype regexp::join( exprtype tp1, exprtype tp2 )
{
   if( tp1. sel( ) == exprtype_error || tp2. sel( ) == exprtype_error )
      return exprtype_error; 

   if( tp1. sel( ) == exprtype_unknown )
      return tp2;

   if( tp2. sel( ) == exprtype_unknown )
      return tp1;

   if( tp1. sel( ) != tp2. sel( ))
      return exprtype_error;

   return tp1;
}


regexp::exprtype regexp::gettype( const defmap& defs, const expr& e )
{
   std::cout << "checking type of " << e << "\n";

   switch( e. sel( ))
   {
   case type_unit:
   case type_bool:
   case type_char:
   case type_sel:
   case type_u64:
   case type_integer:
   case type_double:
   case type_iter:
      return exprtype_single;

   case flt_sel:
      return exprtype_single;
 
   case ref_ident:
         return defs. at( e. view_reference( ). ident( )). tp; 
   
   case tup_constr:
      {
         auto tup = e. view_tuple( );
         exprtype res = exprtype_unknown;
         for( size_t i = 0; i != tup. size( ); ++ i )
         {
            res = join( res, gettype( defs, tup. sub(i) ));
         }
         std::cout << "tup_constr " << e << " -> " << res << "\n"; 
         if( res. isbelow( exprtype_single ))
            return exprtype_tuple;
         else
            return exprtype_error;
      } 

   case log_and:
   case log_or:
      {
         auto log = e. view_logical( );
         exprtype res = exprtype_unknown;
         for( size_t i = 0; i != log. size( ); ++ i )
            res = join( res, gettype( defs, log. sub(i)) );

         return res;
      }

   case set_constr:
      {
         auto set = e. view_set( );
         exprtype res = exprtype_unknown;
         for( size_t i = 0; i != set. size( ); ++ i )
            res = join( res, gettype( defs, set. sub(i)) );
  
         if( res. isbelow( exprtype_single ))
            return exprtype_set;
         else
            return exprtype_error;
      }

   case set_repeat:
      {
         auto tp = gettype( defs, e. view_repeat( ). sub( ));
         if( tp. sel( ) != exprtype_unknown && tp. sel( ) != exprtype_set )
            return exprtype_error;
         else
            return exprtype_set; 
      }

   case conv_tuple2single:
      {
         auto tp = gettype( defs, e. view_conv( ). sub( ));
         if( tp. sel( ) != exprtype_unknown && tp. sel( ) != exprtype_tuple )
            return exprtype_error;
         else
            return exprtype_single;
      }
   }
   std::cout << "unknown selector in regexp::gettype:  " << e. sel( ) << "\n";

   throw std::logic_error( "regexp::gettype" );

}


bool regexp::checktypes( defmap& defs )
{
   std::cout << "checking the types\n";

   auto mp = dependencymap( defs );
   identifier::map< identifier::set > used;
      // used. at(id) contains the identifiers whose automata
      // use id.

   for( const auto& p : mp )
   {
      for( const auto& u : p. second )
      {
         if( !defs. contains(u))
         { 
            std::cout << "automaton for " << p. first;
            std::cout << " uses undefined identifier " << u << "\n";
            return false;
         }
         else
            used[u]. insert( p. first );
      }
   }

   std::cout << "the use table:\n";
   for( const auto& p : used )
   {
      std::cout << p. first << "\n";
      for( const auto& u : p. second )
         std::cout << "   " << u << "\n";
   }

   for( auto& d : defs )
      d. second. tp = exprtype_unknown;

   // Types need to be computed in a fixed point iteration.
   // We compute a first type for every automaton,
   // and remember the changes: 

   std::queue< identifier > changed;
   for( auto& d : defs )
   {
      d. second. tp = gettype( defs, d. second. e );
      if( d. second. tp. sel( ) != exprtype_unknown )
         changed. push( d. first ); 
   }

   std::cout << defs << "\n";
   std::cout << changed. size( ) << "\n";

   throw std::logic_error( "quitting" );

   while( changed. size( )) 
   {
      auto id = changed. front( );
      changed. pop( );
      std::cout << "looking at " << id << "\n";

      for( const auto& neighbour : used. at( id ) )
      { 
         auto tp = gettype( defs, defs. at( neighbour ). e ); 
         if( tp != defs. at( neighbour ). tp ) 
         {
            changed. push( neighbour );
            defs. at( neighbour ). tp = tp;
         }
      }
   }

   // We report the errors:

#if 0
         if( tp. sel( ) == exprtype_error )
         {
            std::cout << "automaton " << d. first << " is ill-typed:\n";
            std::cout << "   " << d. second. e << "\n";
         }

         d. second. tp = tp;
         changed. push_back( std::pair( d. first, :               
         std::cout << d. first << " " << tp << "\n";
         throw std::logic_error( "es besteht handlungsbedarf" );
      }
#endif
}
