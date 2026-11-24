
// Written by Hans de Nivelle, November 2026.

#ifndef BOOLSWITCH_
#define BOOLSWITCH_

template< typename T >
struct boolswitch
{
   T yes;
   T no;

   boolswitch( const T& yes, const T& no )
      : yes( yes ), no( no )
   { }

   const T& operator( ) ( bool b ) const
      { return b ? yes : no; }
};

#endif

