%{
#include <stdio.h>
#include "scanType.h"

int yylex();
int yyerror(const char* msg);
void yyerror_recover(const char* msg);

extern int linenum;
extern char* yytext;
extern int yylineno;
extern int yylval_int;
extern char yylval_char;
extern char* yylval_str;

%}

%union {
    int ival;
    char cval;
    char* sval;
}

%token <ival> NUM BOOLCONST
%token <cval> CHAR
%token <sval> ID

%start tokenlist

%%

tokenlist: tokenlist token
         | token
         ;

token: NUM {
    printf("Line %d: NUM %d\n", linenum, $1);
}
| BOOLCONST {
    printf("Line %d: BOOLCONST %s\n", linenum, $1 == 1 ? "true" : "false");
}
| CHAR {
    printf("Line %d: CHAR '%c'\n", linenum, $1);
}
| ID {
    printf("Line %d: ID %s\n", linenum, $1);
}
;

%%

int main(int argc, char* argv[]) {
    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
        yyin = file;
    }
    yyparse();
    return 0;
}

int yyerror(const char* msg) {
    fprintf(stderr, "Line %d: %s\n", linenum, msg);
    yyerror_recover(msg);
    return 1;
}

void yyerror_recover(const char* msg) {
    // Move to the next line
    while (yylex() != '\n' && !feof(yyin)) {}
}
