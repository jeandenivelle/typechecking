#require "num";;

open Num

type arNop =
  | Plus | Mult

type unop =
  | Recipr
  | Neg

type binop =
  | Minus
  | Div

type mathufun =
  | Sin
  | Cos
  | Ln
  | Exp
  | Sqrt

type mathexpr =
  | Pi
  | E
  | Num of num 
  | Var of string
  | Unop  of unop * mathexpr
  | Binop of binop * mathexpr * mathexpr
  | ArNop of arNop * mathexpr list
  | Pow of mathexpr * num
  | Ufun of mathufun * mathexpr


let rec deriv e v =
  match e with
  | Pi | E | Num _       -> Num (Int 0)
  | Var x                -> if x = v then Num (Int 1) else Num (Int 0)
  | Unop (Neg, e1)       -> Unop(Neg, deriv e1 v)
  | Unop (Recipr, e)     ->
     let de = deriv e v in ArNop (Mult, [Num (Int (-1));
                                         Binop(Div, Num (Int 1), Pow(e, Int 2));
                                         de])
  | Binop(Minus, e1, e2) -> let (de1,de2) = (deriv e1 v, deriv e2 v) in
                            Binop (Minus, de1,de2)
  | Binop(Div, e1, e2)   -> let (de1,de2) = (deriv e1 v, deriv e2 v) in
                            let prod1 = ArNop (Mult, [de1;e2]) in
                            let prod2 = ArNop (Mult, [Num (Int (-1));e1;de2]) in
                            let prod3 = ArNop (Mult, [e2;e2]) in
                            let sum = ArNop (Plus, [prod1;prod2]) in
                            Binop(Div, sum, prod3)
  | ArNop(Plus, es)      -> let ds = List.fold_right
                                       (fun x l -> (deriv x v):: l)
                                       es
                                       [] in
                            ArNop(Plus, ds)
  | ArNop(Mult, es)      -> failwith "not implemented"
  | Pow(e1, n)           -> let de1 = deriv e1 v in
                            ArNop (Mult, [Num n; Pow(e1, n -/ (Int 1)); de1])
  | Ufun(Sin, e1)        -> let de1 = deriv e1 v in
                            ArNop (Mult, [Ufun(Cos, e1); de1])
  | Ufun(Cos, e1)        -> let de1 = deriv e1 v in
                            ArNop (Mult, [Num(Int (-1)); Ufun(Sin, e1); de1])
  |_                     -> failwith "not implemented"
