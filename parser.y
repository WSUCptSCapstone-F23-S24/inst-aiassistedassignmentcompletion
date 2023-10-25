%{
#include <stdio.h>
#include <stdlib.h>
#include "scanType.h" // you can remove this include if it's not needed elsewhere

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

%token<tok> NUMBER ID BOOLCONST STRING CHAR

%%

tokens      : tokens token
            | /* empty */
            ;

token       : NUMBER { printf("Line: %d, Token: NUMBER, Value: %d\n", (yyvsp[(1) - (1)].tok).lineNo, (yyvsp[(1) - (1)].tok).numericVal); }
            | ID { printf("Line: %d, Token: ID, Lexeme: %s\n", (yyvsp[(1) - (1)].tok).lineNo, (yyvsp[(1) - (1)].tok).lexeme); }
            | BOOLCONST { printf("Line: %d, Token: BOOLCONST, Value: %d\n", (yyvsp[(1) - (1)].tok).lineNo, (yyvsp[(1) - (1)].tok).numericVal); }
            | STRING { printf("Line: %d, Token: STRING, Value: %s\n", (yyvsp[(1) - (1)].tok).lineNo, (yyvsp[(1) - (1)].tok).lexeme); }
            | CHAR { printf("Line: %d, Token: CHAR, Value: %c\n", (yyvsp[(1) - (1)].tok).lineNo, (yyvsp[(1) - (1)].tok).numericVal); }
            ;

%%



int yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
    return 0;
}

int main(int argc, char *argv[]) 
{
    // Initialize scanner
    // ...

    yyparse();

    return 0;
}
