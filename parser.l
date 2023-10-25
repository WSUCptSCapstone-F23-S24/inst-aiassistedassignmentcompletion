%{
    #include <stdio.h>
    #include <string.h>
    int line_num = 1;

    typedef struct {
        int tokenClass;
        int numericVal;
        char* lexeme;
        int lineNo;
    } TOKEN;

    TOKEN* yylval;

    TOKEN* createToken(int class, int val, char* lexeme) {
        TOKEN* token = (TOKEN*)malloc(sizeof(TOKEN));
        token->tokenClass = class;
        token->numericVal = val;
        token->lexeme = strdup(lexeme);
        token->lineNo = line_num;
        return token;
    }

    #define NUMBER 1
    #define ID 2
    #define BOOLCONST 3
%}

%%

\n                  { line_num++; }
[ \t\r]             ; // Ignoring whitespace
"/*"                { char c; while((c=input()) != 0) { if(c == '*') { if(input() == '/') break; } if(c == '\n') line_num++; } }
"//".*\n            { line_num++; }
"true"              { yylval = createToken(BOOLCONST, 1, yytext); return BOOLCONST; }
"false"             { yylval = createToken(BOOLCONST, 0, yytext); return BOOLCONST; }
[0-9]+              { yylval = createToken(NUMBER, atoi(yytext), yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z_0-9]* { yylval = createToken(ID, 0, yytext); return ID; }
'[^']'              { yylval = createToken(NUMBER, (int)yytext[1], yytext); return NUMBER; }
''                  { fprintf(stderr, "Error at line %d: Empty character constant\n", line_num); }
'[^']+'             { fprintf(stderr, "Warning at line %d: Character constant '%s' has multiple characters, only the first one will be used\n", line_num, yytext); yylval = createToken(NUMBER, (int)yytext[1], yytext); return NUMBER; }
.                   { fprintf(stderr, "Error at line %d: Illegal character '%c'\n", line_num, yytext[0]); }

%%

void printToken(TOKEN* token) {
    if (!token) return;

    switch (token->tokenClass) {
        case NUMBER:
            printf("Token: NUMBER, Lexeme: %s, Numeric Value: %d, Line: %d\n", token->lexeme, token->numericVal, token->lineNo);
            break;
        case ID:
            printf("Token: ID, Lexeme: %s, Line: %d\n", token->lexeme, token->lineNo);
            break;
        case BOOLCONST:
            printf("Token: BOOLCONST, Lexeme: %s, Numeric Value: %d, Line: %d\n", token->lexeme, token->numericVal, token->lineNo);
            break;
        default:
            printf("Unknown token class %d\n", token->tokenClass);
            break;
    }

    free(token->lexeme); // Free the dynamically allocated lexeme string
    free(token); // Free the token itself
}

int main() {
    TOKEN* token;
    int tokenType;
    while ((tokenType = yylex())) {
        token = yylval;  // Assign yylval to token directly
        printToken(token);
    }
    return 0;
}
