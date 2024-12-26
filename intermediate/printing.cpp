
#include "flatterm.h"
#include "statement.h"

void intermediate::flatterm::print( std::ostream& out ) const
{
   switch( sel( ))
   {
   case flat_var:
      {
         auto v = view_var( );
         out << v. v( );
         return;
      }
   case flat_unitconst:
      {
         out << "trivial"; 
         return;
      } 
   case flat_boolconst:
      {
         auto b = view_boolconst( );
         out << ( b. b( ) ? "true" : "false" );
         return;
      }
   case flat_charconst:
      {
         auto c = view_charconst( );
         out << '\'';
         if( isprint( c. c( )))
            out << c. c( );
         else
         {
            out << '{'; 
            util::hexprint( out, c.c( ));
            out << '}';
         }
         out << '\'';
         return; 
      }
   case flat_selconst:
      {
         auto u = view_selconst( );
         out << '?' << u. s( );
         return; 
      }
   case flat_u64const:
      {
         auto u = view_u64const( );
         out << u. u( );
         return;
      }
   case flat_doubleconst:
      {
         auto d = view_doubleconst( );
         out << d. d( );
         return;
      }
   case flat_some_bool:
      {
         out << "some bool";
         return;
      }
   case flat_some_char:
      {
         out << "some char";
         return; 
      }
   case flat_some_u64:
      {
         out << "some u64";
         return;
      }
   case flat_some_double:
      {
         out << "some double";
         return;
      } 
   case flat_yield:
      {
         auto y = view_yield( );
         out << "yield " << y. v( );
         return; 
      }
   case flat_len:
   case flat_not:
   case flat_neg:
      {
         auto un = view_unary( );
         switch( sel( ))
         {
         case flat_len:
            out << "len"; break;
         case flat_not:
            out << "not"; break;
         case flat_neg:
            out << "neg"; break;
         }
         out << "( " << un. v( ) << " )";
         return;
      }
   case flat_eq:
   case flat_ne:
   case flat_lt:
   case flat_gt:
   case flat_le:
   case flat_ge:
   case flat_add:
   case flat_sub:
      {
         auto b = view_binary( );
         switch( sel( ))
         {
         case flat_eq: out << "eq"; break;
         case flat_ne: out << "ne"; break; 
         case flat_lt: out << "lt"; break;
         case flat_gt: out << "gt"; break; 
         case flat_le: out << "le"; break;
         case flat_ge: out << "ge"; break;
         case flat_add: out << "add"; break;
         case flat_sub: out << "sub"; break;
         default: out << "???"; break; 
         } 
         out << "( " << b. v1( ) << ", " << b. v2( ) << " )";
         return;
      }
   case flat_field:
      {
         auto fld = view_field( );
         out << fld. v( ) << '.' << fld. fname( );
         if( fld. ind( ). has_value( ))
            out << "[ " << fld. ind( ). value( ) << " ]";
         return; 
      }
#if 0
   case flat_scal:
      {
         out << "(";
         auto scal = view_scal( );
         for( size_t i = 0; i != scal. size( ); ++ i )
         {
            if( i != 0 )
               out << ", ";
            else
               out << " ";
            out << scal. v(i);
         }
         out << " )";
         return;
      } 
#endif
   case flat_call:
      {
         auto c = view_call( );
         out << c. func( ) << '(';
         for( size_t i = 0; i != c. size( ); ++i )
         {
            if(i) 
               out << ", ";
            else
               out << ' ';
            out << c. v(i);
         }
         out << " )";
         return; 
      }

   }

   std::cout << "for " << sel( ) << "\n";
   throw std::runtime_error( "flowgraph::flatterm::print not implemented" );
}


void 
intermediate::statement::print( indentation ind, std::ostream& out ) const
{
   out << ind << pnt( ) << ": ";
   switch( sel( ))
   {
   case stat_nop:
      out << "nop\n"; return;

   case stat_assign:
      {
         auto a = view_assign( );
         out << a. v( ) << " <-- " << a. val( ) << '\n';
         return;
      }

// 		case stmnt_char_assgn:
// 		{
// 			const auto& assgn = view_char_assgn( );
// 			out << assgn. v( ) << " <- " << assgn. c( );
// 		}
// 		break;

// 		case stmnt_var_assgn:
// 		{
// 			const auto& assgn = view_var_assgn( );
// 			out << assgn. v( ) << " <- " << assgn. w( );
// 		}
// 		break;

// 		case stmnt_unknown_assgn:
// 		{
// 			const auto& assgn = view_unknown_assgn( );
// 			out << assgn. v( ) << " <- " << assgn. t( );
// 		}
// 		break;

// 		case stmnt_not:
// 		{
// 			const auto& unary = view_unary( );
// 			out << unary. v( ) << " <- " << sel( ) << "( " << unary. w( ) << " )";
// 		}
// 		break;

//		case stmnt_push:
//		{
//			const auto& push = view_push( );
//			out << push. v( ) << ". push( ";
//			for( size_t i = 0; i < push. size( ); ++i )
//			{
//				if( i ) out << ", ";
//				out << push. w( i );
//			}
//			out << " )"; 
//		}
//		break;

//		case stmnt_pop:
//		out << view_pop( ). v( ) << ". pop( )";
//		break;

//		case stmnt_strct:
//		{
//			const auto& strct = view_strct( );
//			out << strct. v( ) << " <= ( ";
//			for( size_t i = 0; i < strct. size( ); ++i )
//			{
//				if( i ) out << ", ";
//				out << strct. w( i );
//			}
//			out << ", " << strct. k( ) << " )";
//		}
//		break;

//		case stmnt_fslct:
//		{
//			const auto& fslct = view_fslct( );
//			out << fslct. v( ) << " <= " << fslct. w( ) << ". " << fslct. f( );
//		}
//		break;
		
      case stat_istrue:
      case stat_isfalse: 
         {
            auto cond = view_is( );
            switch( sel( )) 
            {
            case stat_istrue:
               out << "istrue "; break;
            case stat_isfalse:
               out << "isfalse "; break;
            default:
               out << "???"; break;
            }
            out << cond. v( ) << '\n';
            return;
         } 

      case stat_resolve:
         {
            auto res = view_resolve( );
            out << "resolve\n";
            for( size_t i = 0; i != res. size( ); ++ i )
               res. stat(i). print( ind + 3, out ); 
            return;
         }
 
      case stat_update:
         {
            auto up = view_update( ); 
            out << "update " << up. v( ) << "." << up. fname( ); 
            if( up. ind( ). has_value( ))
               out << "[ " << up. ind( ). value( ) << " ]";
            out << " := " << up. val( ) << "\n";
            return;
         } 

      case stat_return:
         {
            out << "return " << view_return( ). v( ) << '\n';
            return;
         }

//		case stmnt_abort:
//		case stmnt_error:
//		out << sel( ) << " \"" << view_intrpt( ). mssg( ) << '"';
//		break;

   case stat_block:
   case stat_repeat:
   case stat_branch:
      {
         if( sel( ) == stat_block ) out << "block\n";
         if( sel( ) == stat_repeat ) out << "repeat\n";
         if( sel( ) == stat_branch ) out << "branch\n";

         auto c = view_compound( );
         for( size_t i = 0; i != c. size( ); ++ i )
            c. stat(i). print( ind + 3, out );
          
         return;
      }

   case stat_comment:
      {
         out << "// " << view_comment( ). blah( ) << "\n";
         return;
      }

   }
   out << sel( ) << "\n";
   out << "dont know how to print\n";
}

