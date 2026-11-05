
#include "algorithms.h"
#include <queue>


void atm::close_eps( const simple& smp, stateset& set ) 
{
   std::queue< state > unchecked;
   for( auto s : set )
      unchecked. push(s);

   while( unchecked. size( ))
   {
      auto s = unchecked. front( );
      unchecked. pop( );
      auto rg = smp. delta_epsilon. equal_range(s);
      for( auto p = rg. first; p != rg. second; ++ p )
      {
         if( !set. contains( p -> second ))
         {
            unchecked. push( p -> second );
            set. insert( p -> second );
         }
      }
   }
}


atm::stateset atm::apply_tuple( const simple& smp,
                                const stateset& tuple,
                                const stateset& single )
{
   stateset res;
   for( const auto& t : tuple )
   {
      for( const auto& s : single )
      {
         auto r = smp. delta_tuple. equal_range( { t, s } );
         for( auto p = r. first; p != r. second; ++ p )
            res. insert( p -> second );
      }
   }
   return res;
}


atm::stateset atm::apply_set( const simple& smp,
                              const stateset& set,
                              const stateset& element )
{
   stateset res; 
   for( const auto& s : set )
   {
      for( const auto& e : element ) 
      {
         auto r = smp. delta_set. equal_range( { s, e } );  
         for( auto p = r. first; p != r. second; ++ p )
            res. insert( p -> second );  
      }
   }
   return res; 
}


atm::stateset atm::run( const simple& smp, const data::tree& tr ) 
{
   std::cout << "running on " << tr << "\n";
   switch( tr. sel( )) 
   {

#if 0
   case data::tree_never:
      sset. insert( atm. collapsed );
      break;

   case data::tree_unit:
      sset. insert( atm. delta_unit );
      break;
   
   case data::tree_bool:
      sset. insert( atm. delta_bool( data. view_bool(). b() ) );
      break;

#endif
   case data::sel_char:
      {
         stateset res;
         for( const auto& f : smp. delta_char )
            res. insert( f. apply( tr. view_char( ). c( )) );
         close_eps( smp, res );  
         return res;
      }
   case data::sel_usel:
      {
         stateset res; 
         for( const auto& f : smp. delta_usel )
            res. insert( f. apply( tr. view_usel( ). s( )) ); 
         close_eps( smp, res );
         return res; 
      }
   case data::sel_u64:
      {
         stateset res;
         for( const auto& u : smp. delta_u64 )
            res. insert( u. apply( tr. view_u64( ). u( )) );
         close_eps( smp, res );
         return res;
      }

#if 0
   case data::tree_bigint:
      sset. insert( atm. delta_bigint( data. view_bigint(). i() ) );
      break;

   case data::tree_double:
      sset. insert( atm. delta_double( data. view_double(). d() ) );
      break;

#endif

   case data::sel_tuple:
      {
         auto tup = tr. view_tuple( );
         stateset res = { smp. empty_tuple };
         close_eps( smp, res );
 
         for( size_t i = 0; i != tup. size( ); ++ i ) 
         { 
            auto sub = run( smp, tup. val(i));
            res = apply_tuple( smp, res, sub ); 
            close_eps( smp, res ); 
         }
         return res;
      }

   case data::sel_array: 
      {
         auto ar = tr. view_array( );
         stateset res = { smp. empty_set };
         close_eps( smp, res ); 

         for( size_t i = 0; i != ar. size( ); ++ i ) 
         {
            auto sub = run( smp, ar. val(i));
            res = apply_set( smp, res, sub ); 
            close_eps( smp, res );
         }
         return res;
      }
   }
 
   std::cout << "run( ), unrecognized selector " << tr. sel( ) << "\n";
   throw std::logic_error( "atm::run()" );
}


