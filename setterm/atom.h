
// This code was automatically built by TreeGen
// Written by Hans de Nivelle, see www.compiler-tools.eu

#ifndef SETTERM_ATOM_
#define SETTERM_ATOM_

#include <iostream>
#include <utility>
#include <tuple>
#include <initializer_list>
#include "selector.h"


#line 50 "./setterm/setterms.rec"
#include "tvm/includes.h"
   #include "tvm/unit.h"
   #include "util/print.h"
   #include "setterm/setterm.h"
   #include "exactident.h"


namespace setterm { 


   class atom
   {
   private:
      selector _ssss;

      using _loc00 = tvm::unit;
      using _scal00 = std::pair<exactident,setterm>;
      using _rep00 = tvm::unit;
      using _loc01 = tvm::unit;
      using _scal01 = std::tuple<exactident,exactident,setterm>;
      using _rep01 = tvm::unit;
      using _loc02 = tvm::unit;
      using _scal02 = std::tuple<exactident,exactident,exactident,setterm>;
      using _rep02 = tvm::unit;
      using _loc03 = tvm::unit;
      using _scal03 = std::pair<exactident,exactident>;
      using _rep03 = setterm;
      using _loc04 = tvm::unit;
      using _scal04 = tvm::unit;
      using _rep04 = tvm::unit;

      static constexpr bool check = true;

      union options
      {
         tvm::field< _loc00, _scal00, _rep00 > _fld00;
         tvm::field< _loc01, _scal01, _rep01 > _fld01;
         tvm::field< _loc02, _scal02, _rep02 > _fld02;
         tvm::field< _loc03, _scal03, _rep03 > _fld03;
         tvm::field< _loc04, _scal04, _rep04 > _fld04;

         options( ) : _fld04( ) { }
         ~options( ) noexcept { }
      };

   private:
      options repr;

   public:
      atom( ) = delete;
      atom( const atom& );
      atom( atom&& ) noexcept;
      const atom& operator = ( const atom& );
      const atom& operator = ( atom&& ) noexcept;
      ~atom( ) noexcept;
      
      selector sel( ) const { return _ssss; }
      bool very_equal_to( const atom& ) const;
      void printstate( std::ostream& out ) const;
      
      atom( selector sel, const exactident & _xx00, const setterm & _xx01 )
         : _ssss( sel )
      {
         if constexpr( check )
         {
            switch( _ssss )
            {
            case atom1:
               break;
            default:
               throw std::invalid_argument( "wrong selector for constructor" );
            }
         }
         repr. _fld00. heap = takeshare( tvm::constr_scalar< _scal00 > ( std::pair( _xx00, _xx01 ) ));
      }

      atom( selector sel, const exactident & _xx00, const exactident & _xx01, const setterm & _xx02 )
         : _ssss( sel )
      {
         if constexpr( check )
         {
            switch( _ssss )
            {
            case atom2:
               break;
            default:
               throw std::invalid_argument( "wrong selector for constructor" );
            }
         }
         repr. _fld01. heap = takeshare( tvm::constr_scalar< _scal01 > ( std::tuple( _xx00, _xx01, _xx02 ) ));
      }

      atom( selector sel, const exactident & _xx00, const exactident & _xx01, const exactident & _xx02, const setterm & _xx03 )
         : _ssss( sel )
      {
         if constexpr( check )
         {
            switch( _ssss )
            {
            case atom3:
               break;
            default:
               throw std::invalid_argument( "wrong selector for constructor" );
            }
         }
         repr. _fld02. heap = takeshare( tvm::constr_scalar< _scal02 > ( std::tuple( _xx00, _xx01, _xx02, _xx03 ) ));
      }

      template< tvm::const_iterator< _rep03 > It >
      atom( selector sel, const exactident & _xx00, const exactident & _xx01, It begin, It end )
         : _ssss( sel )
      {
         if constexpr( check )
         {
            switch( _ssss )
            {
            case atom4:
               break;
            default:
               throw std::invalid_argument( "wrong selector for constructor" );
            }
         }
         repr. _fld03. heap = takeshare( tvm::constr_scalar_vector< _scal03, _rep03 > ( std::pair( _xx00, _xx01 ), begin, end ));
      }

      atom( selector sel, const exactident & _xx00, const exactident & _xx01, std::initializer_list< _rep03 > repeated )
         : atom( sel, _xx00, _xx01, repeated. begin( ), repeated. end( ) )
      { }

      atom( selector sel )
         : _ssss( sel )
      {
         if constexpr( check )
         {
            switch( _ssss )
            {
            case atom0:
               break;
            default:
               throw std::invalid_argument( "wrong selector for constructor" );
            }
         }
      }

      bool option_is_atom1( ) const noexcept
      {
         switch( _ssss )
         {
         case atom1:
            return true;
         default:
            return false;
         }
      }

      struct const_atom1
      {
         const atom* _xxxx;
         const atom & operator * ( ) const { return * _xxxx; }
         const_atom1( const atom* _xxxx ) : _xxxx( _xxxx ) { }

         const exactident & v( ) const { return _xxxx -> repr. _fld00. heap -> scal. first; }
         const setterm & s( ) const { return _xxxx -> repr. _fld00. heap -> scal. second; }
      };

      const_atom1 view_atom1( ) const
      {
         if constexpr( check )
         {
            if( !option_is_atom1( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }

      struct mut_atom1
      {
         atom* _xxxx;
         mut_atom1( atom* _xxxx ) : _xxxx( _xxxx ) { }
         const atom & operator * ( ) const { return * _xxxx; }

         const exactident & v( ) const { return _xxxx -> repr. _fld00. heap -> scal. first; }
         exactident extr_v( ) const {
            if( iswritable( _xxxx -> repr. _fld00. heap ))
               return std::move( _xxxx -> repr. _fld00. heap -> scal. first );
            else
               return _xxxx -> repr. _fld00. heap -> scal. first;
         }
         void update_v( const exactident & repl ) const
         {
            if( tvm::distinct( _xxxx -> repr. _fld00. heap -> scal. first, repl ))
            {
               _xxxx -> repr. _fld00. heap = takeshare( replacebywritable( _xxxx -> repr. _fld00. heap ));
               _xxxx -> repr. _fld00. heap -> scal. first = repl;
            }
         }
         const setterm & s( ) const { return _xxxx -> repr. _fld00. heap -> scal. second; }
         setterm extr_s( ) const {
            if( iswritable( _xxxx -> repr. _fld00. heap ))
               return std::move( _xxxx -> repr. _fld00. heap -> scal. second );
            else
               return _xxxx -> repr. _fld00. heap -> scal. second;
         }
         void update_s( const setterm & repl ) const
         {
            if( tvm::distinct( _xxxx -> repr. _fld00. heap -> scal. second, repl ))
            {
               _xxxx -> repr. _fld00. heap = takeshare( replacebywritable( _xxxx -> repr. _fld00. heap ));
               _xxxx -> repr. _fld00. heap -> scal. second = repl;
            }
         }
      };

      mut_atom1 view_atom1( )
      {
         if constexpr( check )
         {
            if( !option_is_atom1( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }
      
      bool option_is_atom2( ) const noexcept
      {
         switch( _ssss )
         {
         case atom2:
            return true;
         default:
            return false;
         }
      }

      struct const_atom2
      {
         const atom* _xxxx;
         const atom & operator * ( ) const { return * _xxxx; }
         const_atom2( const atom* _xxxx ) : _xxxx( _xxxx ) { }

         const exactident & v( ) const { return get<0> ( _xxxx -> repr. _fld01. heap -> scal ); }
         const exactident & i( ) const { return get<1> ( _xxxx -> repr. _fld01. heap -> scal ); }
         const setterm & s( ) const { return get<2> ( _xxxx -> repr. _fld01. heap -> scal ); }
      };

      const_atom2 view_atom2( ) const
      {
         if constexpr( check )
         {
            if( !option_is_atom2( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }

      struct mut_atom2
      {
         atom* _xxxx;
         mut_atom2( atom* _xxxx ) : _xxxx( _xxxx ) { }
         const atom & operator * ( ) const { return * _xxxx; }

         const exactident & v( ) const { return get<0> ( _xxxx -> repr. _fld01. heap -> scal ); }
         exactident extr_v( ) const {
            if( iswritable( _xxxx -> repr. _fld01. heap ))
               return std::move( get<0> ( _xxxx -> repr. _fld01. heap -> scal ) );
            else
               return get<0> ( _xxxx -> repr. _fld01. heap -> scal );
         }
         void update_v( const exactident & repl ) const
         {
            if( tvm::distinct( get<0> ( _xxxx -> repr. _fld01. heap -> scal ), repl ))
            {
               _xxxx -> repr. _fld01. heap = takeshare( replacebywritable( _xxxx -> repr. _fld01. heap ));
               get<0> ( _xxxx -> repr. _fld01. heap -> scal ) = repl;
            }
         }
         const exactident & i( ) const { return get<1> ( _xxxx -> repr. _fld01. heap -> scal ); }
         exactident extr_i( ) const {
            if( iswritable( _xxxx -> repr. _fld01. heap ))
               return std::move( get<1> ( _xxxx -> repr. _fld01. heap -> scal ) );
            else
               return get<1> ( _xxxx -> repr. _fld01. heap -> scal );
         }
         void update_i( const exactident & repl ) const
         {
            if( tvm::distinct( get<1> ( _xxxx -> repr. _fld01. heap -> scal ), repl ))
            {
               _xxxx -> repr. _fld01. heap = takeshare( replacebywritable( _xxxx -> repr. _fld01. heap ));
               get<1> ( _xxxx -> repr. _fld01. heap -> scal ) = repl;
            }
         }
         const setterm & s( ) const { return get<2> ( _xxxx -> repr. _fld01. heap -> scal ); }
         setterm extr_s( ) const {
            if( iswritable( _xxxx -> repr. _fld01. heap ))
               return std::move( get<2> ( _xxxx -> repr. _fld01. heap -> scal ) );
            else
               return get<2> ( _xxxx -> repr. _fld01. heap -> scal );
         }
         void update_s( const setterm & repl ) const
         {
            if( tvm::distinct( get<2> ( _xxxx -> repr. _fld01. heap -> scal ), repl ))
            {
               _xxxx -> repr. _fld01. heap = takeshare( replacebywritable( _xxxx -> repr. _fld01. heap ));
               get<2> ( _xxxx -> repr. _fld01. heap -> scal ) = repl;
            }
         }
      };

      mut_atom2 view_atom2( )
      {
         if constexpr( check )
         {
            if( !option_is_atom2( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }
      
      bool option_is_atom3( ) const noexcept
      {
         switch( _ssss )
         {
         case atom3:
            return true;
         default:
            return false;
         }
      }

      struct const_atom3
      {
         const atom* _xxxx;
         const atom & operator * ( ) const { return * _xxxx; }
         const_atom3( const atom* _xxxx ) : _xxxx( _xxxx ) { }

         const exactident & v( ) const { return get<0> ( _xxxx -> repr. _fld02. heap -> scal ); }
         const exactident & t1( ) const { return get<1> ( _xxxx -> repr. _fld02. heap -> scal ); }
         const exactident & t2( ) const { return get<2> ( _xxxx -> repr. _fld02. heap -> scal ); }
         const setterm & s( ) const { return get<3> ( _xxxx -> repr. _fld02. heap -> scal ); }
      };

      const_atom3 view_atom3( ) const
      {
         if constexpr( check )
         {
            if( !option_is_atom3( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }

      struct mut_atom3
      {
         atom* _xxxx;
         mut_atom3( atom* _xxxx ) : _xxxx( _xxxx ) { }
         const atom & operator * ( ) const { return * _xxxx; }

         const exactident & v( ) const { return get<0> ( _xxxx -> repr. _fld02. heap -> scal ); }
         exactident extr_v( ) const {
            if( iswritable( _xxxx -> repr. _fld02. heap ))
               return std::move( get<0> ( _xxxx -> repr. _fld02. heap -> scal ) );
            else
               return get<0> ( _xxxx -> repr. _fld02. heap -> scal );
         }
         void update_v( const exactident & repl ) const
         {
            if( tvm::distinct( get<0> ( _xxxx -> repr. _fld02. heap -> scal ), repl ))
            {
               _xxxx -> repr. _fld02. heap = takeshare( replacebywritable( _xxxx -> repr. _fld02. heap ));
               get<0> ( _xxxx -> repr. _fld02. heap -> scal ) = repl;
            }
         }
         const exactident & t1( ) const { return get<1> ( _xxxx -> repr. _fld02. heap -> scal ); }
         exactident extr_t1( ) const {
            if( iswritable( _xxxx -> repr. _fld02. heap ))
               return std::move( get<1> ( _xxxx -> repr. _fld02. heap -> scal ) );
            else
               return get<1> ( _xxxx -> repr. _fld02. heap -> scal );
         }
         void update_t1( const exactident & repl ) const
         {
            if( tvm::distinct( get<1> ( _xxxx -> repr. _fld02. heap -> scal ), repl ))
            {
               _xxxx -> repr. _fld02. heap = takeshare( replacebywritable( _xxxx -> repr. _fld02. heap ));
               get<1> ( _xxxx -> repr. _fld02. heap -> scal ) = repl;
            }
         }
         const exactident & t2( ) const { return get<2> ( _xxxx -> repr. _fld02. heap -> scal ); }
         exactident extr_t2( ) const {
            if( iswritable( _xxxx -> repr. _fld02. heap ))
               return std::move( get<2> ( _xxxx -> repr. _fld02. heap -> scal ) );
            else
               return get<2> ( _xxxx -> repr. _fld02. heap -> scal );
         }
         void update_t2( const exactident & repl ) const
         {
            if( tvm::distinct( get<2> ( _xxxx -> repr. _fld02. heap -> scal ), repl ))
            {
               _xxxx -> repr. _fld02. heap = takeshare( replacebywritable( _xxxx -> repr. _fld02. heap ));
               get<2> ( _xxxx -> repr. _fld02. heap -> scal ) = repl;
            }
         }
         const setterm & s( ) const { return get<3> ( _xxxx -> repr. _fld02. heap -> scal ); }
         setterm extr_s( ) const {
            if( iswritable( _xxxx -> repr. _fld02. heap ))
               return std::move( get<3> ( _xxxx -> repr. _fld02. heap -> scal ) );
            else
               return get<3> ( _xxxx -> repr. _fld02. heap -> scal );
         }
         void update_s( const setterm & repl ) const
         {
            if( tvm::distinct( get<3> ( _xxxx -> repr. _fld02. heap -> scal ), repl ))
            {
               _xxxx -> repr. _fld02. heap = takeshare( replacebywritable( _xxxx -> repr. _fld02. heap ));
               get<3> ( _xxxx -> repr. _fld02. heap -> scal ) = repl;
            }
         }
      };

      mut_atom3 view_atom3( )
      {
         if constexpr( check )
         {
            if( !option_is_atom3( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }
      
      bool option_is_atom4( ) const noexcept
      {
         switch( _ssss )
         {
         case atom4:
            return true;
         default:
            return false;
         }
      }

      struct const_atom4
      {
         const atom* _xxxx;
         const atom & operator * ( ) const { return * _xxxx; }
         const_atom4( const atom* _xxxx ) : _xxxx( _xxxx ) { }

         const exactident & t1( ) const { return _xxxx -> repr. _fld03. heap -> scal. first; }
         const exactident & t2( ) const { return _xxxx -> repr. _fld03. heap -> scal. second; }
         size_t size( ) const { return _xxxx -> repr. _fld03. heap -> size( ); }
         const setterm & s( size_t _iiii ) const
            { return _xxxx -> repr. _fld03. heap -> begin( ) [ _iiii ]; }
      };

      const_atom4 view_atom4( ) const
      {
         if constexpr( check )
         {
            if( !option_is_atom4( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }

      struct mut_atom4
      {
         atom* _xxxx;
         mut_atom4( atom* _xxxx ) : _xxxx( _xxxx ) { }
         const atom & operator * ( ) const { return * _xxxx; }

         const exactident & t1( ) const { return _xxxx -> repr. _fld03. heap -> scal. first; }
         exactident extr_t1( ) const {
            if( iswritable( _xxxx -> repr. _fld03. heap ))
               return std::move( _xxxx -> repr. _fld03. heap -> scal. first );
            else
               return _xxxx -> repr. _fld03. heap -> scal. first;
         }
         void update_t1( const exactident & repl ) const
         {
            if( tvm::distinct( _xxxx -> repr. _fld03. heap -> scal. first, repl ))
            {
               _xxxx -> repr. _fld03. heap = takeshare( replacebywritable( _xxxx -> repr. _fld03. heap ));
               _xxxx -> repr. _fld03. heap -> scal. first = repl;
            }
         }
         const exactident & t2( ) const { return _xxxx -> repr. _fld03. heap -> scal. second; }
         exactident extr_t2( ) const {
            if( iswritable( _xxxx -> repr. _fld03. heap ))
               return std::move( _xxxx -> repr. _fld03. heap -> scal. second );
            else
               return _xxxx -> repr. _fld03. heap -> scal. second;
         }
         void update_t2( const exactident & repl ) const
         {
            if( tvm::distinct( _xxxx -> repr. _fld03. heap -> scal. second, repl ))
            {
               _xxxx -> repr. _fld03. heap = takeshare( replacebywritable( _xxxx -> repr. _fld03. heap ));
               _xxxx -> repr. _fld03. heap -> scal. second = repl;
            }
         }

         size_t size( ) const { return _xxxx -> repr. _fld03. heap -> size( ); }
         void push_back( const setterm & xx00 ) const
         {
            _xxxx -> repr. _fld03. heap = tvm::push_back( _xxxx -> repr. _fld03. heap, xx00 );
         }
         void pop_back( ) const { _xxxx -> repr. _fld03. heap = tvm::pop_back( _xxxx -> repr. _fld03. heap ); }
         const setterm& s( size_t _iiii ) const
            { return _xxxx -> repr. _fld03. heap -> begin( ) [ _iiii ]; }
         setterm extr_s( size_t _iiii ) const
         {
            if( iswritable( _xxxx -> repr. _fld03. heap ))
               return std::move( _xxxx -> repr. _fld03. heap -> begin( ) [ _iiii ] );
            else
               return _xxxx -> repr. _fld03. heap -> begin( ) [ _iiii ];
         }
         void update_s( size_t _iiii, const setterm & repl ) const
         {
            if( tvm::distinct( _xxxx -> repr. _fld03. heap -> begin( ) [ _iiii ], repl ))
            {
               _xxxx -> repr. _fld03. heap = takeshare( replacebywritable( _xxxx -> repr. _fld03. heap ));
               _xxxx -> repr. _fld03. heap -> begin( ) [ _iiii ] = repl;
            }
         }
      };

      mut_atom4 view_atom4( )
      {
         if constexpr( check )
         {
            if( !option_is_atom4( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }
      
      bool option_is_empty( ) const noexcept
      {
         switch( _ssss )
         {
         case atom0:
            return true;
         default:
            return false;
         }
      }

      struct const_empty
      {
         const atom* _xxxx;
         const atom & operator * ( ) const { return * _xxxx; }
         const_empty( const atom* _xxxx ) : _xxxx( _xxxx ) { }
      };

      const_empty view_empty( ) const
      {
         if constexpr( check )
         {
            if( !option_is_empty( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }

      struct mut_empty
      {
         atom* _xxxx;
         mut_empty( atom* _xxxx ) : _xxxx( _xxxx ) { }
         const atom & operator * ( ) const { return * _xxxx; }
      };

      mut_empty view_empty( )
      {
         if constexpr( check )
         {
            if( !option_is_empty( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }
      


#line 58 "./setterm/setterms.rec"
struct equal_to
   {
      equal_to( ) noexcept = default;
      bool operator ( ) ( const atom&, const atom& ) const;  
   };
   void print( std::ostream& ) const;

   };


#line 67 "./setterm/setterms.rec"
inline bool operator== ( const atom& a1, const atom& a2 )
	{ auto eq = atom::equal_to( ); return eq( a1, a2 ); }

}

#endif

