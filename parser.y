%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanType.h"

extern int yylval_int;
extern char yylval_char;
extern char* yylval_str;
extern int linenum;
extern FILE* yyin;

int yylex();
int yyparse(void);
int yyerror(const char* msg);
void yyerror_recover(const char* msg);

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

// Define the grammar rules

tokenlist: tokenlist token
         | token
         ;

token: NUM {
    struct TokenData tokenData;
    tokenData.tokenclass = NUM;
    tokenData.linenum = linenum;
    tokenData.tokenstr = strdup(yytext);
    tokenData.nvalue = $1;
    printf("Line %d: NUM %d\n", linenum, $1);
}
| BOOLCONST {
    struct TokenData tokenData;
    tokenData.tokenclass = BOOLCONST;
    tokenData.linenum = linenum;
    tokenData.tokenstr = strdup(yytext);
    tokenData.nvalue = $1 == 1 ? 1 : 0;
    printf("Line %d: BOOLCONST %s\n", linenum, $1 == 1 ? "true" : "false");
}
| CHAR {
    struct TokenData tokenData;
    tokenData.tokenclass = CHAR;
    tokenData.linenum = linenum;
    tokenData.tokenstr = strdup(yytext);
    tokenData.cvalue = $1;
    printf("Line %d: CHAR '%c'\n", linenum, $1);
}
| ID {
    struct TokenData tokenData;
    tokenData.tokenclass = ID;
    tokenData.linenum = linenum;
    tokenData.tokenstr = strdup(yytext);
    tokenData.svalue = strdup($1);
    printf("Line %d: ID %s\n", linenum, $1);
}
;

%%

// Main function to start parsing
int main(int argc, char* argv[]) {
    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
        yyin = file;
    }
    yyparse(); // Start parsing
    return 0;
}

// Error handling function
int yyerror(const char* msg) {
    fprintf(stderr, "Line %d: %s\n", linenum, msg);
    yyerror_recover(msg);
    return 1;
}

// Error recovery function
void yyerror_recover(const char* msg) {
    while (yylex() != '\n' && !feof(yyin)) {}
}
