
// This code was automatically built by TreeGen
// Written by Hans de Nivelle, see www.compiler-tools.eu

#ifndef SETTERM_SETTERM_
#define SETTERM_SETTERM_

#include <iostream>
#include <utility>
#include <tuple>
#include <initializer_list>
#include "selector.h"


#line 20 "./setterm/setterms.rec"
#include "tvm/includes.h"
   #include "tvm/unit.h" 
   #include "usel.h"
   #include "util/print.h"
   #include "util/bigint.h"


namespace setterm { 


   class setterm
   {
   private:
      selector _ssss;

      using _loc00 = tvm::unit;
      using _scal00 = char;
      using _rep00 = tvm::unit;
      using _loc01 = tvm::unit;
      using _scal01 = double;
      using _rep01 = tvm::unit;
      using _loc02 = tvm::unit;
      using _scal02 = bigint;
      using _rep02 = tvm::unit;
      using _loc03 = tvm::unit;
      using _scal03 = size_t;
      using _rep03 = tvm::unit;
      using _loc04 = tvm::unit;
      using _scal04 = tvm::unit;
      using _rep04 = tvm::unit;
      using _loc05 = tvm::unit;
      using _scal05 = tvm::unit;
      using _rep05 = setterm;
      using _loc06 = tvm::unit;
      using _scal06 = usel;
      using _rep06 = tvm::unit;

      static constexpr bool check = true;

      union options
      {
         tvm::field< _loc00, _scal00, _rep00 > _fld00;
         tvm::field< _loc01, _scal01, _rep01 > _fld01;
         tvm::field< _loc02, _scal02, _rep02 > _fld02;
         tvm::field< _loc03, _scal03, _rep03 > _fld03;
         tvm::field< _loc04, _scal04, _rep04 > _fld04;
         tvm::field< _loc05, _scal05, _rep05 > _fld05;
         tvm::field< _loc06, _scal06, _rep06 > _fld06;

         options( ) : _fld04( ) { }
         ~options( ) noexcept { }
      };

   private:
      options repr;

   public:
      setterm( ) = delete;
      setterm( const setterm& );
      setterm( setterm&& ) noexcept;
      const setterm& operator = ( const setterm& );
      const setterm& operator = ( setterm&& ) noexcept;
      ~setterm( ) noexcept;
      
      selector sel( ) const { return _ssss; }
      bool very_equal_to( const setterm& ) const;
      void printstate( std::ostream& out ) const;
      
      setterm( selector sel, const char & _xx00 )
         : _ssss( sel )
      {
         if constexpr( check )
         {
            switch( _ssss )
            {
            case setterm_char:
            case setterm_bool:
               break;
            default:
               throw std::invalid_argument( "wrong selector for constructor" );
            }
         }
         repr. _fld00. heap = takeshare( tvm::constr_scalar< _scal00 > ( _xx00 ));
      }

      setterm( selector sel, const double & _xx00 )
         : _ssss( sel )
      {
         if constexpr( check )
         {
            switch( _ssss )
            {
            case setterm_double:
               break;
            default:
               throw std::invalid_argument( "wrong selector for constructor" );
            }
         }
         repr. _fld01. heap = takeshare( tvm::constr_scalar< _scal01 > ( _xx00 ));
      }

      setterm( selector sel, const bigint & _xx00 )
         : _ssss( sel )
      {
         if constexpr( check )
         {
            switch( _ssss )
            {
            case setterm_integer:
               break;
            default:
               throw std::invalid_argument( "wrong selector for constructor" );
            }
         }
         repr. _fld02. heap = takeshare( tvm::constr_scalar< _scal02 > ( _xx00 ));
      }

      setterm( selector sel, const size_t & _xx00 )
         : _ssss( sel )
      {
         if constexpr( check )
         {
            switch( _ssss )
            {
            case setterm_u64:
            case setterm_iter:
               break;
            default:
               throw std::invalid_argument( "wrong selector for constructor" );
            }
         }
         repr. _fld03. heap = takeshare( tvm::constr_scalar< _scal03 > ( _xx00 ));
      }

      setterm( selector sel )
         : _ssss( sel )
      {
         if constexpr( check )
         {
            switch( _ssss )
            {
            case setterm_unit:
            case setterm_never:
               break;
            default:
               throw std::invalid_argument( "wrong selector for constructor" );
            }
         }
      }

      template< tvm::const_iterator< _rep05 > It >
      setterm( selector sel, It begin, It end )
         : _ssss( sel )
      {
         if constexpr( check )
         {
            switch( _ssss )
            {
            case setterm_set:
            case setterm_tuple:
               break;
            default:
               throw std::invalid_argument( "wrong selector for constructor" );
            }
         }
         repr. _fld05. heap = takeshare( tvm::constr_scalar_vector< _scal05, _rep05 > ( tvm::unit( ), begin, end ));
      }

      setterm( selector sel, std::initializer_list< _rep05 > repeated )
         : setterm( sel, repeated. begin( ), repeated. end( ) )
      { }

      setterm( selector sel, const usel & _xx00 )
         : _ssss( sel )
      {
         if constexpr( check )
         {
            switch( _ssss )
            {
            case setterm_sel:
               break;
            default:
               throw std::invalid_argument( "wrong selector for constructor" );
            }
         }
         repr. _fld06. heap = takeshare( tvm::constr_scalar< _scal06 > ( _xx00 ));
      }

      bool option_is_bool( ) const noexcept
      {
         switch( _ssss )
         {
         case setterm_bool:
            return true;
         default:
            return false;
         }
      }

      struct const_bool
      {
         const setterm* _xxxx;
         const setterm & operator * ( ) const { return * _xxxx; }
         const_bool( const setterm* _xxxx ) : _xxxx( _xxxx ) { }

         const char & b( ) const { return _xxxx -> repr. _fld00. heap -> scal; }
      };

      const_bool view_bool( ) const
      {
         if constexpr( check )
         {
            if( !option_is_bool( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }

      struct mut_bool
      {
         setterm* _xxxx;
         mut_bool( setterm* _xxxx ) : _xxxx( _xxxx ) { }
         const setterm & operator * ( ) const { return * _xxxx; }

         const char & b( ) const { return _xxxx -> repr. _fld00. heap -> scal; }
         char extr_b( ) const {
            if( iswritable( _xxxx -> repr. _fld00. heap ))
               return std::move( _xxxx -> repr. _fld00. heap -> scal );
            else
               return _xxxx -> repr. _fld00. heap -> scal;
         }
         void update_b( const char & repl ) const
         {
            if( tvm::distinct( _xxxx -> repr. _fld00. heap -> scal, repl ))
            {
               _xxxx -> repr. _fld00. heap = takeshare( replacebywritable( _xxxx -> repr. _fld00. heap ));
               _xxxx -> repr. _fld00. heap -> scal = repl;
            }
         }
      };

      mut_bool view_bool( )
      {
         if constexpr( check )
         {
            if( !option_is_bool( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }
      
      bool option_is_char( ) const noexcept
      {
         switch( _ssss )
         {
         case setterm_char:
            return true;
         default:
            return false;
         }
      }

      struct const_char
      {
         const setterm* _xxxx;
         const setterm & operator * ( ) const { return * _xxxx; }
         const_char( const setterm* _xxxx ) : _xxxx( _xxxx ) { }

         const char & c( ) const { return _xxxx -> repr. _fld00. heap -> scal; }
      };

      const_char view_char( ) const
      {
         if constexpr( check )
         {
            if( !option_is_char( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }

      struct mut_char
      {
         setterm* _xxxx;
         mut_char( setterm* _xxxx ) : _xxxx( _xxxx ) { }
         const setterm & operator * ( ) const { return * _xxxx; }

         const char & c( ) const { return _xxxx -> repr. _fld00. heap -> scal; }
         char extr_c( ) const {
            if( iswritable( _xxxx -> repr. _fld00. heap ))
               return std::move( _xxxx -> repr. _fld00. heap -> scal );
            else
               return _xxxx -> repr. _fld00. heap -> scal;
         }
         void update_c( const char & repl ) const
         {
            if( tvm::distinct( _xxxx -> repr. _fld00. heap -> scal, repl ))
            {
               _xxxx -> repr. _fld00. heap = takeshare( replacebywritable( _xxxx -> repr. _fld00. heap ));
               _xxxx -> repr. _fld00. heap -> scal = repl;
            }
         }
      };

      mut_char view_char( )
      {
         if constexpr( check )
         {
            if( !option_is_char( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }
      
      bool option_is_double( ) const noexcept
      {
         switch( _ssss )
         {
         case setterm_double:
            return true;
         default:
            return false;
         }
      }

      struct const_double
      {
         const setterm* _xxxx;
         const setterm & operator * ( ) const { return * _xxxx; }
         const_double( const setterm* _xxxx ) : _xxxx( _xxxx ) { }

         const double & d( ) const { return _xxxx -> repr. _fld01. heap -> scal; }
      };

      const_double view_double( ) const
      {
         if constexpr( check )
         {
            if( !option_is_double( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }

      struct mut_double
      {
         setterm* _xxxx;
         mut_double( setterm* _xxxx ) : _xxxx( _xxxx ) { }
         const setterm & operator * ( ) const { return * _xxxx; }

         const double & d( ) const { return _xxxx -> repr. _fld01. heap -> scal; }
         double extr_d( ) const {
            if( iswritable( _xxxx -> repr. _fld01. heap ))
               return std::move( _xxxx -> repr. _fld01. heap -> scal );
            else
               return _xxxx -> repr. _fld01. heap -> scal;
         }
         void update_d( const double & repl ) const
         {
            if( tvm::distinct( _xxxx -> repr. _fld01. heap -> scal, repl ))
            {
               _xxxx -> repr. _fld01. heap = takeshare( replacebywritable( _xxxx -> repr. _fld01. heap ));
               _xxxx -> repr. _fld01. heap -> scal = repl;
            }
         }
      };

      mut_double view_double( )
      {
         if constexpr( check )
         {
            if( !option_is_double( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }
      
      bool option_is_integer( ) const noexcept
      {
         switch( _ssss )
         {
         case setterm_integer:
            return true;
         default:
            return false;
         }
      }

      struct const_integer
      {
         const setterm* _xxxx;
         const setterm & operator * ( ) const { return * _xxxx; }
         const_integer( const setterm* _xxxx ) : _xxxx( _xxxx ) { }

         const bigint & i( ) const { return _xxxx -> repr. _fld02. heap -> scal; }
      };

      const_integer view_integer( ) const
      {
         if constexpr( check )
         {
            if( !option_is_integer( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }

      struct mut_integer
      {
         setterm* _xxxx;
         mut_integer( setterm* _xxxx ) : _xxxx( _xxxx ) { }
         const setterm & operator * ( ) const { return * _xxxx; }

         const bigint & i( ) const { return _xxxx -> repr. _fld02. heap -> scal; }
         bigint extr_i( ) const {
            if( iswritable( _xxxx -> repr. _fld02. heap ))
               return std::move( _xxxx -> repr. _fld02. heap -> scal );
            else
               return _xxxx -> repr. _fld02. heap -> scal;
         }
         void update_i( const bigint & repl ) const
         {
            if( tvm::distinct( _xxxx -> repr. _fld02. heap -> scal, repl ))
            {
               _xxxx -> repr. _fld02. heap = takeshare( replacebywritable( _xxxx -> repr. _fld02. heap ));
               _xxxx -> repr. _fld02. heap -> scal = repl;
            }
         }
      };

      mut_integer view_integer( )
      {
         if constexpr( check )
         {
            if( !option_is_integer( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }
      
      bool option_is_iter( ) const noexcept
      {
         switch( _ssss )
         {
         case setterm_iter:
            return true;
         default:
            return false;
         }
      }

      struct const_iter
      {
         const setterm* _xxxx;
         const setterm & operator * ( ) const { return * _xxxx; }
         const_iter( const setterm* _xxxx ) : _xxxx( _xxxx ) { }

         const size_t & s( ) const { return _xxxx -> repr. _fld03. heap -> scal; }
      };

      const_iter view_iter( ) const
      {
         if constexpr( check )
         {
            if( !option_is_iter( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }

      struct mut_iter
      {
         setterm* _xxxx;
         mut_iter( setterm* _xxxx ) : _xxxx( _xxxx ) { }
         const setterm & operator * ( ) const { return * _xxxx; }

         const size_t & s( ) const { return _xxxx -> repr. _fld03. heap -> scal; }
         size_t extr_s( ) const {
            if( iswritable( _xxxx -> repr. _fld03. heap ))
               return std::move( _xxxx -> repr. _fld03. heap -> scal );
            else
               return _xxxx -> repr. _fld03. heap -> scal;
         }
         void update_s( const size_t & repl ) const
         {
            if( tvm::distinct( _xxxx -> repr. _fld03. heap -> scal, repl ))
            {
               _xxxx -> repr. _fld03. heap = takeshare( replacebywritable( _xxxx -> repr. _fld03. heap ));
               _xxxx -> repr. _fld03. heap -> scal = repl;
            }
         }
      };

      mut_iter view_iter( )
      {
         if constexpr( check )
         {
            if( !option_is_iter( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }
      
      bool option_is_never( ) const noexcept
      {
         switch( _ssss )
         {
         case setterm_never:
            return true;
         default:
            return false;
         }
      }

      struct const_never
      {
         const setterm* _xxxx;
         const setterm & operator * ( ) const { return * _xxxx; }
         const_never( const setterm* _xxxx ) : _xxxx( _xxxx ) { }
      };

      const_never view_never( ) const
      {
         if constexpr( check )
         {
            if( !option_is_never( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }

      struct mut_never
      {
         setterm* _xxxx;
         mut_never( setterm* _xxxx ) : _xxxx( _xxxx ) { }
         const setterm & operator * ( ) const { return * _xxxx; }
      };

      mut_never view_never( )
      {
         if constexpr( check )
         {
            if( !option_is_never( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }
      
      bool option_is_repeated( ) const noexcept
      {
         switch( _ssss )
         {
         case setterm_set:
         case setterm_tuple:
            return true;
         default:
            return false;
         }
      }

      struct const_repeated
      {
         const setterm* _xxxx;
         const setterm & operator * ( ) const { return * _xxxx; }
         const_repeated( const setterm* _xxxx ) : _xxxx( _xxxx ) { }
         size_t size( ) const { return _xxxx -> repr. _fld05. heap -> size( ); }
         const setterm & sub( size_t _iiii ) const
            { return _xxxx -> repr. _fld05. heap -> begin( ) [ _iiii ]; }
      };

      const_repeated view_repeated( ) const
      {
         if constexpr( check )
         {
            if( !option_is_repeated( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }

      struct mut_repeated
      {
         setterm* _xxxx;
         mut_repeated( setterm* _xxxx ) : _xxxx( _xxxx ) { }
         const setterm & operator * ( ) const { return * _xxxx; }

         size_t size( ) const { return _xxxx -> repr. _fld05. heap -> size( ); }
         void push_back( const setterm & xx00 ) const
         {
            _xxxx -> repr. _fld05. heap = tvm::push_back( _xxxx -> repr. _fld05. heap, xx00 );
         }
         void pop_back( ) const { _xxxx -> repr. _fld05. heap = tvm::pop_back( _xxxx -> repr. _fld05. heap ); }
         const setterm& sub( size_t _iiii ) const
            { return _xxxx -> repr. _fld05. heap -> begin( ) [ _iiii ]; }
         setterm extr_sub( size_t _iiii ) const
         {
            if( iswritable( _xxxx -> repr. _fld05. heap ))
               return std::move( _xxxx -> repr. _fld05. heap -> begin( ) [ _iiii ] );
            else
               return _xxxx -> repr. _fld05. heap -> begin( ) [ _iiii ];
         }
         void update_sub( size_t _iiii, const setterm & repl ) const
         {
            if( tvm::distinct( _xxxx -> repr. _fld05. heap -> begin( ) [ _iiii ], repl ))
            {
               _xxxx -> repr. _fld05. heap = takeshare( replacebywritable( _xxxx -> repr. _fld05. heap ));
               _xxxx -> repr. _fld05. heap -> begin( ) [ _iiii ] = repl;
            }
         }
      };

      mut_repeated view_repeated( )
      {
         if constexpr( check )
         {
            if( !option_is_repeated( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }
      
      bool option_is_sel( ) const noexcept
      {
         switch( _ssss )
         {
         case setterm_sel:
            return true;
         default:
            return false;
         }
      }

      struct const_sel
      {
         const setterm* _xxxx;
         const setterm & operator * ( ) const { return * _xxxx; }
         const_sel( const setterm* _xxxx ) : _xxxx( _xxxx ) { }

         const usel & s( ) const { return _xxxx -> repr. _fld06. heap -> scal; }
      };

      const_sel view_sel( ) const
      {
         if constexpr( check )
         {
            if( !option_is_sel( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }

      struct mut_sel
      {
         setterm* _xxxx;
         mut_sel( setterm* _xxxx ) : _xxxx( _xxxx ) { }
         const setterm & operator * ( ) const { return * _xxxx; }

         const usel & s( ) const { return _xxxx -> repr. _fld06. heap -> scal; }
         usel extr_s( ) const {
            if( iswritable( _xxxx -> repr. _fld06. heap ))
               return std::move( _xxxx -> repr. _fld06. heap -> scal );
            else
               return _xxxx -> repr. _fld06. heap -> scal;
         }
         void update_s( const usel & repl ) const
         {
            if( tvm::distinct( _xxxx -> repr. _fld06. heap -> scal, repl ))
            {
               _xxxx -> repr. _fld06. heap = takeshare( replacebywritable( _xxxx -> repr. _fld06. heap ));
               _xxxx -> repr. _fld06. heap -> scal = repl;
            }
         }
      };

      mut_sel view_sel( )
      {
         if constexpr( check )
         {
            if( !option_is_sel( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }
      
      bool option_is_u64( ) const noexcept
      {
         switch( _ssss )
         {
         case setterm_u64:
            return true;
         default:
            return false;
         }
      }

      struct const_u64
      {
         const setterm* _xxxx;
         const setterm & operator * ( ) const { return * _xxxx; }
         const_u64( const setterm* _xxxx ) : _xxxx( _xxxx ) { }

         const size_t & i( ) const { return _xxxx -> repr. _fld03. heap -> scal; }
      };

      const_u64 view_u64( ) const
      {
         if constexpr( check )
         {
            if( !option_is_u64( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }

      struct mut_u64
      {
         setterm* _xxxx;
         mut_u64( setterm* _xxxx ) : _xxxx( _xxxx ) { }
         const setterm & operator * ( ) const { return * _xxxx; }

         const size_t & i( ) const { return _xxxx -> repr. _fld03. heap -> scal; }
         size_t extr_i( ) const {
            if( iswritable( _xxxx -> repr. _fld03. heap ))
               return std::move( _xxxx -> repr. _fld03. heap -> scal );
            else
               return _xxxx -> repr. _fld03. heap -> scal;
         }
         void update_i( const size_t & repl ) const
         {
            if( tvm::distinct( _xxxx -> repr. _fld03. heap -> scal, repl ))
            {
               _xxxx -> repr. _fld03. heap = takeshare( replacebywritable( _xxxx -> repr. _fld03. heap ));
               _xxxx -> repr. _fld03. heap -> scal = repl;
            }
         }
      };

      mut_u64 view_u64( )
      {
         if constexpr( check )
         {
            if( !option_is_u64( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }
      
      bool option_is_unit( ) const noexcept
      {
         switch( _ssss )
         {
         case setterm_unit:
            return true;
         default:
            return false;
         }
      }

      struct const_unit
      {
         const setterm* _xxxx;
         const setterm & operator * ( ) const { return * _xxxx; }
         const_unit( const setterm* _xxxx ) : _xxxx( _xxxx ) { }
      };

      const_unit view_unit( ) const
      {
         if constexpr( check )
         {
            if( !option_is_unit( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }

      struct mut_unit
      {
         setterm* _xxxx;
         mut_unit( setterm* _xxxx ) : _xxxx( _xxxx ) { }
         const setterm & operator * ( ) const { return * _xxxx; }
      };

      mut_unit view_unit( )
      {
         if constexpr( check )
         {
            if( !option_is_unit( ))
               throw std::invalid_argument( "wrong selector for view" );
         }
         return this;
      }
      


#line 28 "./setterm/setterms.rec"
struct equal_to
   {
      equal_to( ) noexcept = default;
      bool operator ( ) ( const setterm&, const setterm& ) const;  
   }; 
   void print( std::ostream& ) const;

   };


#line 37 "./setterm/setterms.rec"
inline bool operator== ( const setterm& s1, const setterm& s2 )
	{ auto eq = setterm::equal_to( ); return eq( s1, s2 ); }

}

#endif

