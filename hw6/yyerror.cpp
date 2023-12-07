#include "yyerror.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>

static int split(char *s, char *strs[], char breakchar)
{
    int num;
    
    strs[0] = s;
    num = 1;
    
    for(char *p = s; *p; p++) 
    {
        if (*p==breakchar) 
        {
            strs[num++] = p+1;
            *p = '\0';
        }
    }
    
    strs[num] = NULL;
    
    return num;
}

static void trim(char *s)
{
    s[strlen(s)-1] = '\0';
}

static std::map<std::string , char* > niceTokenNameMap;

void initErrorProcessing() 
{
    niceTokenNameMap["ADDASGN"] = (char *)"\"+=\"";
    niceTokenNameMap["AND"] = (char *)"\"and\"";
    niceTokenNameMap["ASGN"] = (char *)"\"<=\"";
    niceTokenNameMap["BEGN"] = (char *)"\"begin\"";
    niceTokenNameMap["BOOL"] = (char *)"\"bool\"";
    niceTokenNameMap["BOOLCONST"] = (char *)"Boolean constant";
    niceTokenNameMap["BREAK"] = (char *)"\"break\"";
    niceTokenNameMap["BY"] = (char *)"\"step\"";
    niceTokenNameMap["CHAR"] = (char *)"\"char\"";
    niceTokenNameMap["CHARCONST"] = (char *)"character constant";
    niceTokenNameMap["DEC"] = (char *)"\"--\"";
    niceTokenNameMap["DIVASS"] = (char *)"\"/=\"";
    niceTokenNameMap["DO"] = (char *)"\"do\"";
    niceTokenNameMap["ELSE"] = (char *)"\"else\"";
    niceTokenNameMap["FINISH"] = (char *)"\"end\"";
    niceTokenNameMap["FOR"] = (char *)"\"for\"";
    niceTokenNameMap["GEQ"] = (char *)"\"!<\"";
    niceTokenNameMap["ID"] = (char *)"identifier";
    niceTokenNameMap["IF"] = (char *)"\"if\"";
    niceTokenNameMap["INC"] = (char *)"\"++\"";
    niceTokenNameMap["INT"] = (char *)"\"int\"";
    niceTokenNameMap["LEQ"] = (char *)"\"!>\"";
    niceTokenNameMap["MULASS"] = (char *)"\"*=\"";
    niceTokenNameMap["NEQ"] = (char *)"\"!=\"";
    niceTokenNameMap["NOT"] = (char *)"\"not\"";
    niceTokenNameMap["NUMCONST"] = (char *)"numeric constant";
    niceTokenNameMap["OR"] = (char *)"\"or\"";
    niceTokenNameMap["RETURN"] = (char *)"\"return\"";
    niceTokenNameMap["STATIC"] = (char *)"\"static\"";
    niceTokenNameMap["STRINGCONST"] = (char *)"string constant";
    niceTokenNameMap["SUBASS"] = (char *)"\"-=\"";
    niceTokenNameMap["THEN"] = (char *)"\"then\"";
    niceTokenNameMap["TO"] = (char *)"\"..\"";
    niceTokenNameMap["WHILE"] = (char *)"\"while\"";
    niceTokenNameMap["SEMICOLON"] = (char *)"\';\'";
    niceTokenNameMap["COLON"] = (char *)"\':\'";
    niceTokenNameMap["COMMA"] = (char *)"\',\'";
    niceTokenNameMap["OPAREN"] = (char *)"\'(\'";
    niceTokenNameMap["CPAREN"] = (char *)"\')\'";
    niceTokenNameMap["OBRACKET"] = (char *)"\'[\'";
    niceTokenNameMap["CBRACKET"] = (char *)"\']\'";
    niceTokenNameMap["MOD"] = (char *)"\'%\'";
    niceTokenNameMap["LESS"] = (char *)"\'<\'";
    niceTokenNameMap["GREAT"] = (char *)"\'>\'";
    niceTokenNameMap["EQUAL"] = (char *)"\'=\'";
    niceTokenNameMap["PLUS"] = (char *)"\'+\'";
    niceTokenNameMap["MINUS"] = (char *)"\'-\'";
    niceTokenNameMap["MULT"] = (char *)"\'*\'";
    niceTokenNameMap["DIV"] = (char *)"\'/\'";
    niceTokenNameMap["QUESTION"] = (char *)"\'?\'";
    niceTokenNameMap["$end"] = (char *)"end of input";
}

static char* niceTokenStr(char* tokenName) 
{
    if (tokenName[0] == '\'') 
    {
        return tokenName;
    }

    if (niceTokenNameMap.find(tokenName) == niceTokenNameMap.end()) 
    {
        printf("ERROR(SYSTEM): niceTokenStr fails to find string '%s'\n", tokenName); 
        fflush(stdout);
        exit(1);
    }
    
    return niceTokenNameMap[tokenName];
}

static bool elaborate(char* s)
{
    return (strstr(s, "constant") || strstr(s, "identifier"));
}

static void tinySort(char* base[], int num, int step, bool up)
{
    for (int i=step; i<num; i+=step) 
    {
        for (int j=0; j<i; j+=step) 
        {
            if (up ^ (strcmp(base[i], base[j])>0)) 
            {
                char *tmp;
                tmp = base[i]; 
                base[i] = base[j]; 
                base[j] = tmp;
            }
        }
    }
}
  
void yyerror(const char* msg)
{
    char *space;
    char *strs[100];
    int numstrs;
    space = strdup(msg);
    numstrs = split(space, strs, ' ');
    if (numstrs>4) trim(strs[3]);
    for (int i=3; i<numstrs; i+=2) 
    {
        strs[i] = niceTokenStr(strs[i]);
    }
    printf("ERROR(%d): Syntax error, unexpected %s", line, strs[3]);
    if (elaborate(strs[3])) 
    {
        if (yytext[0]=='\'' || yytext[0]=='"') printf(" %s", yytext); 
        else printf(" \"%s\"", yytext);
    }

    if (numstrs>4) printf(",");
    tinySort(strs+5, numstrs-5, 2, true); 
    for (int i=4; i<numstrs; i++) 
    {
        printf(" %s", strs[i]);
    }
    printf(".\n");
    fflush(stdout);

    numErrors++;

    free(space);
}