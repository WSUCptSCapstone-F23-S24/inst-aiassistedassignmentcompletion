%{
#include "scanType.h"  // Include the token data structure
%}

%option noyywrap

%{
int line_number = 1;  // Initialize line number
%}

%%

[ \t\n]+            ; // Ignore whitespace and newlines

"true"              { yylval.svalue = strdup(yytext); return BOOLCONST; }
"false"             { yylval.svalue = strdup(yytext); return BOOLCONST; }
[0-9]+              { yylval.nvalue = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.svalue = strdup(yytext); return IDENTIFIER; }
'.'                 { return DOT; }
'+'                 { return PLUS; }
'-'                 { return MINUS; }
'*'                 { return STAR; }
'/'                 { return SLASH; }
'%'                 { return PERCENT; }
'('                 { return LPAREN; }
')'                 { return RPAREN; }
'{'                 { return LBRACE; }
'}'                 { return RBRACE; }
'['                 { return LBRACKET; }
']'                 { return RBRACKET; }
'<'                 { return LESS; }
'>'                 { return GREATER; }
'='                 { return EQUAL; }
','                 { return COMMA; }
';'                 { return SEMICOLON; }
'!'                 { return EXCLAMATION; }
'&'                 { return AMPERSAND; }
'^'                 { return CARET; }
'|'                 { return PIPE; }
'?'                 { return QUESTION; }
':'                 { return COLON; }
'.'[0-9]+           { yylval.svalue = strdup(yytext); return FLOAT; }
'.'[0-9]+'e'[-+]?[0-9]+' { yylval.svalue = strdup(yytext); return FLOAT; }

'/*'([^*]|'+'[^/*])*'*/'  ; // Ignore comments

.                   { fprintf(stderr, "Error: Illegal character '%c' at line %d\n", yytext[0], line_number); }

\n                  { line_number++; }  // Increment line number for newline

%%

int main(int argc, char* argv[]) {
    if (argc > 1) {
        FILE* input_file = fopen(argv[1], "r");
        if (input_file == NULL) {
            fprintf(stderr, "Error: Unable to open input file\n");
            return 1;
        }
        yyin = input_file;
    }

    // Initialize the Flex scanner
    yylex();

    return 0;
}