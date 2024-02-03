%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(char* s);
extern int yylineno;
%}

%token EQUALSIGN
%token PLUS
%token MINUS
%token MULTIPLICATIONOPERATOR
%token DIVISIONOPERATOR
%token MODULAOPERATOR
%token EXPONENTOPERATOR
%token LEFTPARANTHESIS
%token RIGHTPARANTHESIS
%token COMMA
%token LEFTCURLYBRACE
%token RIGHTCURLYBRACE
%token SEMICOLON
%token LEFTSQUAREBRACKET
%token RIGHTSQUAREBRACKET
%token LESSTHAN
%token BIGGERTHAN
%token LESSTHANOREQUALTO
%token BIGGERTHANOREQUALTO
%token EQUALTO
%token NOTEQUALTO
%token AND
%token OR
%token IF
%token THEN
%token ELSE
%token ELSEIF
%token WHILE
%token FOR
%token DO
%token INPUT
%token OUTPUT
%token FUNCTION
%token RETURN
%token CONST
%token DATASTRUCTUREASSIGNMENT
%token SINGLELINECOMMENT
%token MULTILINECOMMENT
%token PASSBYREFERENCE
%token IDENTIFIER
%token STRING
%token INTEGER

%left AND
%left OR
%nonassoc EQUALSIGN
%left PLUS MINUS
%left BIGGERTHANOREQUALTO LESSTHANOREQUALTO BIGGERTHAN LESSTHAN
%left MULTIPLICATIONOPERATOR DIVISIONOPERATOR MODULAOPERATOR
%left DATASTRUCTUREASSIGNMENT
%right EXPONENTOPERATOR

%%

program: statement_list

statement_list: statement | statement statement_list

statement: conditional_statement | assignment_statement | loop_statement | input_statement | output_statement | function_definition | comment_statement | data_access_statement | data_structure_change_statement | function_call | error statement

assignment_statement: initialization_statement | data_structure_statement

initialization_statement: IDENTIFIER EQUALSIGN expression SEMICOLON | CONST IDENTIFIER EQUALSIGN expression SEMICOLON | IDENTIFIER EQUALSIGN function_call SEMICOLON 

function_call: IDENTIFIER LEFTPARANTHESIS parameters RIGHTPARANTHESIS |  IDENTIFIER LEFTPARANTHESIS RIGHTPARANTHESIS

data_structure_statement: IDENTIFIER DATASTRUCTUREASSIGNMENT data SEMICOLON

data_structure_change_statement: IDENTIFIER LEFTSQUAREBRACKET INTEGER RIGHTSQUAREBRACKET EQUALSIGN signed_integer SEMICOLON | IDENTIFIER LEFTSQUAREBRACKET IDENTIFIER RIGHTSQUAREBRACKET EQUALSIGN signed_integer SEMICOLON | IDENTIFIER LEFTSQUAREBRACKET INTEGER RIGHTSQUAREBRACKET EQUALSIGN IDENTIFIER SEMICOLON | IDENTIFIER LEFTSQUAREBRACKET IDENTIFIER RIGHTSQUAREBRACKET EQUALSIGN IDENTIFIER SEMICOLON

data_access_statement: IDENTIFIER EQUALSIGN IDENTIFIER LEFTSQUAREBRACKET INTEGER RIGHTSQUAREBRACKET SEMICOLON| IDENTIFIER EQUALSIGN IDENTIFIER LEFTSQUAREBRACKET IDENTIFIER RIGHTSQUAREBRACKET SEMICOLON

expression: term | expression PLUS term | expression MINUS term

term: factor | term MULTIPLICATIONOPERATOR factor | term DIVISIONOPERATOR factor | term MODULAOPERATOR factor

factor: factor EXPONENTOPERATOR factor | IDENTIFIER | LEFTPARANTHESIS expression RIGHTPARANTHESIS | signed_integer

conditional_statement: IF LEFTPARANTHESIS logical_statement RIGHTPARANTHESIS THEN LEFTCURLYBRACE statement_list RIGHTCURLYBRACE else_if_clause | IF LEFTPARANTHESIS logical_statement RIGHTPARANTHESIS THEN LEFTCURLYBRACE statement_list RIGHTCURLYBRACE

else_if_clause: ELSEIF LEFTPARANTHESIS logical_statement RIGHTPARANTHESIS THEN LEFTCURLYBRACE statement_list RIGHTCURLYBRACE else_if_clause | ELSE LEFTCURLYBRACE statement_list RIGHTCURLYBRACE | ELSEIF LEFTPARANTHESIS logical_statement RIGHTPARANTHESIS THEN LEFTCURLYBRACE statement_list RIGHTCURLYBRACE

loop_statement: for_loop | while_loop | dowhile_loop

for_loop: FOR LEFTPARANTHESIS initialization_statement logical_statement SEMICOLON update RIGHTPARANTHESIS LEFTCURLYBRACE statement_list RIGHTCURLYBRACE

while_loop: WHILE LEFTPARANTHESIS logical_statement RIGHTPARANTHESIS LEFTCURLYBRACE statement_list RIGHTCURLYBRACE

dowhile_loop: DO LEFTCURLYBRACE statement_list RIGHTCURLYBRACE WHILE LEFTPARANTHESIS logical_statement RIGHTPARANTHESIS

logical_statement : primary_logical_statement | primary_logical_statement logical_operator logical_statement
 
primary_logical_statement : LEFTPARANTHESIS expression comparison_operator expression RIGHTPARANTHESIS

logical_operator : AND | OR

comparison_operator: BIGGERTHANOREQUALTO | LESSTHANOREQUALTO | BIGGERTHAN | LESSTHAN | EQUALTO | NOTEQUALTO

update: IDENTIFIER PLUS PLUS | IDENTIFIER MINUS MINUS

input_statement: INPUT IDENTIFIER SEMICOLON

output_statement: OUTPUT STRING SEMICOLON | OUTPUT IDENTIFIER SEMICOLON

function_definition: FUNCTION IDENTIFIER LEFTPARANTHESIS parameters RIGHTPARANTHESIS LEFTCURLYBRACE statement_list return_statement RIGHTCURLYBRACE | FUNCTION IDENTIFIER LEFTPARANTHESIS RIGHTPARANTHESIS LEFTCURLYBRACE statement_list return_statement RIGHTCURLYBRACE

parameters: IDENTIFIER | PASSBYREFERENCE IDENTIFIER | IDENTIFIER COMMA parameters | PASSBYREFERENCE IDENTIFIER COMMA parameters

return_statement: RETURN expression SEMICOLON

data: LEFTSQUAREBRACKET data_content RIGHTSQUAREBRACKET

data_content: IDENTIFIER | signed_integer | IDENTIFIER COMMA data_content | signed_integer COMMA data_content

comment_statement: SINGLELINECOMMENT | MULTILINECOMMENT

signed_integer: INTEGER | MINUS INTEGER |PLUS INTEGER

%%

void yyerror(char *s) {
    fprintf(stderr, "Syntax error at line %d: %s!\n", yylineno, s);
}

int main(void){
 yyparse();
if(yynerrs < 1){
        printf("Input program is valid\n");
    }
 return 0;
}
