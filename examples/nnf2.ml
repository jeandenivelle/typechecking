type polarity =
  |Pos |Neg

let swap = function
  | Pos -> Neg
  | Neg -> Pos

(* type usel = *)
(*   | Neg *)

(* type bsel = *)
(*   |Imp  *)

type nsel =
  | And | Or

let swap_nsel = function
  | And -> Or
  | Or -> And

type formula =
  | Var of string
  | Neg of formula
  | Imp of formula * formula 
  | Nary  of nsel * formula list


let apply (p: polarity) (f: formula) =
  match p with
  |Pos -> f
  |Neg -> Neg f

let rec nnf (p:polarity) (f:formula) =
  match f with
  | Var s -> apply p f
  | Imp (f1,f2) -> if p = Pos then Nary (Or, ([(nnf (swap p) f1); nnf p f2]))
                   else Nary(And, ([(nnf p f1); nnf (swap p) f2]))
  | Neg f -> nnf (swap p) f
  | Nary (nsel,fs)  -> if p = Neg then Nary (swap_nsel nsel, nnf_list p fs)
               else Nary( nsel, nnf_list p fs)


and nnf_list p = function 
  | [] -> []
  | f::fs -> (nnf p f):: nnf_list p fs

let rec eq_form f1 f2 =
  match f1,f2 with
  | Var s1, Var s2 -> s1 = s2
  | Neg sf1, Neg sf2 -> eq_form sf1 sf2
  | Imp (sf1,sf2), Imp (sf21,sf22) -> eq_form sf1 sf21 && eq_form sf2 sf22
  | Nary (nsel1, fs1), Nary (nsel2,fs2) -> nsel1 = nsel2 && eq_forms fs1 fs2
  | _ -> false
and eq_forms fs1 fs2 = match fs1, fs2 with
  | [],[] -> true
  | f1::fs1, f2::fs2 -> eq_form f1 f2 && eq_forms fs1 fs2
  | _ -> false

let( ) = print_endline ( nnf_list Pos [] )

