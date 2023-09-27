%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanType.h"  // Include the token data structure
%}

%union {
    int nvalue;
    char* svalue;
}

%token <svalue> BOOLCONST IDENTIFIER
%token NUMBER FLOAT
%token PLUS MINUS STAR SLASH PERCENT
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token LESS GREATER EQUAL
%token COMMA SEMICOLON EXCLAMATION AMPERSAND CARET PIPE QUESTION COLON DOT
%token <nvalue> INT
%token <svalue> FLOAT

%type <nvalue> constant
%type <svalue> id

%%

program : /* empty / 
        | program statement
        ;

statement : expression SEMICOLON
          | assignment SEMICOLON
          ;

expression : constant
           | id
           | expression PLUS expression
           | expression MINUS expression
           | expression STAR expression
           | expression SLASH expression
           | LPAREN expression RPAREN
           ;

constant : NUMBER
         | BOOLCONST
         | FLOAT
         ;

id : IDENTIFIER
   ;

assignment : id EQUAL expression
           ;

%%

void yyerror(const char s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(int argc, char* argv[]) {
    yyparse();
    return 0;
}