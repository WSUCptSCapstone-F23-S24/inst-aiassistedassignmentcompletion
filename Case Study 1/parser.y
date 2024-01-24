%{
// Evan and Adam

#include "scanType.h"  // TokenData Type
#include <stdio.h>

double variables[26];    

extern int yylex();
extern FILE *yyin;
extern int line;
extern int numErrors;

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
    printf("ERROR(%d): %s\n", line, msg);
    numErrors++;
}

%}

%union {
    TokenData *tokenData;
}

%token <tokenData> BOOLCONST ID NUMCONST CHARCONST STRINGCONST

%%

tokenlist     : tokenlist token
              | token
              ;

token         : constant
              | mulop
              | sumop
              | ops

sumop         : '+'
              | '-'

mulop         : '*'
              | '/'
              | '%'

ops           : '<'
              | '>'
              | '('
              | ')'
              | '['
              | ']'
              | ':'
              | ';'
              | ','
              | '?'
              | '='

constant      : BOOLCONST
              | ID
              | NUMCONST
              | CHARCONST
              | STRINGCONST



%%
extern int yydebug;
int main(int argc, char *argv[])
{
    if (argc > 1) {
        if ((yyin = fopen(argv[1], "r"))) {
            // Enter if we successfully opened the file
        }
        else {
            // Enter if we failed to open the file
            printf("ERROR: Failed to open '%s'\n", argv[1]);
            exit(1);
        }
    }

    // Make all 26 letter variables 0.0
    for (int i = 0; i < 26; i++) variables[i] = 0.0;

    // Perform the parsing
    numErrors = 0;
    yyparse();
    return 0;
}
