type polarity =
  |Pos |Neg

let swap = function
  | Pos -> Neg
  | Neg -> Pos


type formula =
  | Var of string
  | And of formula list
  | Or of formula list
  | Imp of formula * formula
  | Neg of formula

let apply (p: polarity) (f: formula) =
  match p with
  |Pos -> f
  |Neg -> Neg f

let rec nnf (p:polarity) (f:formula) =
  match f with
  | Var s -> apply p f
  | And fs -> if p = Neg then Or(nnf_list p fs) else And (nnf_list p fs)
  | Or fs -> if p = Neg then And(nnf_list p fs) else Or (nnf_list p fs)
  | Imp (f1,f2) -> if p = Pos then Or ([(nnf (swap p) f1); nnf p f2])
                   else And ([(nnf p f1); nnf (swap p) f2])
  | Neg f -> nnf (swap p) f

and nnf_list p = function 
  | [] -> []
  | f::fs -> (nnf p f):: nnf_list p fs

