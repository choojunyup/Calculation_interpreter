# Calculation_interpreter
Calculation_interpreter

1.Backus-Naur Form

<expr> ::= <term> (("+" | "-") <term>)*
<term> ::= <factor> ("*" <factor>)*
<factor> ::= <primary-expr> | ("+" | "-") <factor>
<primary-expr> ::= <decimal> | "(" <expr> ")"

2.use 
 
- cmd open
- typing " interperter (1+2)*-2+1 "
- result
"
token parser ok

****token****
operator:(
digit:1
operator:+
digit:2
operator:)
operator:*
operator:-
digit:2
operator:+
digit:1
(end):

<expr> -> <term> -> <factor> -> <primary_expr> -> <expr> -> <term> -> <factor> -> <primary_expr> -> <decimal> -> 1

+
<term> -> <factor> -> <primary_expr> -> <decimal> -> 2

*
<factor> ->
-
<factor> -> <primary_expr> -> <decimal> -> 2

+
<term> -> <factor> -> <primary_expr> -> <decimal> -> 1

ast
(1+2)*-2+1
(+)(*)(+)(1)(2)(-)(0)(2)(1)
********result*******
(1+2)*-2+1 = -5.000000
********result*******
"
