%{
    #include <stdio.h>
    #include <string.h>
    #include "parser.tab.h"  // Include Bison generated header
    #include "scanType.h"

    int line_num = 1;

    int yyparse(void);

    YYSTYPE createToken(int class, int val, char* lexeme) {
        YYSTYPE token;
        token.tok.tokenClass = class;
        token.tok.numericVal = val;
        token.tok.lexeme = strdup(lexeme);
        token.tok.lineNo = line_num;
        return token;
    }
%}

%%

\n                  { line_num++; }
[ \t\r]             ; // Ignoring whitespace
"/*"                { char c, prev = 0; while((c=input()) != 0) { if(prev == '*' && c == '/') break; if(c == '\n') line_num++; prev = c; } }
"//".*\n            { line_num++; }
\"(\\.|[^\\"])*\"   { yylval = createToken(STRINGCONST, 0, yytext); return STRINGCONST; }
\'(\\.|[^\\'])*\'   { yylval = createToken(CHARCONST, (int)yytext[1], yytext); return CHARCONST; }
"true"|"false"      { yylval = createToken(yytext[0] == 't' ? TRUE : FALSE, yytext[0] == 't' ? 1 : 0, yytext); return yytext[0] == 't' ? TRUE : FALSE; }
"int"|"bool"|"char"|"void"|"static" { yylval = createToken(ID, 0, yytext); return ID; }
"if"|"else"|"while"|"for"|"return"|"break" { yylval = createToken(ID, 0, yytext); return ID; }
[0-9]+              { yylval = createToken(NUMCONST, atoi(yytext), yytext); return NUMCONST; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval = createToken(ID, 0, yytext); return ID; }
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return TIMES; }
"/"                 { return DIVIDE; }
"&&"                { return AND; }
"||"                { return OR; }
"!"                 { return NOT; }
"=="                { return EQ; }
"!="                { return NE; }
"<"                 { return LT; }
"<="                { return LE; }
">"                 { return GT; }
">="                { return GE; }
"="                 { return ASSIGN; }
";"                 { return SEMI; }
","                 { return COMMA; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }
"{"                 { return LBRACE; }
"}"                 { return RBRACE; }
"["                 { return LBRACK; }
"]"                 { return RBRACK; }
"++"                { return PLUSPLUS; }
"--"                { return MINUSMINUS; }

%%

int yywrap() {
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Could not open file %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }

    yyparse();

    return 0;
}
