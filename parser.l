%{
    #include <stdio.h>
    #include <string.h>
    #include "parser.tab.h"
    #include "scanType.h"

    int line_num = 1;

    YYSTYPE createToken(int class, int val, char* lexeme) {
        YYSTYPE token;
        token.tok.tokenClass = class;
        token.tok.numericVal = val;
        token.tok.lexeme = strdup(lexeme);
        token.tok.lineNo = line_num;
        return token;
    }
%}

%option noyywrap

%%

\n                  { line_num++; }
[ \t\r]             ; // Ignoring whitespace
"/*"                { char c; while((c=input()) != 0) { if(c == '*') { if(input() == '/') break; } if(c == '\n') line_num++; } }
"//".*\n            { line_num++; }
\"(\\.|[^\\"])*\"   { yylval = createToken(STRING, 0, yytext); return STRING; }
\'(\\.|[^\\'])*\'   { yylval = createToken(CHAR, (int)yytext[1], yytext); return CHAR; }
"true"              { yylval = createToken(BOOLCONST, 1, yytext); return BOOLCONST; }
"false"             { yylval = createToken(BOOLCONST, 0, yytext); return BOOLCONST; }
[0-9]+              { yylval = createToken(NUMBER, atoi(yytext), yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z_0-9]* { yylval = createToken(ID, 0, yytext); return ID; }
.                   { fprintf(stderr, "Error at line %d: Illegal character '%c'\n", line_num, yytext[0]); }

%%
