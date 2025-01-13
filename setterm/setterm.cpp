
// This code was automatically built by TreeGen
// Written by Hans de Nivelle, see www.compiler-tools.eu

#include "setterm.h"

setterm::setterm::setterm( const setterm& from )
   : _ssss( from. _ssss )
{
   // std::cout << "setterm( const setterm& " << from. _ssss << " )";
   
   switch( from. _ssss )
   {
   case setterm_char:
   case setterm_bool:
      repr. _fld00. heap = takeshare( from. repr. _fld00. heap );
      break;
   case setterm_double:
      repr. _fld01. heap = takeshare( from. repr. _fld01. heap );
      break;
   case setterm_integer:
      repr. _fld02. heap = takeshare( from. repr. _fld02. heap );
      break;
   case setterm_u64:
   case setterm_iter:
      repr. _fld03. heap = takeshare( from. repr. _fld03. heap );
      break;
   case setterm_unit:
   case setterm_never:
      break;
   case setterm_set:
   case setterm_tuple:
      repr. _fld05. heap = takeshare( from. repr. _fld05. heap );
      break;
   case setterm_sel:
      repr. _fld06. heap = takeshare( from. repr. _fld06. heap );
      break;
   }
}

setterm::setterm::setterm( setterm&& from ) noexcept
   : _ssss( from. _ssss )
{
   // std::cout << "setterm( setterm&& " << from. _ssss << " )";
   
   switch( from. _ssss )
   {
   case setterm_char:
   case setterm_bool:
      repr. _fld00. heap = from. repr. _fld00. heap;
      break;
   case setterm_double:
      repr. _fld01. heap = from. repr. _fld01. heap;
      break;
   case setterm_integer:
      repr. _fld02. heap = from. repr. _fld02. heap;
      break;
   case setterm_u64:
   case setterm_iter:
      repr. _fld03. heap = from. repr. _fld03. heap;
      break;
   case setterm_unit:
   case setterm_never:
      break;
   case setterm_set:
   case setterm_tuple:
      repr. _fld05. heap = from. repr. _fld05. heap;
      break;
   case setterm_sel:
      repr. _fld06. heap = from. repr. _fld06. heap;
      break;
   }

   // Leave from in trivial state:
   
   from. _ssss = setterm_never;
   new (&from. repr) options( );
}

// Note that the implementation of assignment is minimalistic.
// One should create special cases for when *this and from are 
// in the same state.

const setterm::setterm & setterm::setterm::operator = ( const setterm& from )
{
   if( this == &from )
      return *this;
   
   switch( from. _ssss )
   {
   case setterm_char:
   case setterm_bool:
      takeshare( from. repr. _fld00. heap );
      break;
   case setterm_double:
      takeshare( from. repr. _fld01. heap );
      break;
   case setterm_integer:
      takeshare( from. repr. _fld02. heap );
      break;
   case setterm_u64:
   case setterm_iter:
      takeshare( from. repr. _fld03. heap );
      break;
   case setterm_set:
   case setterm_tuple:
      takeshare( from. repr. _fld05. heap );
      break;
   case setterm_sel:
      takeshare( from. repr. _fld06. heap );
      break;
   }

   this -> ~setterm( );
   
   _ssss = from. _ssss;
   
   switch( _ssss )
   {
   case setterm_char:
   case setterm_bool:
      repr. _fld00. heap = from. repr. _fld00. heap;
      break;
   case setterm_double:
      repr. _fld01. heap = from. repr. _fld01. heap;
      break;
   case setterm_integer:
      repr. _fld02. heap = from. repr. _fld02. heap;
      break;
   case setterm_u64:
   case setterm_iter:
      repr. _fld03. heap = from. repr. _fld03. heap;
      break;
   case setterm_unit:
   case setterm_never:
      break;
   case setterm_set:
   case setterm_tuple:
      repr. _fld05. heap = from. repr. _fld05. heap;
      break;
   case setterm_sel:
      repr. _fld06. heap = from. repr. _fld06. heap;
      break;
   }

   return *this;
}

// We don't check self assignment in the moving case, because it is UB:

const setterm::setterm & setterm::setterm::operator = ( setterm&& from ) noexcept
{
   if( _ssss == from. _ssss )
   {
      switch( _ssss )
      {
      case setterm_char:
      case setterm_bool:
         dropshare( repr. _fld00. heap );
         repr. _fld00. heap = from. repr. _fld00. heap;
         break;
      case setterm_double:
         dropshare( repr. _fld01. heap );
         repr. _fld01. heap = from. repr. _fld01. heap;
         break;
      case setterm_integer:
         dropshare( repr. _fld02. heap );
         repr. _fld02. heap = from. repr. _fld02. heap;
         break;
      case setterm_u64:
      case setterm_iter:
         dropshare( repr. _fld03. heap );
         repr. _fld03. heap = from. repr. _fld03. heap;
         break;
      case setterm_unit:
      case setterm_never:
         break;
      case setterm_set:
      case setterm_tuple:
         dropshare( repr. _fld05. heap );
         repr. _fld05. heap = from. repr. _fld05. heap;
         break;
      case setterm_sel:
         dropshare( repr. _fld06. heap );
         repr. _fld06. heap = from. repr. _fld06. heap;
         break;
      }

      // Leave from in trivial state:

      from. _ssss = setterm_never;
      new (&from. repr) options( );
      return *this;
   }
   else
   {
      // I believe that this wll be safe, because we have
      // the only reference to other: 

      this -> ~setterm( );

      new (this) setterm( std::move( from ));
      return *this;
   }
}

setterm::setterm::~setterm( ) noexcept
{
   // If there are prefix fields, they will be destroyed automatically

   switch( _ssss )
   {
   case setterm_char:
   case setterm_bool:
      dropshare( repr. _fld00. heap );
      break;
   case setterm_double:
      dropshare( repr. _fld01. heap );
      break;
   case setterm_integer:
      dropshare( repr. _fld02. heap );
      break;
   case setterm_u64:
   case setterm_iter:
      dropshare( repr. _fld03. heap );
      break;
   case setterm_unit:
   case setterm_never:
      break;
   case setterm_set:
   case setterm_tuple:
      dropshare( repr. _fld05. heap );
      break;
   case setterm_sel:
      dropshare( repr. _fld06. heap );
      break;
   }
}

bool setterm::setterm::very_equal_to( const setterm & other ) const
{
   if( _ssss != other. _ssss )
      return false;

   switch( _ssss )
   {
   case setterm_char:
   case setterm_bool:
      if( repr. _fld00. heap != other. repr. _fld00. heap )
         return false;
      return true;
   case setterm_double:
      if( repr. _fld01. heap != other. repr. _fld01. heap )
         return false;
      return true;
   case setterm_integer:
      if( repr. _fld02. heap != other. repr. _fld02. heap )
         return false;
      return true;
   case setterm_u64:
   case setterm_iter:
      if( repr. _fld03. heap != other. repr. _fld03. heap )
         return false;
      return true;
   case setterm_unit:
   case setterm_never:
      return true;
   case setterm_set:
   case setterm_tuple:
      if( repr. _fld05. heap != other. repr. _fld05. heap )
         return false;
      return true;
   case setterm_sel:
      if( repr. _fld06. heap != other. repr. _fld06. heap )
         return false;
      return true;
   }
}

void setterm::setterm::printstate( std::ostream& out ) const
{
   switch( _ssss )
   {
   case setterm_char:
   case setterm_bool:
      tvm::printstate( repr. _fld00. heap, out );
      break;
   case setterm_double:
      tvm::printstate( repr. _fld01. heap, out );
      break;
   case setterm_integer:
      tvm::printstate( repr. _fld02. heap, out );
      break;
   case setterm_u64:
   case setterm_iter:
      tvm::printstate( repr. _fld03. heap, out );
      break;
   case setterm_set:
   case setterm_tuple:
      tvm::printstate( repr. _fld05. heap, out );
      break;
   case setterm_sel:
      tvm::printstate( repr. _fld06. heap, out );
      break;
   }
}

