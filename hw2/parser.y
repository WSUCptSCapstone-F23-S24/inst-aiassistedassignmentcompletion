%{
#include <stdio.h>
#include <stdlib.h>
#include "scanType.h"

extern int yylex();
extern FILE *yyin;
extern int yylineno;

#define YYERROR_VERBOSE

int yyerror(const char *s);

%}

%union {
    struct {
        int tokenClass;
        int numericVal;
        char *lexeme;
        int lineNo;
    } tok;
}

%token<tok> NUMCONST ID CHARCONST STRINGCONST TRUE FALSE
%token<tok> INT BOOL CHAR VOID
%token<tok> IF THEN ELSE WHILE FOR TO BY DO RETURN BREAK
%token<tok> PLUS MINUS TIMES DIVIDE MOD
%token<tok> LT LE GT GE EQ NE
%token<tok> ASSIGN PLUSASSIGN MINUSASSIGN TIMESASSIGN DIVIDEASSIGN
%token<tok> SEMI COMMA COLON LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE
%token<tok> AND OR NOT
%token PLUSPLUS
%token MINUSMINUS
%token STATIC

%%

program      : declList;
declList     : declList decl | decl;
decl         : varDecl | funDecl;
varDecl      : typeSpec varDeclList SEMI;
varDeclList  : varDeclList COMMA varDeclInit | varDeclInit;
varDeclInit  : varDeclId | varDeclId COLON simpleExp;
varDeclId    : ID | ID LBRACK NUMCONST RBRACK;
typeSpec     : INT | BOOL | CHAR;
funDecl      : typeSpec ID LPAREN parms RPAREN stmt | ID LPAREN parms RPAREN stmt;
parms        : parmList | /* empty */;
parmList     : parmList SEMI parmTypeList | parmTypeList;
parmTypeList : typeSpec parmIdList;
parmIdList   : parmIdList COMMA parmId | parmId;
parmId       : ID | ID LBRACK RBRACK;
stmt : matchedStmt
     | unmatchedStmt;
matchedStmt : IF simpleExp THEN matchedStmt ELSE matchedStmt
            | /* other kinds of statements like WHILE, FOR, etc. that don't cause ambiguity */
            ;
unmatchedStmt : IF simpleExp THEN stmt
              | IF simpleExp THEN matchedStmt ELSE unmatchedStmt
              ;

simpleExp : ID | NUMCONST;

%%

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
    return 0;
}
