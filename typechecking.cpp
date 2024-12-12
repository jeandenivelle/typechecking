
#include <iostream>
#include <list>

#include "fieldmap.h"
#include "identifier.h"
#include "usel.h"
#include "exactident.h"

#include "data/tree.h"

#include "prop/expr.h"
#include "prop/defmap.h"

#include "flowgraph/label.h"
#include "flowgraph/point.h"
#include "flowgraph/variable.h"
#include "flowgraph/flatterm.h"
#include "flowgraph/statement.h"
#include "flowgraph/graph.h"

#include "approx/cutoff.h"

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


void mixing( flowgraph::body& bod )
{
   using namespace flowgraph;

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

   variable succ = { 's', 0 };

   auto propSucc = prop::expr( prop::tuple, 
      { prop::expr( prop::sel_const, usel( "succ" )),
        prop::expr( prop::ident, exactident( identifier( ) + "nat", 0 )) } );

   auto propEven = prop::expr( prop::ident, 
      exactident( identifier( ) + "even", 0 ));
 
   auto b1 = statement( stat_assign, p ++, alpha0, 
      flatterm( flat_boolconst, false ) );
   auto b2 = statement( stat_assign, p ++, alpha0, 
      flatterm( flat_boolconst, true ) );
 
   statement abool = statement( stat_branch, p ++, { b1, b2 } );

   {
      auto c1 = statement( stat_block, p ++, 
         { statement( stat_iffalse, p ++, alpha0 ),
           statement( stat_goto, p ++, label( "dec", 0 )) } );

      auto c2 = statement( stat_block, p ++, 
         { statement( stat_iftrue, p ++, alpha0 ),
           statement( stat_goto, p ++, label( "inc", 0 )) } );

      auto cond = statement( stat_branch, p ++, { c1, c2 } );

      auto zero = statement( stat_assign, p ++, beta1, 
                             flatterm( flat_selconst, usel( "zero" )));

      auto cmp = statement( stat_assign, p ++, beta2, 
                             flatterm( flat_eq, beta0, beta1 ));
                  
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
   }


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
}


void repeated( flowgraph::body& bod )
{
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
}


// Adjective conversion in an array:

void arrayconv( flowgraph::body& bod )
{
   flowgraph::point p;
   flowgraph::statement nop = flowgraph::statement( flowgraph::stat_nop, p ++ );

   using namespace flowgraph; 

   auto x0 = variable( 'x', 0 );
   auto i0 = variable( 'i', 0 );
   auto j0 = variable( 'j', 0 );
 
   auto a0 = variable( 'a', 0 );  

   auto b0 = variable( 'b', 0 );

   auto d0 = variable( 'd', 0 );

   auto e0 = variable( 'e', 0 );

   auto g0 = variable( 'g', 0 );

   auto propA = prop::expr( prop::ident, exactident( identifier( ) + "A", 0 ));
   auto propB = prop::expr( prop::ident, exactident( identifier( ) + "B", 0 ));
   auto propAllB = prop::expr( prop::log_forall, propB );

   {
      auto start = statement( stat_assign, p ++, i0,  
                                   flatterm( flat_u64const, (size_t) 0 ));
      start = statement( stat_block, p ++, 
         { start, statement( stat_goto, p ++, label( "cond", 0 )) } );

      bod. code. insert( { flowgraph::label( "start", 0 ), start } );
   }
 
   {
      auto p1 = statement( stat_assign, p ++, a0, flatterm( flat_len, x0 ));
      auto p2 = statement( stat_assign, p ++, b0, flatterm( flat_lt, i0, a0 ));
      auto p3 = statement( stat_assign, p ++, g0, flatterm( flat_not, b0 ));
   
      auto yes = statement( stat_iftrue, p ++, g0 );
      auto no = statement( stat_iffalse, p ++, g0 );

      auto cond = statement( stat_branch, p ++, 
         { 
            statement( stat_block, p ++, 
               { statement( stat_iftrue, p ++, g0 ), 
                 statement( stat_goto, p ++, label( "body", 0 )) } ),
            statement( stat_block, p ++, 
               { statement( stat_iffalse, p ++, g0 ), 
                 statement( stat_goto, p ++, label( "exit", 0 )) } ) 
         } );

      cond = statement( stat_block, p ++,
         { p1, p2, p3, cond } );

      bod. code. insert( { flowgraph::label( "cond", 0 ), cond } );
   }

   {
      auto p1 = statement( stat_assign, p ++, d0, 
                           flatterm( flat_field, x0, 0, { i0 } ));
      
      auto call = statement( stat_assign, p ++, e0, flatterm( flat_call,
         exactident( identifier( ) + "F", 0 ), { d0 } ));

      call = statement( stat_resolve, p ++, 
         { { precond( { { d0, propA } } ), call }} );

      auto p2 = statement( stat_update, p ++, x0, 0, { i0 }, e0 );
      auto p3 = statement( stat_assign, p ++, j0, 
                              flatterm( flat_u64const, (size_t) 1 ));
      auto p4 = statement( stat_assign, p ++, i0, flatterm( flat_add, i0, j0 ));
      auto p5 = statement( stat_goto, p ++, label( "cond", 0 ));

      bod. code.insert( { flowgraph::label( "body", 0 ), 
         statement( stat_block, p ++, { p1, call, p2, p3, p4, p5 } ) } );
   }

   {
      auto ret = statement( stat_return, p ++, x0 );

      ret = statement( stat_resolve, p ++, 
         { { precond( {{ x0, propAllB }} ), ret } } );

      bod. code. insert( { flowgraph::label( "exit", 0 ), ret } );
   }
}


// Add natural numbers, even and odd numbers:

void add_nat( prop::defmap& prp, fieldmap& flds )
{
   std::cout << "Constructing Natural Numbers:\n";

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
}


void add_fol( prop::defmap& prp, fieldmap& flds )
{
   std::cout << "\n";
   std::cout << "Constructing definition of simply typed first-order logic:\n\n";
      // The definition was copied from an unfinished (hardly started)
      // implementation of geo.
 
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


#if 0

void modaladjectives( adj::map& sys )
{
#if 0
   std::cout << "Adding adjectives on modal formula:\n";

   using namespace ast;

   auto tr = tree( new expr( op_or( ),
         { tree( new constant( selector( "?true" ))),
           tree( new constant( selector( "?false" ))) } ));

   auto nullaryF = exactname( "nullaryF" );
   sys. insert( { nullaryF, 
                  adj::def( decldef( -1, 0, vis_global ),
                            new type::fullident( "modal" ), tr ) } );
#endif 
}

#endif

int main( int argc, char* argv [] )
{

   flowgraph::body bod;

   // test_scalar_list( );

   // std::vector< parsing::error > errors; 

#if 0
   parsing::parser prs( simpmap, compmap, adjmap, funcmap, 
                        errors, toplevelspace, filespace, tok ); 
 
   prs. debug = 3; 
   std::cout << "not even started\n";

   parsing::symbol sym = prs. parse( parsing::sym_File ); 
   std::cout << "parser returned " << sym << "\n";

   for( const auto& e : errors )
      std::cout << e << "\n";

   if( filespace ) 
      std::cout << "filespace = " << filespace. value( ) << "\n";
   else
      std::cout << "no filespace was set\n";

   tvm::printselectorenum( std::cout );

   return 0;
#endif
 
   fieldmap flds;
   prop::defmap prp;

   add_nat( prp, flds );
   add_fol( prp, flds );

   std::cout << prp << "\n";
   std::cout << flds << "\n";

   // mixing( bod );
   // repeated( bod );
   arrayconv( bod );
   std::cout << bod << "\n";

   return 0;

   // adj::overloadmap adjover;

   // natural( types, adjmap, fields, adjover );
   // firstorder( compmap, adjmap, fields, adjover );

   // std::cout << simpmap << "\n";
   // std::cout << compmap << "\n";
   // std::cout << adjmap << "\n";
   // std::cout << fields << "\n";
   //  std::cout << adjover << "\n";

#if 0
   types. insert( { "modal", modal( ) } ); 
   std::cout << types << "\n";
   return 0;

   auto nnf = exactname( "nnf" );

   adjmap. insert( { nnf, adj::def( new type::fullident( "fol" ), tr ) } );
#endif

   // modaladjectives( adjmap );

   return 0;	
}

