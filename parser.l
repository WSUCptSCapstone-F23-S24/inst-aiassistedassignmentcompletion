%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanType.h"

extern int yylval_int;
extern char yylval_char;
extern char* yylval_str;
extern int linenum;

int yylex();
%}

%option noyywrap
%option yylineno

%%

[ \t\r\f\v]+             /* skip whitespace */
"true"                   { yylval_int = 1; return BOOLCONST; }
"false"                  { yylval_int = 0; return BOOLCONST; }
[0-9]+                   { yylval_int = atoi(yytext); return NUM; }
'\\'.'                   { yylval_char = yytext[1]; return CHAR; }
'\'[^\\'\n]'\n?          { yylval_char = yytext[1]; return CHAR; }
'\'\\'\\'\n?             { yylval_char = '\''; return CHAR; }
'\'\\'.'\n?              { yyerror("Illegal character constant"); }
[a-zA-Z_][a-zA-Z0-9_]*   { yylval_str = strdup(yytext); return ID; }
.                        { yyerror("Illegal character"); }

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
