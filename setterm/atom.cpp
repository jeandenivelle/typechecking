
// This code was automatically built by TreeGen
// Written by Hans de Nivelle, see www.compiler-tools.eu

#include "atom.h"

setterm::atom::atom( const atom& from )
   : _ssss( from. _ssss )
{
   // std::cout << "atom( const atom& " << from. _ssss << " )";
   
   switch( from. _ssss )
   {
   case atom1:
      repr. _fld00. heap = takeshare( from. repr. _fld00. heap );
      break;
   case atom2:
      repr. _fld01. heap = takeshare( from. repr. _fld01. heap );
      break;
   case atom3:
      repr. _fld02. heap = takeshare( from. repr. _fld02. heap );
      break;
   case atom4:
      repr. _fld03. heap = takeshare( from. repr. _fld03. heap );
      break;
   case atom0:
      break;
   }
}

setterm::atom::atom( atom&& from ) noexcept
   : _ssss( from. _ssss )
{
   // std::cout << "atom( atom&& " << from. _ssss << " )";
   
   switch( from. _ssss )
   {
   case atom1:
      repr. _fld00. heap = from. repr. _fld00. heap;
      break;
   case atom2:
      repr. _fld01. heap = from. repr. _fld01. heap;
      break;
   case atom3:
      repr. _fld02. heap = from. repr. _fld02. heap;
      break;
   case atom4:
      repr. _fld03. heap = from. repr. _fld03. heap;
      break;
   case atom0:
      break;
   }

   // Leave from in trivial state:
   
   from. _ssss = atom0;
   new (&from. repr) options( );
}

// Note that the implementation of assignment is minimalistic.
// One should create special cases for when *this and from are 
// in the same state.

const setterm::atom & setterm::atom::operator = ( const atom& from )
{
   if( this == &from )
      return *this;
   
   switch( from. _ssss )
   {
   case atom1:
      takeshare( from. repr. _fld00. heap );
      break;
   case atom2:
      takeshare( from. repr. _fld01. heap );
      break;
   case atom3:
      takeshare( from. repr. _fld02. heap );
      break;
   case atom4:
      takeshare( from. repr. _fld03. heap );
      break;
   }

   this -> ~atom( );
   
   _ssss = from. _ssss;
   
   switch( _ssss )
   {
   case atom1:
      repr. _fld00. heap = from. repr. _fld00. heap;
      break;
   case atom2:
      repr. _fld01. heap = from. repr. _fld01. heap;
      break;
   case atom3:
      repr. _fld02. heap = from. repr. _fld02. heap;
      break;
   case atom4:
      repr. _fld03. heap = from. repr. _fld03. heap;
      break;
   case atom0:
      break;
   }

   return *this;
}

// We don't check self assignment in the moving case, because it is UB:

const setterm::atom & setterm::atom::operator = ( atom&& from ) noexcept
{
   if( _ssss == from. _ssss )
   {
      switch( _ssss )
      {
      case atom1:
         dropshare( repr. _fld00. heap );
         repr. _fld00. heap = from. repr. _fld00. heap;
         break;
      case atom2:
         dropshare( repr. _fld01. heap );
         repr. _fld01. heap = from. repr. _fld01. heap;
         break;
      case atom3:
         dropshare( repr. _fld02. heap );
         repr. _fld02. heap = from. repr. _fld02. heap;
         break;
      case atom4:
         dropshare( repr. _fld03. heap );
         repr. _fld03. heap = from. repr. _fld03. heap;
         break;
      case atom0:
         break;
      }

      // Leave from in trivial state:

      from. _ssss = atom0;
      new (&from. repr) options( );
      return *this;
   }
   else
   {
      // I believe that this wll be safe, because we have
      // the only reference to other: 

      this -> ~atom( );

      new (this) atom( std::move( from ));
      return *this;
   }
}

setterm::atom::~atom( ) noexcept
{
   // If there are prefix fields, they will be destroyed automatically

   switch( _ssss )
   {
   case atom1:
      dropshare( repr. _fld00. heap );
      break;
   case atom2:
      dropshare( repr. _fld01. heap );
      break;
   case atom3:
      dropshare( repr. _fld02. heap );
      break;
   case atom4:
      dropshare( repr. _fld03. heap );
      break;
   case atom0:
      break;
   }
}

bool setterm::atom::very_equal_to( const atom & other ) const
{
   if( _ssss != other. _ssss )
      return false;

   switch( _ssss )
   {
   case atom1:
      if( repr. _fld00. heap != other. repr. _fld00. heap )
         return false;
      return true;
   case atom2:
      if( repr. _fld01. heap != other. repr. _fld01. heap )
         return false;
      return true;
   case atom3:
      if( repr. _fld02. heap != other. repr. _fld02. heap )
         return false;
      return true;
   case atom4:
      if( repr. _fld03. heap != other. repr. _fld03. heap )
         return false;
      return true;
   case atom0:
      return true;
   }
}

void setterm::atom::printstate( std::ostream& out ) const
{
   switch( _ssss )
   {
   case atom1:
      tvm::printstate( repr. _fld00. heap, out );
      break;
   case atom2:
      tvm::printstate( repr. _fld01. heap, out );
      break;
   case atom3:
      tvm::printstate( repr. _fld02. heap, out );
      break;
   case atom4:
      tvm::printstate( repr. _fld03. heap, out );
      break;
   }
}

