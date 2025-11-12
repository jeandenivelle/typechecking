#include <list>
#include <vector>

#include "tests.h"

#include "data/tree.h"

#include "atm/state.h"
#include "atm/stateset.h"
#include "atm/statemap.h"
#include "atm/simple.h"

#include "simulation.h"
#if 0
void test_scalar_list( )
{
   std::vector< std::string > s = 
   { "aaaaaaaaaaaaaaaaaaaaaaaaa", "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", "ccccccccccccccccccccccccccccccccccccccccccc", "dddddddd", "eeeeee" };
   auto p = tvm::constr_scalar_list< std::list< std::string >, std::string > 
               ( std::list< std::string > ( { "a", "b", "c" } ), s. begin( ), s. end( )); 
   p = takeshare(p);
   auto p1 = takeshare(p);

   p1 = takeshare( replacebywritable( p1 ));
   p = takeshare( replacebywritablewithcap( p, p -> size( ) + 2 )); 
   for( auto it = p -> begin( ); it != p -> end( ); )
   {
      if( p -> at(it). size( ) % 2 == 0 )
         it = erase( p, it );
      else
         it = p -> next( it );
   }
   show( p, std::cout );
   auto ind = p -> begin( );
   std::cout << "inserting at " << p -> at( ind ) << "\n";
   ind = insert( p, ind, "prof" ); 
   ind = insert( p, ind, "hans" ); 
   ind = insert( p, ind, "de" );
   ind = insert( p, ind, "nivelle" );
   p = takeshare( replacebywritablewithcap( p, 200 ));
   ind = insert( p, ind, "kireeva" );
   ind = p -> next( ind );
   std::string str = "yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy";
   insert( p, ind, str );
   ind = insert( p, ind, "abcdefghijklm" );
   std::cout << "moved out " << str << "\n";
   show( p, std::cout );
   checkinvariant(p);
   dropshare(p);
   dropshare(p1);
}
#endif

#if 0
intermediate::function tests::mixing( )
{
   using namespace intermediate;

   point p;
   statement nop = statement( stat_nop, p ++ );

   // Create a few variables:

   variable m0 = { 'm', 0 };
   variable m1 = m0. succ( );
   variable m2 = m1. succ( );

   variable alpha0 = { 'a', 0 }; 
   variable alpha1 = alpha0. succ( );
   variable alpha2 = alpha1. succ( ); 

   variable beta0 = { 'b', 0 };
   variable beta1 = beta0. succ( );
   variable beta2 = beta1. succ( );

   variable gamma0 = { 'g', 0 };
   variable gamma1 = gamma0. succ( );

   variable succ = { 's', 0 };

   auto propSucc = prop::expr( prop::tuple, 
      { prop::expr( prop::sel_const, usel( "succ" )),
        prop::expr( prop::ident, exactident( identifier( ) + "nat", 0 )) } );

   auto propEven = prop::expr( prop::ident, 
      exactident( identifier( ) + "even", 0 ));

   std::vector< statement > res;
      // It will be collected into a single block at the end. 

   std::vector< statement > rep;
   rep. push_back( statement( stat_assign, p ++, alpha0, 
                             flatterm( flat_some_bool )));

   rep. push_back( statement( stat_nop, p ++ ));
   rep. push_back( statement( stat_assign, p ++, beta0, 
                    flatterm( flat_field, m0, exactident( identifier( ) + "op", 0 ), { } )));

   rep. push_back( statement( stat_assign, p ++, gamma0, 
                             flatterm( flat_selconst, usel( "zero" ))));

   rep. push_back( statement( stat_assign, p ++, gamma1, 
                             flatterm( flat_eq, beta0, gamma0 )));

   std::vector< statement > bl1;
   bl1. push_back( statement( stat_istrue, p ++, alpha0 ));
   bl1. push_back( statement( stat_istrue, p ++, gamma1 ));

#if 0

   {
#if 0
      auto c1 = statement( stat_block, p ++, 
         { statement( stat_iffalse, p ++, alpha0 ),
           statement( stat_goto, p ++, label( "dec", 0 )) } );

      auto c2 = statement( stat_block, p ++, 
         { statement( stat_iftrue, p ++, alpha0 ),
           statement( stat_goto, p ++, label( "inc", 0 )) } );

      auto cond = statement( stat_branch, p ++, { c1, c2 } );


      c1 = statement( stat_block, p ++,
         { statement( stat_iftrue, p ++, beta2 ),
           statement( stat_goto, p ++, label( "inc", 0 )) } );

      c2 = statement( stat_block, p ++,
         { statement( stat_iffalse, p ++, beta2 ), cond } );

      cond = statement( stat_branch, p ++, { c1, c2 } );
 
      auto op = statement( stat_assign, p ++, beta0, flatterm( flat_field, m0, 0, { } ));

      auto start = statement( stat_block, p ++,
         { nop, abool, nop, op, zero, cmp, cond } );

      auto ret = statement( stat_return, p ++,  m0 );

      ret = statement( stat_resolve, p ++, { { precond( {{ m0, propEven }} ), ret } } );

      start = statement( stat_branch, p ++, { ret, start } );

      bod. code. insert( { label( "start", 0 ), start } );    
#endif
   }

#if 0
   // The decrement loop:

   {
      auto dec = statement( stat_assign, p ++, m0,
      flatterm( flat_field, m1, 1, {} ));

      auto req = statement( stat_resolve, p ++, { { precond( {{m1,propSucc}} ), dec } } );
      dec = statement( stat_assign, p ++, m1, 
                       flatterm( flat_field, m0, 1, {} ));

      dec = statement( stat_block, p ++, { dec, req } );
      req = statement( stat_resolve, p ++, 
                 { { precond( { { m0, propSucc }} ), dec } } ); 

      auto restart = statement( stat_goto, p ++, label( "start", 0 ));

      dec = statement( stat_block, p ++, { req, restart } );
      bod. code. insert( { label( "dec", 0 ), dec } );
   }
 
   // The increment loop:

   {
      auto inc1 = statement( stat_assign, p ++, succ,
         flatterm( flat_selconst, usel( "succ" )));

      auto inc2 = statement( stat_assign, p ++, m1,
         flatterm( flat_scal, { succ, m0 } ));
 
      auto inc3 = statement( stat_assign, p ++, m0,
         flatterm( flat_scal, { succ, m1 } )); 

      auto restart = statement( stat_goto, p ++, label( "start", 0 ));

      auto inc = statement( stat_block, p ++, { inc1, inc2, inc3, restart } );

      bod. code. insert( { flowgraph::label( "inc", 0 ), inc } );
   }
#endif
#endif
   res. push_back( statement( stat_repeat, p ++, rep. begin( ), rep. end( )));

    return function( statement( stat_block, p ++, res.begin( ), res. end( )),
                     prop::expr( prop::type_unit ));

}
#endif

#if 0
intermediate::function tests::repeated( )
{
#if 0
   flowgraph::point p;
   flowgraph::statement nop = flowgraph::statement( flowgraph::stat_nop, p ++ );

   using namespace flowgraph;

   auto x1 = variable( 'x', 1 );
   auto x2 = variable( 'x', 2 );

   auto a1 = variable( 'a', 1 );
   auto a2 = variable( 'a', 2 );
   auto a3 = variable( 'a', 3 );
   auto a4 = variable( 'a', 4 );

   auto b1 = variable( 'b', 1 );
   auto b2 = variable( 'b', 2 );
   auto b3 = variable( 'c', 3 );

   auto s1 = statement( stat_assign, p++, a1, flatterm( flat_field, x1, 0, { } ));
   auto s2 = statement( stat_assign, p++, a2, flatterm( flat_field, x2, 0, { } ));

   auto eq = statement( stat_assign, p++, b1, flatterm( flat_eq, a1, a2 ));

   auto cnd1 = statement( stat_iftrue, p ++, b1 );

   auto s3 = statement( stat_assign, p++, a3, flatterm( flat_field, x1, 0, { } ));

   auto s4 = statement( stat_assign, p++, b2, flatterm( flat_selconst, usel( "zero" )));
   auto s5 = statement( stat_assign, p++, b3, flatterm( flat_eq, a3, b2 ));

   auto cnd2 = statement( stat_iftrue, p++, b3 );

   auto s6 = statement( stat_assign, p++, a4, flatterm( flat_field, x2, 0, { } ));

   auto res = statement( stat_resolve, p ++, 
       { { precond( {{ a4, prop::expr( prop::sel_const, usel( "zero" )) }} ), 
              statement( stat_return, p ++, a4 ) }} );

   auto fin = statement( stat_block, p ++, { s1, s2, eq, cnd1, s3, s4, s5, cnd2, s6, res } ); 

   std::cout << fin << "\n";
#endif

}
#endif

#if 0
// Adjective conversion in an array:
intermediate::function tests::arrayconv( )
{
   using namespace intermediate; 

   point p;

   auto x0 = variable( 'x', 0 );
   auto i0 = variable( 'i', 0 );
   auto j0 = variable( 'j', 0 );
 
   auto a0 = variable( 'a', 0 );  
   auto b0 = variable( 'b', 0 );
   auto g0 = variable( 'g', 0 );

   auto d0 = variable( 'd', 0 );
   auto e0 = variable( 'e', 0 );

   auto propA = prop::expr( prop::ident, exactident( identifier( ) + "A", 0 ));
   auto propB = prop::expr( prop::ident, exactident( identifier( ) + "B", 0 ));
   auto propAllA = prop::expr( prop::log_forall, propA );
   auto propAllB = prop::expr( prop::log_forall, propB );

   std::vector< statement > res;
      // It will be collected into a single block at the end. 

   res. push_back( statement( stat_assign, p ++, i0,  
                              flatterm( flat_u64const, (size_t) 0 )));
 
   res. push_back( statement( stat_assign, p ++, a0, flatterm( flat_len, x0 )));
   res. push_back( statement( stat_assign, p ++, b0, flatterm( flat_lt, i0, a0 )));
   res. push_back( statement( stat_assign, p ++, g0, flatterm( flat_not, b0 )));

   std::vector< statement > rep;
      // Will be a repeat.

   rep. push_back( statement( stat_isfalse, p ++, g0 ));
 
   rep. push_back( statement( stat_resolve, p ++, { statement( stat_assign, p ++, d0, 
                              flatterm( flat_field, x0, 
                                  exactident( identifier( ) + "f", 0 ), i0 )) } ));

   {
      auto call = statement( stat_assign, p ++, e0, flatterm( flat_call,
                             exactident( identifier( ) + "F", 0 ), { d0 } )); 

      std::vector< variable > var = { d0 };
      std::vector< prop::expr > prec = { propA };

      rep. push_back( statement( stat_resolve, p ++, { call } ));
      
      rep. push_back( statement( stat_update, p ++, x0, 
                                 exactident( identifier() + "f", 0 ),
                                 { i0 }, e0 ));

      rep. push_back( statement( stat_assign, p ++, j0, 
                              flatterm( flat_u64const, (size_t) 1 )));
      rep. push_back( statement( stat_assign, p ++, i0, flatterm( flat_add, i0, j0 )));
      rep. push_back( statement( stat_comment, p ++, "prepare for the next test" ));

      rep. push_back( statement( stat_assign, p ++, a0, flatterm( flat_len, x0 )));
      rep. push_back( statement( stat_assign, p ++, b0, flatterm( flat_lt, i0, a0 )));
      rep. push_back( statement( stat_assign, p ++, g0, flatterm( flat_not, b0 )));
   }

   res. push_back( statement( stat_repeat, p ++, rep. begin( ), rep. end( )));
   res. push_back( statement( stat_istrue, p ++, g0 ));  
   res. push_back( statement( stat_resolve, p ++, { statement( stat_return, p ++, x0 ) } ));

   return function( statement( stat_block, p ++, res.begin( ), res. end( )),
                    propAllB );
}
#endif

#if 1
// Add natural numbers, even and odd numbers:
void tests::add_nat()
{
   std::cout << "Constructing An Automaton for Natural Numbers:\n";

   auto nat = atm::simple( atm::state( ));

   atm::statemap prop;
   prop[ "nat" ] = nat. newstate( );
   prop[ "even" ] = nat. newstate( );
   prop[ "odd" ] = nat. newstate( );
   prop[ "?zero" ] = nat. newstate( );
   prop[ "?succ" ] = nat. newstate( );

   nat. delta_bool = { nat. collapsed };

   std::cout << prop << "\n";
 
   nat. delta_usel. assign( usel( "zero" ), prop. at( "?zero" ));
   nat. delta_usel. assign( usel( "succ" ), prop. at( "?succ" ));

   nat. addtuple( { prop. at( "?zero" ) }, prop. at( "even" ));
   nat. addtuple( { prop. at( "?succ" ), prop. at( "even" ) }, prop. at("odd" ));
   nat. addtuple( { prop. at( "?succ" ), prop. at( "odd" ) }, prop. at("even" )) ; 
   std::cout << nat << "\n";

   std::cout << "Simulating The Automaton of Natural Numbers\n";
   
   std::vector< data::tree > ds;

   auto usel_zero = data::tree( data::tree_usel, usel( "zero" ) );
   ds. push_back( usel_zero );
 
   auto usel_succ = data::tree( data::tree_usel, usel( "succ" ) );
   ds. push_back( usel_succ );
   
   auto data_zero = data::tree( data::tree_tuple, { usel_zero } );
   ds. push_back( data_zero );

   ds. push_back(
      data::tree( data::tree_tuple, 
         { usel_succ, data_zero } ));

   ds. push_back( 
      data::tree( data::tree_tuple, 
         { usel_succ, ds. back() } ));

   for( auto d : ds ) {
      std::cout << d << " ==> { "; 
      for( auto s : simulate( nat, d ) ) {
         std::cout << s << ", "; 
      }
      std::cout << " }\n";
   }

#if 0
   // This is code that uses property expressions.
   // I keep them for the moment.

   auto zero = prop::expr( prop::sel_const, usel( "zero" ));
   zero = prop::expr( prop::tuple, { zero } );
 
   auto succ = prop::expr( prop::sel_const, usel( "succ" ));
   succ = prop::expr( prop::tuple, 
      { succ, prop::expr( prop::ident, { identifier( ) + "nat", 0 } ) } );

   auto nat = exactident( identifier( ) + "nat", 0 );
   prp. insert( nat, prop::expr( prop::log_or, { zero, succ } ));

   succ = prop::expr( prop::sel_const, usel( "succ" ));
   succ = prop::expr( prop::tuple, { succ, prop::expr( prop::ident, { identifier( ) + "odd", 0 } ) } );
   auto even = exactident( identifier( ) + "even", 0 );
   prp. insert( even, prop::expr( prop::log_or, { zero, succ } ));
  
   succ = prop::expr( prop::sel_const, usel( "succ" )); 
   succ = prop::expr( prop::tuple, { succ, prop::expr( prop::ident, { identifier( ) + "even", 0 } ) } );
   auto odd = exactident( identifier( ) + "odd", 0 );
   prp. insert( odd, succ );

   flds. insert( exactident( identifier( ) + "op", 0 ), 
                     fielddef( fld_scalar, 
                        prop::expr( prop::ident, { identifier( ) + "nat", 0 } ), 0 ));
#endif
}
#endif

#if 0
void tests::add_fol( prop::defmap& prp, fieldmap& flds )
{
   std::cout << "\n";
   std::cout << "Constructing definition of simply typed first-order logic:\n\n";
      // The definition was copied from an unfinished (hardly started)
      // implementation of geo.

   auto nat = atm::simple( atm::state( ));

   atm::statemap prop;
   prop[ "nat" ] = nat. newstate( );
   prop[ "even" ] = nat. newstate( );
   prop[ "odd" ] = nat. newstate( );
   prop[ "?zero" ] = nat. newstate( );
   prop[ "?succ" ] = nat. newstate( );

   nat. delta_bool = { nat. collapsed };
 
   auto ident = exactident( identifier( ) + "ident", 0 );

   prp. insert( ident, prop::expr( prop::tuple, { prop::expr( prop::log_forall, 
                                                  prop::expr( prop::type_char )) } ));

   flds. insert( exactident( identifier( ) + "c", 0 ),
      fielddef( fld_vector, 
         prop::expr( prop::ident, ident ), 0 ));   

   //// term:

   auto term = exactident( identifier( ) + "term", 0 );

   {
      auto tm = prop::expr( prop::tuple,
         { prop::expr( prop::ident, ident ),
           prop::expr( prop::log_forall, prop::expr( prop::ident, ident ))
         } );

      prp. insert( term, tm );
   }

   flds. insert( exactident( identifier( ) + "func", 0 ),
      fielddef( fld_scalar,
         prop::expr( prop::ident, term ), 0 ));  

   flds. insert( exactident( identifier( ) + "args", 0 ),
      fielddef( fld_vector,
         prop::expr( prop::ident, term ), 1 ));  

   //// sort:

   auto sort = exactident( identifier( ) + "sort", 0 );

   {
      auto prim = prop::expr( prop::log_or, 
               { prop::expr( prop::sel_const, usel( "truthval" )),
                 prop::expr( prop::sel_const, usel( "obj" )),
                 prop::expr( prop::sel_const, usel( "set" )) } );

      prim = prop::expr( prop::tuple, { prim } );

      auto named = prop::expr( prop::tuple,  
         { prop::expr( prop::sel_const, usel( "named" )),
           prop::expr( prop::ident, ident ) } );

      prp. insert( sort, prop::expr( prop::log_or, { prim, named } )); 
   };
  
   // op gets index 1, because 'op' of nat has index 0.
 
   flds. insert( exactident( identifier( ) + "op", 1 ),
      fielddef( fld_scalar,
         prop::expr( prop::ident, sort ), 0 ));

   flds. insert( exactident( identifier( ) + "name", 0 ),
      fielddef( fld_scalar,
         prop::expr( prop::tuple,
            { prop::expr( prop::sel_const, usel( "named" )),
              prop::expr( prop::ident, ident )
            }), 1 ));

   /// fol :
 
   auto fol = exactident( identifier( ) + "fol", 0 );

   auto atom = prop::expr( prop::tuple,
      { prop::expr( prop::sel_const, usel( "atom" )),
        prop::expr( prop::ident, ident ), 
        prop::expr( prop::log_forall, prop::expr( prop::ident, term )) 
      } );

   auto negated = prop::expr( prop::tuple,
      { prop::expr( prop::sel_const, usel( "not" )),
        prop::expr( prop::ident, fol )
      } );

   auto eq = prop::expr( prop::tuple,
      { prop::expr( prop::sel_const, usel( "equals" )),
        prop::expr( prop::ident, fol ),
        prop::expr( prop::ident, fol )
      } );

   auto bin = prop::expr( prop::tuple,
      { prop::expr( prop::log_or, { prop::expr( prop::sel_const, usel( "implies" )),
                                    prop::expr( prop::sel_const, usel( "equiv" )) } ),
        prop::expr( prop::ident, fol ),
        prop::expr( prop::ident, fol ) 
      } );

   auto nary = prop::expr( prop::tuple,
      { prop::expr( prop::log_or, { prop::expr( prop::sel_const, usel( "and" )),
                                    prop::expr( prop::sel_const, usel( "or" )) } ),
        prop::expr( prop::log_forall, prop::expr( prop::ident, fol )) 
      } );

   auto quant = prop::expr( prop::tuple,
      { prop::expr( prop::log_or, { prop::expr( prop::sel_const, usel( "forall" )),
                                    prop::expr( prop::sel_const, usel( "exists" )) } ), 
        prop::expr( prop::log_forall, prop::expr( prop::ident, ident )),
        prop::expr( prop::log_forall, prop::expr( prop::ident, sort )),
      } );

   prp. insert( fol, prop::expr( prop::log_or, { atom, eq, negated, bin, nary, quant } ));

   flds. insert( exactident( identifier( ) + "op", 2 ),
      fielddef( fld_scalar,
         prop::expr( prop::ident, fol ), 0 ));

   flds. insert( exactident( identifier( ) + "sub", 0 ),
      fielddef( fld_scalar,
         prop::expr( prop::tuple,
            { prop::expr( prop::sel_const, usel( "not" )),
              prop::expr( prop::ident, fol )
            }), 1 ));

   flds. insert( exactident( identifier( ) + "sub1", 0 ),
      fielddef( fld_scalar,
         prop::expr( prop::tuple,
            { prop::expr( prop::sel_const, usel( "equals" )),
              prop::expr( prop::ident, term ),
              prop::expr( prop::ident, term )
            }), 1 ));

   flds. insert( exactident( identifier( ) + "sub2", 0 ),
      fielddef( fld_scalar,
         prop::expr( prop::tuple,
            { prop::expr( prop::sel_const, usel( "equals" )),
              prop::expr( prop::ident, term ),
              prop::expr( prop::ident, term )
            }), 2 ));

   // sub1,sub2 of binary logical operator:

   flds. insert( exactident( identifier( ) + "sub1", 1 ),
      fielddef( fld_scalar,
         prop::expr( prop::tuple,
            { prop::expr( prop::log_or,
                 { prop::expr( prop::sel_const, usel( "implies" )),
                   prop::expr( prop::sel_const, usel( "equiv" ))
                 }
              ),
              prop::expr( prop::ident, fol ),
              prop::expr( prop::ident, fol )
            }), 1 ));

   flds. insert( exactident( identifier( ) + "sub2", 1 ),
      fielddef( fld_scalar,
         prop::expr( prop::tuple,
            { prop::expr( prop::log_or,
                 { prop::expr( prop::sel_const, usel( "implies" )),
                   prop::expr( prop::sel_const, usel( "equiv" ))
                 }
              ),
              prop::expr( prop::ident, fol ),
              prop::expr( prop::ident, fol )
            }), 2 ));

   // sub of n-ary logical operator:

   flds. insert( exactident( identifier( ) + "sub", 1 ),
      fielddef( fld_vector,
         prop::expr( prop::tuple,
            { prop::expr( prop::log_or,
                 { prop::expr( prop::sel_const, usel( "and" )),
                   prop::expr( prop::sel_const, usel( "or" ))
                 }
              ),
              prop::expr( prop::log_forall, prop::expr( prop::ident, fol )) 
            }), 1 ));

   // body of quantifier:

   flds. insert( exactident( identifier( ) + "body", 1 ),
      fielddef( fld_scalar,
         prop::expr( prop::tuple,
            { prop::expr( prop::log_or,
                 { prop::expr( prop::sel_const, usel( "forall" )),
                   prop::expr( prop::sel_const, usel( "exists" ))
                 }
              ),
              prop::expr( prop::expr( prop::ident, fol )),
              prop::expr( prop::log_forall, prop::expr( prop::ident, ident )),
              prop::expr( prop::log_forall, prop::expr( prop::ident, sort )) 
            }), 1 ));

   // Preferred name of quantified variable: 

   flds. insert( exactident( identifier( ) + "pref", 1 ),
      fielddef( fld_vector,
         prop::expr( prop::tuple,
            { prop::expr( prop::log_or,
                 { prop::expr( prop::sel_const, usel( "forall" )),
                   prop::expr( prop::sel_const, usel( "exists" ))
                 }
              ),
              prop::expr( prop::expr( prop::ident, fol )),
              prop::expr( prop::log_forall, prop::expr( prop::ident, ident )),
              prop::expr( prop::log_forall, prop::expr( prop::ident, sort ))
            }), 2 ));

   // Sort of quantified variable: 

   flds. insert( exactident( identifier( ) + "srt", 1 ),
      fielddef( fld_vector,
         prop::expr( prop::tuple,
            { prop::expr( prop::log_or,
                 { prop::expr( prop::sel_const, usel( "forall" )),
                   prop::expr( prop::sel_const, usel( "exists" ))
                 }
              ),
              prop::expr( prop::expr( prop::ident, fol )),
              prop::expr( prop::log_forall, prop::expr( prop::ident, ident )),
              prop::expr( prop::log_forall, prop::expr( prop::ident, sort ))
            }), 3 ));

}
#endif


atm::simple tests::prop( )
{
   using namespace atm;

   auto prop = simple( state( ));

   // define transition for characters:

   state q_char = prop. newstate( );
   prop. delta_char. bot = prop. collapsed;

   prop. delta_char. append( '0', q_char, q_char );
   prop. delta_char. append( '9', q_char, prop. collapsed );

   prop. delta_char. append( 'A', q_char, q_char );
   prop. delta_char. append( 'Z', q_char, prop. collapsed );

   prop. delta_char. append( '_', q_char, prop. collapsed );

   prop. delta_char. append( 'a', q_char, q_char );
   prop. delta_char. append( 'z', q_char, prop. collapsed );

   state q_all_char = prop. newstate( );
   prop. addforall( q_char, q_all_char );

   auto q_atom = prop. newstate( );
   auto q_neg = prop. newstate( );
   auto q_implies = prop. newstate( );
   auto q_equiv = prop. newstate( );
   auto q_or = prop. newstate( );
   auto q_and = prop. newstate( );

   auto q_prop = prop. newstate( );

   prop. delta_usel. def = prop. collapsed;
   prop. delta_usel. assign( usel( "atom" ), q_atom );
   prop. delta_usel. assign( usel( "neg" ), q_neg );
   prop. delta_usel. assign( usel( "implies" ), q_implies );
   prop. delta_usel. assign( usel( "equiv" ), q_equiv );
   prop. delta_usel. assign( usel( "or" ), q_or );
   prop. delta_usel. assign( usel( "and" ), q_and );

   prop. addtuple( { q_atom, q_all_char }, q_prop );
   prop. addtuple( { q_neg, q_prop }, q_prop );

   prop. addtuple( { q_implies, q_prop, q_prop }, q_prop );
   prop. addtuple( { q_equiv, q_prop, q_prop }, q_prop );

   // A multiset of props:

   auto q_all_prop = prop. newstate( );
   prop. addforall( q_prop, q_all_prop );

   prop. addtuple( { q_or, q_all_prop }, q_all_prop );
   prop. addtuple( { q_and, q_all_prop }, q_all_prop );

   std::cout << prop << "\n";
   return prop; 
}

