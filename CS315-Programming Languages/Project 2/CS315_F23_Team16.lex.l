%{
#include <stdio.h>
#include "y.tab.h"
void yyerror(char *);
%}

%option yylineno

%%
    
"=" {return EQUALSIGN;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MULTIPLICATIONOPERATOR;}
"/" {return DIVISIONOPERATOR;}
"%" {return MODULAOPERATOR;}
"^" {return EXPONENTOPERATOR;}
"(" { return LEFTPARANTHESIS; }
")" { return RIGHTPARANTHESIS; }
"," { return COMMA; }
"{" { return LEFTCURLYBRACE; }
"}" { return RIGHTCURLYBRACE; }
";" { return SEMICOLON; }
"[" { return LEFTSQUAREBRACKET; }
"]" { return RIGHTSQUAREBRACKET; }
"<" { return LESSTHAN; }
">" { return BIGGERTHAN; }
"<=" { return LESSTHANOREQUALTO; }
">=" { return BIGGERTHANOREQUALTO; }
"==" { return EQUALTO; }
"!=" { return NOTEQUALTO; }
"&&" { return AND; }
"||" { return OR; }
"if" { return IF; }
"then" { return THEN; }
"else" { return ELSE; }
"elseif" { return ELSEIF; }
"while" { return WHILE; }
"for" { return FOR; }
"do" { return DO; }
"input" { return INPUT; }
"output" { return OUTPUT; }
"function" { return FUNCTION; }
"return" { return RETURN; }
"const" { return CONST; }
"::=" {return DATASTRUCTUREASSIGNMENT; }
"\\&" { return PASSBYREFERENCE; }
"#"\s*[^\n]* { return SINGLELINECOMMENT; }
"?"[^?]*"?" { return MULTILINECOMMENT; }
[A-Za-z][A-Za-z0-9_]* { return IDENTIFIER; }
\"([^\\\"]|\\\"|\\\\)*\" { return STRING; }
[0-9]+ { return INTEGER; }
[ \t]+ ;
\n { }

%%

int yywrap(void) {
    return 1;
}
