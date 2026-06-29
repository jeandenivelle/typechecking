
(* types must start with lowercase, and constructors must start *)
(* with uppercase.                                              *)

type exactname =
   | Exact of int
;;

type structtype =
   | TypeForm 
   | TypeObj
   | TypeStruct of exactname  
   | TypeUnchecked of string
   | TypeFunc of structtype * structtype list 
;;

type vartype =
   | VarType of string * structtype ;;

type term =
  | TermExact of exactname
  | TermDeBruijn of int 
  | TermUnchecked of string 
  | TermFalse 
  | TermError
  | TermTrue 
  | TermNot of term
  | TermProp of term
  | TermAnd of term * term
  | TermOr of term * term
  | TermImplies of term * term
  | TermEquiv of term * term
  | TermLazyAnd of term * term
  | TermLazyImplies of term * term
  | TermEquals of term * term
  | TermForall of ( vartype list ) * term 
  | TermExists of ( vartype list ) * term 
  | TermLet of vartype * term * term 
  | TermApply of term * ( term list )
  | TermLambda of ( vartype list ) * term 
;;

(* f t vardepth returns an optional term. If there is *)
(* a value, we return it, otherwise, we recurse.      *)

let rec outermost f tm vardepth =
   let here = f tm vardepth in
   match here with
      | Some res -> res 
      | None -> match tm with
         | TermNot sub -> TermNot( outermost f sub vardepth )
         | TermProp sub -> TermProp( outermost f sub vardepth ) 
         | TermAnd( sub1, sub2 ) -> 
              TermAnd( outermost f sub1 vardepth, outermost f sub2 vardepth ) 
         | TermOr( sub1, sub2 ) ->
              TermOr ( outermost f sub1 vardepth, outermost f sub2 vardepth )
         | TermImplies( sub1, sub2 ) ->
              TermImplies ( outermost f sub1 vardepth, outermost f sub2 vardepth )
         | TermEquiv( sub1, sub2 ) ->
              TermEquiv( outermost f sub1 vardepth, outermost f sub2 vardepth )
         | TermLazyAnd( sub1, sub2 ) ->
              TermLazyAnd( outermost f sub1 vardepth, outermost f sub2 vardepth )
         | TermLazyImplies( sub1, sub2 ) ->
              TermLazyImplies( outermost f sub1 vardepth, outermost f sub2 vardepth ) 
         | TermEquals( sub1, sub2 ) -> 
              TermEquals( outermost f sub1 vardepth, outermost f sub2 vardepth ) 
         | TermForall( vars, body ) ->
              TermForall( vars, outermost f body ( vardepth + List.length vars ))
         | TermExists( vars, body ) ->
              TermExists( vars, outermost f body ( vardepth + List.length vars )) 
         | TermApply( func, args ) ->
              TermApply( 
              
         | _ -> tm
;;


(* Lifting: *)

let lift dist =
   fun tm vardepth -> 
      match tm with
      | TermDeBruijn ind -> if ind >= vardepth then 
           Some ( TermDeBruijn ( ind + dist )) 
        else
           None 
      | _ -> None
;;

(* Substitution: *)

let subst values =
   fun tm vardepth ->
      match tm with
      | TermDeBruijn ind -> 
           if ind >= vardepth then
              let vlen = List. length values in
                 if ind < vardepth + vlen then
                    Some ( outermost ( lift vardepth ) 
                           ( List.nth values ( ind - vardepth )) 0 )
                 else
                    Some ( TermDeBruijn ( ind - vlen ))
            else
               None
      | _ -> None
;;
 
let tm = TermEquals ( TermDeBruijn 4, TermExact ( Exact 4 )) ;;


let apply (p: polarity) (f: formula) =
  match p with
  | Pos -> f
  | Neg -> Neg f
;;


let rec nnf ( p:polarity ) ( f:formula ) =
  match f with
  | Var s -> apply p f
  | And fs -> if p = Neg then Or(nnf_list p fs) else And (nnf_list p fs)
  | Or fs -> if p = Neg then And(nnf_list p fs) else Or (nnf_list p fs)
  | Imp (f1,f2) -> if p = Pos then Or ([(nnf (swap p) f1); nnf p f2])
                   else And ([(nnf p f1); nnf (swap p) f2])
  | Neg f -> nnf (swap p) f

and 
   nnf_list p = function 
      | [] -> []
      | f::fs -> ( nnf p f ) :: nnf_list p fs
;;


