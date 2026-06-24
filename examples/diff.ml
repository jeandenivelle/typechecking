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
  Pi
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
  | ArNop(Mult, es)      ->
     (match es with
     | []        -> Num (Int 1)
     | [e1]      -> deriv e1 v
     | e1::e2::t ->
        let (de1,de2) = (deriv e1 v, deriv  (ArNop(Mult,e2::t)) v) in
        let prod1 = ArNop (Mult, [de1;e2]) in
        let prod2 = ArNop (Mult, [e1;de2]) in
        ArNop (Plus, [prod1;prod2])) 
  | Pow(e1, n)           -> let de1 = deriv e1 v in
                            ArNop (Mult, [Num n; Pow(e1, n -/ (Int 1)); de1])
  | Ufun(Sin, e1)        -> let de1 = deriv e1 v in
                            ArNop (Mult, [Ufun(Cos, e1); de1])
  | Ufun(Cos, e1)        -> let de1 = deriv e1 v in
                            ArNop (Mult, [Num(Int (-1)); Ufun(Sin, e1); de1])
  |_                     -> failwith "not implemented"


let parens s = "("^s^")"
let string_of_mathufun = function
  | Sin -> "sin "
  | Cos -> "cos "
  | Ln -> "ln "
  | Exp -> "exp "
  | Sqrt -> "sqrt "

let rec string_of_mathexpr = function
  | Pi -> "π"
  | E  -> "e"
  | Num n -> string_of_num n
  | Var x -> x
  | Unop (Neg, e1)  -> "-("^(string_of_mathexpr e1)^")"
  | Unop (Recipr, e1)-> "("^(string_of_mathexpr e1)^")⁻¹"
  | Binop(Minus, e1, e2) -> "("^(string_of_mathexpr e1)^
                              ") - ("^(string_of_mathexpr e2)^")"
  | Binop(Div, e1, e2) -> "("^(string_of_mathexpr e1)^
                            ") / ("^(string_of_mathexpr e2)^")"
  | ArNop(Plus, [])    -> "0"
  | ArNop(Plus, e::es) -> parens @@
                            List.fold_left
                              (fun s e -> s^" + "^(string_of_mathexpr e))
                              (string_of_mathexpr e)
                              es
  | ArNop(Mult, [])    -> "1"
  | ArNop(Mult, e::es) -> parens @@
                            List.fold_left
                              (fun s e -> s^" * "^(string_of_mathexpr e))
                              (string_of_mathexpr e)
                              es
  | Pow(e1, n)           -> (parens (string_of_mathexpr e1)) ^"^"^
                              string_of_num n
  | Ufun(f, e1)     -> (string_of_mathufun f) ^ (string_of_mathexpr e1)
