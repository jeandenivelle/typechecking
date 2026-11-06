

#include "tests.h"
#include "data/constructors.h"

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

   auto ffunc = finfunc< usel, bool, usel::hash, usel::equal_to > 
      ( false, {{ usel( "succ" ), true }} );

   
#if 0
   auto propSucc = regexp::expr( regexp::tuple, 
      { regexp::expr( regexp::flt_sel, ffunc ) 
        regexp::expr( regexp::ref_ident, exactident( identifier( ) + "nat", 0 )) } );
#endif

   auto propEven = regexp::expr( regexp::ref_ident, identifier( ) + "even" );

   std::vector< statement > res;
      // It will be collected into a single block at the end. 

   std::vector< statement > rep;
   rep. push_back( statement( stat_assign, p ++, alpha0, 
                             flatterm( flat_some_bool )));

#if 0
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
#endif
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
                    regexp::expr( regexp::type_unit ));

}


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
       { { precond( {{ a4, regexp::expr( regexp::sel_const, usel( "zero" )) }} ), 
              statement( stat_return, p ++, a4 ) }} );

   auto fin = statement( stat_block, p ++, { s1, s2, eq, cnd1, s3, s4, s5, cnd2, s6, res } ); 

   std::cout << fin << "\n";
#endif

}

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

   auto propA = regexp::expr( regexp::ref_ident, identifier( ) + "A" );
   auto propB = regexp::expr( regexp::ref_ident, identifier( ) + "B" );
   auto propAllA = regexp::expr( regexp::set_repeat, propA );
   auto propAllB = regexp::expr( regexp::set_repeat, propB );

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

#if 0 
   rep. push_back( statement( stat_resolve, p ++, { statement( stat_assign, p ++, d0, 
                              flatterm( flat_field, x0, 
                                  exactident( identifier( ) + "f", 0 ), i0 )) } ));

#endif
   {
#if 0 
      auto call = statement( stat_assign, p ++, e0, flatterm( flat_call,
                             exactident( identifier( ) + "F", 0 ), { d0 } )); 
#endif
      std::vector< variable > var = { d0 };
      std::vector< regexp::expr > prec = { propA };

      // rep. push_back( statement( stat_resolve, p ++, { call } ));

#if 0
      rep. push_back( statement( stat_update, p ++, x0, 
                                 exactident( identifier() + "f", 0 ),
                                 { i0 }, e0 ));
#endif

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


void tests::add_nat( regexp::defmap& defs, fieldmap& flds )
{
   std::cout << "Constructing Natural Numbers:\n";

   using namespace regexp;

   auto zero = expr( flt_sel, { false, {{ usel( "zero" ), true }} } );
   zero = tuple( { zero } );
 
   auto succ = expr( flt_sel, { false, {{ usel( "succ" ), true }} } );
   succ = tuple( { succ, expr( ref_ident, identifier( ) + "nat" ) } );

   auto nat = identifier( ) + "nat";
   defs. insert( nat, expr( log_or, { zero, succ } ), exprtype_unknown );

   succ = expr( flt_sel, { false, {{ usel( "succ" ), true }} } );
   succ = tuple( { succ, expr( ref_ident, identifier( ) + "odd" ) } );
   auto even = identifier( ) + "even";
   defs. insert( even, expr( log_or, { zero, succ } ), exprtype_unknown );
  
   succ = selectors( { usel( "succ" ) } ); 
   succ = tuple( { succ, expr( ref_ident, identifier( ) + "even" ) } );
   auto odd = identifier( ) + "odd";
   defs. insert( odd, succ, exprtype_unknown );

   flds. insert( identifier( ) + "op", 
                     fielddef( fld_scalar, 
                        expr( ref_ident, identifier( ) + "nat" ), 0 ));
}


void tests::add_fol( regexp::defmap& defs, fieldmap& flds )
{
   std::cout << "\n";
   std::cout << "Constructing regular expression of simply typed first-order logic:\n\n";

   using namespace regexp;
 
   auto fol = identifier( ) + "fol"; 
   defs. insert( fol + "variable", expr( set_repeat, expr( type_char )),
       exprtype_unknown );

   auto term = fol + "term";

   {
      auto appl = 
         tuple( { selectors( { usel( "?appl" ) } ),
                  expr( conv_set2single, expr( ref_ident, fol + "variable" )),
                  expr( conv_set2single, 
                     expr( set_repeat, expr( ref_ident, fol + "term" ))) 
                } 
           );

      auto db = tuple( { selectors( { usel( "?debruijn" ) } ), 
                         expr( type_u64 ) } );

      defs. insert( term, expr( log_or, { appl, db } ), exprtype_unknown ); 
   } 

   {
      auto prim = expr( log_or, 
      {
         selectors( { usel( "?prop" ) } ), 
         tuple( { selectors( { usel( "?def" ) } ), 
                  expr( conv_set2single, expr( ref_ident, fol + "variable" )) } ) 
      });

      auto sort = tuple( { prim, expr( conv_set2single, expr( set_repeat, prim )) } );
      defs. insert( fol + "sort", std::move( sort ), exprtype_unknown  );
   } 

   defs. insert( fol + "atom", 
      tuple( { selectors( { usel( "?atom" ) } ), 
               expr( conv_set2single, expr( ref_ident, fol + "variable" )), 
               expr( conv_set2single, expr( set_repeat, 
                                         expr( ref_ident, fol + "term" ))) } ),
      exprtype_unknown );

   defs. insert( fol + "binary",
      tuple( { selectors( { usel( "?implies" ), usel( "?equiv" ) } ),
               expr( ref_ident, fol + "form" ),
               expr( ref_ident, fol + "form" ) } ),
      exprtype_unknown );

   defs. insert( fol + "nary",
      tuple( { selectors( { usel( "?and" ), usel( "?or" ) } ),
               expr( conv_set2single, expr( set_repeat, expr( ref_ident, fol + "form" ))) } ),
      exprtype_unknown );

   defs. insert( fol + "equals",
      tuple( { selectors( { usel( "?equals" ) } ),
               expr( ref_ident, fol + "term" ),
               expr( ref_ident, fol + "term" ) } ),
      exprtype_unknown );

   auto vartype = tuple( { expr( conv_set2single, 
                              expr( ref_ident, fol + "variable" )),
                           expr( ref_ident, fol + "sort" ) } );

   defs. insert( fol + "quant",
      tuple( { selectors( { usel( "?forall" ), usel( "?exists" ) } ),
               expr( conv_set2single, 
                  expr( set_repeat, vartype )),
               expr( ref_ident, fol + "form" ) } ),
      exprtype_unknown );

   defs. insert( fol + "form",
      expr( log_or, { expr( ref_ident, fol + "atom" ),
                      expr( ref_ident, fol + "equals" ),
                      expr( ref_ident, fol + "binary" ),
                      expr( ref_ident, fol + "nary" ),
                      expr( ref_ident, fol + "quant" ) } ),
      exprtype_unknown );

   flds. insert( identifier( ) + "sub1",
      fielddef( fld_scalar, expr( regexp::ref_ident, fol + "binary" ), 1 ));

   flds. insert( identifier( ) + "sub2",
      fielddef( fld_scalar, expr( regexp::ref_ident, fol + "binary" ), 2 ));

}


atm::simple tests::atm_fol( )
{
   atm::simple res;

   auto single_char = res. newstate( );
   res. comment( single_char, "single char" ); 
   res. add_delta_char( single_char );

   auto char_set = res. newstate( );
   res. comment( char_set, "set of characters" );
   res. addforall( { single_char }, char_set );

   // Eventually vartype:

   auto def = res. newstate( );
   res. comment( def, "?def" );
   {
      auto& v = res. add_delta_usel( res. trap );
      v. assign( usel( "?def" ), def );
   }

   auto prop = res. newstate( );
   res. comment( prop, "?prop" );
   {
      auto& v = res. add_delta_usel( res. trap );
      v. assign( usel( "?prop" ), prop );
   }

   auto prim = res. newstate( );
   res. comment( prim, "prim" );
   res. addtuple( { def, char_set }, prim );
   res. delta_epsilon. insert( { prop, prim } );

   auto prim_set = res. newstate( );
   res. comment( prim_set, "set of prims" );
   res. addforall( { prim }, prim_set ); 

   auto sort = res. newstate( );
   res. comment( sort, "sort" );
   res. addtuple( { prim, prim_set }, sort );
 
   auto vartype = res. newstate( );
   res. comment( vartype, "vartype" );
   res. addtuple( { char_set, sort }, vartype );

   auto vartype_set = res. newstate( );
   res. comment( vartype_set, "set of vartypes" );
   res. addforall( { vartype }, vartype_set );
 
   auto u64 = res. newstate( );
   res. comment( u64, "u64" );
   res. add_delta_u64( u64 );

   auto debruijn = res. newstate( );
   res. comment( debruijn, "?debruijn" );
   {
      auto& v = res. add_delta_usel( res. trap );
      v. assign( usel( "?debruijn" ), debruijn );
   }

   auto index = res. newstate( );
   res. comment( index, "index" );
   res. addtuple( { debruijn, u64 }, index );

   auto term = res. newstate( );
   res. comment( term, "term" );

   auto term_set = res. newstate( );
   res. comment( term_set, "set of terms" );
   res. addforall( { term }, term_set );

   auto appl = res. newstate( );
   res. comment( appl, "?appl" );
   {
      auto& v = res. add_delta_usel( res. trap );
      v. assign( usel( "?appl" ), appl );
   }
   
   res. addtuple( { appl, char_set, term_set }, term );
   res. delta_epsilon. insert( { index, term } ); 

   auto atom = res. newstate( );
   res. comment( atom, "?atom" );
   {
      auto& v = res. add_delta_usel( res. trap );
      v. assign( usel( "?atom" ), atom );
   }

   auto qnt = res. newstate( ); 
   res. comment( qnt, "?forall/?exists" );
   {
      auto& v = res. add_delta_usel( res. trap );
      v. assign( usel( "?forall" ), qnt );
      v. assign( usel( "?exists" ), qnt );
   }


   auto form = res. newstate( );
   res. comment( form, "formula" );

   res. addtuple( { atom, char_set, term_set }, form );
   res. addtuple( { qnt, vartype_set, form }, form );

   return res;
}


void modaladjectives( regexp::defmap& defs, fieldmap& flds )
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

data::tree tests::formula( )
{
   // forall x : p(x,0).

   auto zero = data::string( "zero" );

   zero = data::tuple( 
      { data::usel( "?appl" ), zero, 
        data::array( {} ) } );

   auto db = data::u64(0);
   db = data::tuple( { data::usel( "?debruijn" ), db } );

   auto p = data::string( "p" );

   p = data::tuple( 
      { data::usel( "?atom" ), p, 
        data::array( { zero, db } ) } );

   // We need the sort of natural numbers:

   auto s = data::tuple(
      { data::usel( "?def" ), 
        data::string( "Nat" )
      } );

   s = data::tuple( { s, data::array( { } ) } );

   auto vt = data::tuple( { data::string( "x" ), s } );

   return data::tuple( 
      { data::usel( "?forall" ),
        data::array( { vt } ), 
        p } );
}


