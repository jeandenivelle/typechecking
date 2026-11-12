
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

   case tup_exact:
   case tup_prefix:
      {
         auto tup = e. view_tuple( );
         for( size_t i = 0; i != tup. size( ); ++ i )
            collect( tup. sub(i), defs, c ); 
         return;
      }

   case log_or:
      {
         auto log = e. view_disjunction( );
         for( size_t i = 0; i != log. size( ); ++ i )
            collect( log. sub(i), defs, c );
         return;
      }
#if 0
   case single2set:
      collect( e. view_single2set( ). elem( ), defs, c ); 
      return;

   case set2single:
      collect( e. view_set2single( ). sub( ), defs, c );
      return; 
#endif
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
      collect( d. second, used, cntr );

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
      return exprtype_single; 
   
   case tup_exact:
   case tup_prefix:
      {
         auto tup = e. view_tuple( );
         for( size_t i = 0; i != tup. size( ); ++ i )
         {
            auto tp = gettype( defs, tup. sub(i) );
            if( !tp. isbelow( exprtype_single ))
               return exprtype_error; 
         }
         return exprtype_single;
      } 

   case log_or:
      {
         auto log = e. view_disjunction( );
         exprtype res = exprtype_unknown;
         for( size_t i = 0; i != log. size( ); ++ i )
            res = join( res, gettype( defs, log. sub(i)) );
         return res;
      }

#if 0
   case single2set:
      {
         auto tp = gettype( defs, e. view_single2set( ). elem( ));
         if( tp. isbelow( exprtype_single ))
            return exprtype_set; 
         else
            return exprtype_error;
      }
#endif
#if 0
   case concat:
      {
         auto cat = e. view_concat( );
         for( size_t i = 0; i != cat. size( ); ++ i )
         {
            auto tp = gettype( defs, cat. sub(i) );
            if( !tp. isbelow( exprtype_set ))
               return exprtype_error;
         }
         return exprtype_set;
      }
#endif

#if 0
   case set2single:
      {
         auto tp = gettype( defs, e. view_set2single( ). sub( ));
         if( tp. isbelow( exprtype_set ))
            return exprtype_single;
         else
            return exprtype_error;
      }

#endif
   }
   std::cout << "unknown selector in regexp::gettype:  " << e. sel( ) << "\n";

   throw std::logic_error( "regexp::gettype" );
}


bool regexp::checktypes( defmap& defs )
{
#if 0
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
      auto tp = gettype( defs, d. second. e );
      if( tp. sel( ) == exprtype_error )
         std::cout << d. first << " is typed as error\n";

      if( tp != exprtype_unknown )
      {
         d. second. tp = tp; 
         changed. push( d. first ); 
      }
   }

   while( changed. size( )) 
   {
      auto id = changed. front( );
      changed. pop( );

      for( const auto& occursin : used. at( id ))
      { 
         auto tp = gettype( defs, defs. at( occursin ). e ); 
         if( tp != defs. at( occursin ). tp ) 
         {
            if( tp == exprtype_error )
               std::cout << occursin << " is typed as error\n";

            changed. push( occursin );
            defs. at( occursin ). tp = tp;
         }
      }
   }

   // We report the errors:

   size_t nrproblems = 0;
   for( const auto& d : defs ) 
   {
      if( d. second. tp == exprtype_error ||
          d. second. tp == exprtype_unknown )
      {
         ++ nrproblems; 
         std::cout << "could not assign a type to " << d. first << "\n";
      }
   }
   return nrproblems == 0;
#endif
}

