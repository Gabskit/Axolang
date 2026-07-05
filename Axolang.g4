grammar Axolang;

// Regla raíz del programa
program
: ' '*? statement* EOF
;

// Sentencias válidas en Axolang
statement
: varDeclaration
| matchStatement
;

// Declaración de variables (Tipos primitivos, Auto-inferencia y Sintaxis de Array Exacta)
varDeclaration
: type ' ' IDENTIFIER '=' expression
| type ' ' IDENTIFIER '[' INT_LITERAL? ']' '=' arrayLiteral
| type ' ' IDENTIFIER
| type ' ' IDENTIFIER '[' INT_LITERAL ']'
;

type
: 'xxsvar' | 'xsvar' | 'svar' | 'var' | 'lvar' | 'xlvar' | 'xxlvar' | 'fun'
;

matchStatement
: 'match' '(' IDENTIFIER ')' '{' matchCase+ '}'
;

matchCase
:  expression '->' declaration ';'
|  expression '->' '{'  OTHER '}'
| '_' '->' declaration ';'
;

declaration
:  IDENTIFIER '=' expression
|  IDENTIFIER '(' OTHER ')'
| statement
;

// Un paquete contiene declaraciones internas estructuradas
pkg
: ' '*? '{' varDeclaration* '}'
;

// Expresiones jerárquicas de Axolang
expression
: INT_LITERAL
| UINT_LITERAL
| FLOAT_LITERAL
| IDENTIFIER
| COMPLEX_LITERAL
| CHAR_LITERAL
| STRING_LITERAL
| DECIMAL_LITERAL
| pkg
| BOOLEAN
| arrayLiteral
| arrayAccess
;

arrayLiteral
: '«' ' '? expression (',' ' '? expression)* '»'
;

arrayAccess
: IDENTIFIER '[' expression ']'
;

// --- TOKENS LÉXICOS ---
IDENTIFIER : [\u{1F4A9}\u{1F926}\p{Alpha}\p{General_Category=Other_Letter}][\u{1F4A9}\u{1F926}\p{Alnum}\p{General_Category=Other_Letter}]* ;
CHAR_LITERAL : [ \t]*? '\'' [\u{1F4A9}\u{1F926}\p{Alnum}\p{General_Category=Other_Letter}] '\'';
STRING_LITERAL : [ \t]*? '"' [ \t\n\u{1F4A9}\u{1F926}\p{Alnum}\p{General_Category=Other_Letter}]* '"';
INT_LITERAL : [ \t]*? [+-]? [ \t]*? [0-9]+ ;
UINT_LITERAL : [ \t]*? [0-9]+ 'u';
FLOAT_LITERAL : [ \t]*? [+-]? [ \t]*? [0-9]+ ('.' [0-9]+)?;
DECIMAL_LITERAL : [ \t]*? [+-]? [ \t]*? [0-9]+ ('.' [0-9]+)? [dD];
COMPLEX_LITERAL : [ \t]*? [+-]? [ \t]*? [0-9]+ ('.' [0-9]+)? [ \t]*? [+-] [ \t]*? [0-9]+ ('.' [0-9]+)? [ \t]*? 'i'
| [ \t]*? [+-]? [ \t]*? [0-9]+ ('.' [0-9]+)? [ \t]*? 'i';
BOOLEAN : [ \t]*? 'true' | [ \t]*? 'false';
WS : [ \t\r\n]+ -> skip ;

OTHER : .+? ;