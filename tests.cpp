
#include <list>

#include "tests.h"

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

   auto propSucc = regexp::expr( regexp::tuple, 
      { regexp::expr( regexp::sel_const, usel( "succ" )),
        regexp::expr( regexp::ident, exactident( identifier( ) + "nat", 0 )) } );

   auto propEven = regexp::expr( regexp::ident, 
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

   auto propA = regexp::expr( regexp::ident, exactident( identifier( ) + "A", 0 ));
   auto propB = regexp::expr( regexp::ident, exactident( identifier( ) + "B", 0 ));
   auto propAllA = regexp::expr( regexp::log_forall, propA );
   auto propAllB = regexp::expr( regexp::log_forall, propB );

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
      std::vector< regexp::expr > prec = { propA };

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


// Add natural numbers, even and odd numbers:

void tests::add_nat( regexp::defmap& prp, fieldmap& flds )
{
   std::cout << "Constructing Natural Numbers:\n";

   using namespace regexp;

   auto zero = expr( sel_const, usel( "zero" ));
   zero = expr( tuple, { zero } );
 
   auto succ = expr( sel_const, usel( "succ" ));
   succ = expr( tuple, 
      { succ, expr( ident, { identifier( ) + "nat", 0 } ) } );

   auto nat = exactident( identifier( ) + "nat", 0 );
   prp. insert( nat, expr( log_or, { zero, succ } ));

   succ = expr( sel_const, usel( "succ" ));
   succ = expr( tuple, { succ, expr( ident, { identifier( ) + "odd", 0 } ) } );
   auto even = exactident( identifier( ) + "even", 0 );
   prp. insert( even, expr( log_or, { zero, succ } ));
  
   succ = expr( sel_const, usel( "succ" )); 
   succ = expr( tuple, { succ, expr( ident, { identifier( ) + "even", 0 } ) } );
   auto odd = exactident( identifier( ) + "odd", 0 );
   prp. insert( odd, succ );

   flds. insert( exactident( identifier( ) + "op", 0 ), 
                     fielddef( fld_scalar, 
                        expr( ident, { identifier( ) + "nat", 0 } ), 0 ));
}


void tests::add_fol( regexp::defmap& prp, fieldmap& flds )
{
   std::cout << "\n";
   std::cout << "Constructing definition of simply typed first-order logic:\n\n";
      // The definition was copied from an unfinished (hardly started)
      // implementation of geo.

   using namespace regexp;
 
   auto ident = exactident( identifier( ) + "ident", 0 );

   prp. insert( ident, expr( tuple, { expr( log_forall, expr( type_char )) } ));

   flds. insert( exactident( identifier( ) + "c", 0 ),
      fielddef( fld_vector, expr( regexp::ident, ident ), 0 ));   

   //// term:

   auto term = exactident( identifier( ) + "term", 0 );

   {
      auto tm = expr( tuple, { expr( regexp::ident, ident ),
           expr( log_forall, expr( regexp::ident, ident ))
         } );

      prp. insert( term, tm );
   }

   flds. insert( exactident( identifier( ) + "func", 0 ),
      fielddef( fld_scalar,
         expr( regexp::ident, term ), 0 ));  

   flds. insert( exactident( identifier( ) + "args", 0 ),
      fielddef( fld_vector,
         expr( regexp::ident, term ), 1 ));  


   //// sort:

   auto sort = exactident( identifier( ) + "sort", 0 );

   {
      auto prim = expr( log_or, 
               { expr( sel_const, usel( "truthval" )),
                 expr( sel_const, usel( "obj" )),
                 expr( sel_const, usel( "set" )) } );

      prim = expr( tuple, { prim } );

      auto named = expr( tuple,  
         { expr( sel_const, usel( "named" )),
           expr( regexp::ident, ident ) } );

      prp. insert( sort, expr( log_or, { prim, named } )); 
   };
  
   // op gets index 1, because 'op' of nat has index 0.
 
   flds. insert( exactident( identifier( ) + "op", 1 ),
      fielddef( fld_scalar,
         expr( regexp::ident, sort ), 0 ));

   flds. insert( exactident( identifier( ) + "name", 0 ),
      fielddef( fld_scalar,
         expr( tuple,
            { expr( sel_const, usel( "named" )),
              expr( regexp::ident, ident )
            }), 1 ));

   /// fol :
 
   auto fol = exactident( identifier( ) + "fol", 0 );

   auto atom = expr( tuple, { expr( sel_const, usel( "atom" )),
        expr( regexp::ident, ident ), 
        expr( log_forall, expr( regexp::ident, term )) 
      } );

   auto negated = expr( tuple,
      { expr( sel_const, usel( "not" )),
        expr( regexp::ident, fol )
      } );

   auto eq = expr( tuple,
      { expr( sel_const, usel( "equals" )),
        expr( regexp::ident, fol ),
        expr( regexp::ident, fol )
      } );

   auto bin = expr( tuple,
      { expr( log_or, { expr( sel_const, usel( "implies" )),
                                    expr( sel_const, usel( "equiv" )) } ),
        expr( regexp::ident, fol ),
        expr( regexp::ident, fol ) 
      } );

   auto nary = expr( tuple,
      { expr( log_or, { expr( sel_const, usel( "and" )),
                                    expr( sel_const, usel( "or" )) } ),
        expr( log_forall, expr( regexp::ident, fol )) 
      } );

   auto quant = expr( tuple,
      { expr( log_or, { expr( sel_const, usel( "forall" )),
                                    expr( sel_const, usel( "exists" )) } ), 
        expr( log_forall, expr( regexp::ident, ident )),
        expr( log_forall, expr( regexp::ident, sort )),
      } );

   prp. insert( fol, expr( log_or, { atom, eq, negated, bin, nary, quant } ));


   flds. insert( exactident( identifier( ) + "op", 2 ),
      fielddef( fld_scalar,
         expr( regexp::ident, fol ), 0 ));

   flds. insert( exactident( identifier( ) + "sub", 0 ),
      fielddef( fld_scalar,
         expr( tuple,
            { expr( sel_const, usel( "not" )),
              expr( regexp::ident, fol )
            }), 1 ));

   flds. insert( exactident( identifier( ) + "sub1", 0 ),
      fielddef( fld_scalar,
         expr( tuple,
            { expr( sel_const, usel( "equals" )),
              expr( regexp::ident, term ),
              expr( regexp::ident, term )
            }), 1 ));

   flds. insert( exactident( identifier( ) + "sub2", 0 ),
      fielddef( fld_scalar,
         expr( tuple,
            { expr( sel_const, usel( "equals" )),
              expr( regexp::ident, term ),
              expr( regexp::ident, term )
            }), 2 ));

   // sub1,sub2 of binary logical operator:

   flds. insert( exactident( identifier( ) + "sub1", 1 ),
      fielddef( fld_scalar,
         expr( tuple, { expr( log_or,
                 { expr( sel_const, usel( "implies" )),
                   expr( sel_const, usel( "equiv" ))
                 }
              ),
              expr( regexp::ident, fol ),
              expr( regexp::ident, fol )
            }), 1 ));

   flds. insert( exactident( identifier( ) + "sub2", 1 ),
      fielddef( fld_scalar,
         expr( tuple,
            { expr( log_or,
                 { expr( sel_const, usel( "implies" )),
                   expr( sel_const, usel( "equiv" ))
                 }
              ),
              expr( regexp::ident, fol ),
              expr( regexp::ident, fol )
            }), 2 ));

   // sub of n-ary logical operator:

   flds. insert( exactident( identifier( ) + "sub", 1 ),
      fielddef( fld_vector,
         expr( tuple,
            { expr( log_or,
                 { expr( sel_const, usel( "and" )),
                   expr( sel_const, usel( "or" ))
                 }
              ),
              expr( log_forall, expr( regexp::ident, fol )) 
            }), 1 ));

   // body of quantifier:

   flds. insert( exactident( identifier( ) + "body", 1 ),
      fielddef( fld_scalar,
         expr( tuple,
            { expr( log_or,
                 { expr( sel_const, usel( "forall" )),
                   expr( sel_const, usel( "exists" ))
                 }
              ),
              expr( expr( regexp::ident, fol )),
              expr( log_forall, expr( regexp::ident, ident )),
              expr( log_forall, expr( regexp::ident, sort )) 
            }), 1 ));

   // Preferred name of quantified variable: 

   flds. insert( exactident( identifier( ) + "pref", 1 ),
      fielddef( fld_vector,
         expr( tuple,
            { expr( log_or,
                 { expr( sel_const, usel( "forall" )),
                   expr( sel_const, usel( "exists" ))
                 }
              ),
              expr( expr( regexp::ident, fol )),
              expr( log_forall, expr( regexp::ident, ident )),
              expr( log_forall, expr( regexp::ident, sort ))
            }), 2 ));


   // Sort of quantified variable: 

   flds. insert( exactident( identifier( ) + "srt", 1 ),
      fielddef( fld_vector,
         expr( tuple,
            { expr( log_or,
                 { expr( sel_const, usel( "forall" )),
                   expr( sel_const, usel( "exists" ))
                 }
              ),
              expr( expr( regexp::ident, fol )),
              expr( log_forall, expr( regexp::ident, ident )),
              expr( log_forall, expr( regexp::ident, sort ))
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


