%{
#include "scanType.h"
#include "node.h"
#include "parser.tab.h"
#include <ctype.h>

static int lineNumber = 1;

int line;
char *lastToken;

extern int NUM_ERRORS;
extern int NUM_WARNINGS;


static void convertEscapeStr(char *inBuff, char *outBuff)
{
    if(inBuff[0] != '"')
    {
        printf("INTERNAL SCANNING ERROR: A non double quoted string was allowed as a token\n");
        exit(-1);
    }

    int j = 0;
    size_t inBuffLen = strlen(inBuff);
    for(size_t i = 1; i < inBuffLen; i++)
    {

        if(inBuff[i] == '"')
        {
            outBuff[j] = '\0';
            return;
        }

        if(inBuff[i] != '\\')
        {
            outBuff[j++] = inBuff[i];
            continue;
        }

        else
        {
            i++;
            if(inBuff[i] == 'n')
            {
                outBuff[j++] = '\n';
            }
            else if(inBuff[i] == '0')
            {
                outBuff[j++] = '\0';
            }
            else
            {
                outBuff[j++] = inBuff[i];
            }
        }
    }

    for(size_t i = 0; i < inBuffLen; i++)
    {
        printf("ERROR(%d): Invalid or misplaced input character: '%c'. Character Ignored.\n",
        lineNumber,
        inBuff[i]);

         NUM_ERRORS++;
    }
}

static void convertEscapeChar(char *inBuff, char *outBuff)
{
    if(inBuff[0] != '\'')
    {
        printf("INTERNAL SCANNING ERROR: A non quoted character was allowed as a token\n");
        exit(-1);
    }

    int j = 0;
    size_t i = 0;
    size_t inBuffLen = strlen(inBuff);
    for(i = 1; i < inBuffLen; i++)
    {

        if(inBuff[i] == '\'')
        {
            outBuff[j] = '\0';
            return;
        }

        if(inBuff[i] != '\\')
        {
            outBuff[j++] = inBuff[i];
            continue;
        }

        else
        {
            i++;
            if(inBuff[i] == 'n')
            {
                outBuff[j++] = '\n';
            }
            else if(inBuff[i] == '0')
            {
                outBuff[j++] = '\0';
            }
            else
            {
                outBuff[j++] = inBuff[i];
            }
        }
    }


    printf("INTERNAL SCANNING ERROR: inBuff Character is not closed by a \'\n");
    printf("I[%d] j[%d] outBuff[%s]\n",(int)i,j,outBuff);
    exit(-1);
}

static int setValue(int lineNumber, int tokenClass, char *svalue)
{
    lastToken = svalue;
    line = lineNumber;

    yylval.tokenData = new TokenData;
    yylval.tokenData->tokenClass = tokenClass;
    yylval.tokenData->lineNum = lineNumber;
    yylval.tokenData->tokenStr = strdup(svalue);

    if (tokenClass == NUMCONST)
    {

        yylval.tokenData->nValue = atof(svalue);
    }
    else if (tokenClass == CHARCONST)
    {
        if( ((int)strlen(svalue) -2) != 1)
        {
            if(svalue[1] != '\\')
            {
                printf("WARNING(%d): character is %d characters long and not a single character: '%s'.  The first char will be used.\n",
                    lineNumber,
                    ((int)strlen(svalue) -2),
                    svalue);

                NUM_WARNINGS++;
            }
        }
        yylval.tokenData->sValue = strdup(svalue);
        convertEscapeChar(yylval.tokenData->sValue,yylval.tokenData->sValue);
        yylval.tokenData->cValue = yylval.tokenData->sValue[0];
    }
    else if (tokenClass == STRINGCONST)
    {
        yylval.tokenData->sValue = strdup(svalue);
        convertEscapeStr(yylval.tokenData->sValue,yylval.tokenData->sValue);
    }
    else if (tokenClass == TRUE)
    {
        yylval.tokenData->nValue = 1;
    }
    else if (tokenClass == FALSE)
    {
        yylval.tokenData->nValue = 0;
    }

    return tokenClass;
}





%}

whitespace [ \t\r\f]

numbers [0-9]
letterDig [a-zA-Z]|[0-9]
letters [a-zA-Z]
charconst '[^'\n]*'
escapedCharConst '(\\.|[^\\'\n])*'
stringConst \"[^\"\n]*\"
escapedStringConst \"(\\.|[^\\\"\n])*\"
comment \/\/(.)*
ID [a-zA-Z][a-zA-Z0-9]*

%option noyywrap
%option nounput
%%
int                       {return setValue(lineNumber,INT,yytext);}
char                      {return setValue(lineNumber,CHAR,yytext);}
if                        {return setValue(lineNumber,IF,yytext);}
then                      {return setValue(lineNumber,THEN,yytext);}
else                      {return setValue(lineNumber,ELSE,yytext);}
while                     {return setValue(lineNumber,WHILE,yytext);}
do                        {return setValue(lineNumber,DO,yytext);}
for                       {return setValue(lineNumber,FOR,yytext);}
to                        {return setValue(lineNumber,TO,yytext);}
by                        {return setValue(lineNumber,BY,yytext);}
return                    {return setValue(lineNumber,RETURN,yytext);}
break                     {return setValue(lineNumber,BREAK,yytext);}
static                    {return setValue(lineNumber,STATIC,yytext);}
not                       {return setValue(lineNumber,NOT,yytext);}
and                       {return setValue(lineNumber,AND,yytext);}
or                        {return setValue(lineNumber,OR,yytext);}
bool                      {return setValue(lineNumber,BOOL,yytext);}
true                      {return setValue(lineNumber,TRUE,yytext);}
false                     {return setValue(lineNumber,FALSE,yytext);}

\{                        {return setValue(lineNumber,OPEN_BRACE,yytext);}
\}                        {return setValue(lineNumber,CLOSE_BRACE,yytext);}
\(                        {return setValue(lineNumber,OPEN_PAREN,yytext);}
\)                        {return setValue(lineNumber,CLOSE_PAREN,yytext);}
\,                        {return setValue(lineNumber,COMMA,yytext);}
\:                        {return setValue(lineNumber,COLON,yytext);}
\=                        {return setValue(lineNumber,ASS,yytext);}
\-                        {return setValue(lineNumber,MINUS,yytext);}
\/                        {return setValue(lineNumber,DIV,yytext);}
\*                        {return setValue(lineNumber,MULT,yytext);}
\%                        {return setValue(lineNumber,MOD,yytext);}
\+\=                      {return setValue(lineNumber,ADDASS,yytext);}
\-\=                      {return setValue(lineNumber,SUBASS,yytext);}
\*\=                      {return setValue(lineNumber,MULASS,yytext);}
\/\=                      {return setValue(lineNumber,DIVASS,yytext);}
\=\=                      {return setValue(lineNumber,EQ,yytext);}
\[                        {return setValue(lineNumber,OPEN_BRACK,yytext);}
\]                        {return setValue(lineNumber,CLOSE_BRACK,yytext);}
\>                        {return setValue(lineNumber,GREATER,yytext);}
\<                        {return setValue(lineNumber,LESS,yytext);}
\-\-                      {return setValue(lineNumber,DEC,yytext);}
\+\+                      {return setValue(lineNumber,INC,yytext);}
\!\=                      {return setValue(lineNumber,NEQ,yytext);}
\+                        {return setValue(lineNumber,PLUS,yytext);}
\:\<\:                    {return setValue(lineNumber,MIN,yytext);}
\:\>\:                    {return setValue(lineNumber,MAX,yytext);}
\?                        {return setValue(lineNumber,QUESTION,yytext);}
\>\=                      {return setValue(lineNumber,GEQ,yytext);}
\<\=                      {return setValue(lineNumber,LEQ,yytext);}
\;                        {return setValue(lineNumber,SEMI,yytext);}


[\n]                      {lineNumber++;}
{whitespace}+             {;}
{comment}                 {;}
{stringConst}             {return setValue(lineNumber,STRINGCONST,yytext);}
{escapedStringConst}      {return setValue(lineNumber,STRINGCONST,yytext);}
{charconst}               {if(((int)strlen(yytext)-2)!=0) return setValue(lineNumber,CHARCONST,yytext);else printf("ERROR(%d): Empty character ''.  Characters ignored.\n",
                                                                                                                lineNumber);
                                                                                                                NUM_ERRORS++;}
{escapedCharConst}        {return setValue(lineNumber,CHARCONST,yytext);}
{numbers}+                {return setValue(lineNumber,NUMCONST,yytext);}
{ID}                      {return setValue(lineNumber,ID,yytext);}

.                         {printf("ERROR(%d): Invalid or misplaced input character: '%c'. Character Ignored.\n",lineNumber,yytext[0]); NUM_ERRORS++;}

<INITIAL><<EOF>>         {line = lineNumber; return 0;}
%%
