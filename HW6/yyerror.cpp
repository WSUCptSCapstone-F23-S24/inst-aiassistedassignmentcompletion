#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include "yyerror.h"


static int split(char *s, char *strs[], char breakchar)
{
    int num;

    strs[0] = s;
    num = 1;
    for (char *p = s; *p; p++)
    {
        if (*p == breakchar)
        {
            strs[num++] = p + 1;
            *p = '\0';
        }
    }
    strs[num] = NULL;

    return num;
}

static void trim(char *s)
{
    s[strlen(s) - 1] = '\0';
}
static std::map<std::string, char *> niceTokenNameMap;
void initErrorProcessing()
{

    niceTokenNameMap["ADDASS"] = (char *)"\"+=\"";
    niceTokenNameMap["AND"] = (char *)"\"and\"";
    niceTokenNameMap["BOOL"] = (char *)"\"bool\"";
    niceTokenNameMap["BOOLCONST"] = (char *)"Boolean constant";
    niceTokenNameMap["BREAK"] = (char *)"\"break\"";
    niceTokenNameMap["BY"] = (char *)"\"by\"";
    niceTokenNameMap["CHAR"] = (char *)"\"char\"";
    niceTokenNameMap["CHARCONST"] = (char *)"character constant";
    niceTokenNameMap["CHSIGN"] = (char *)"-";
    niceTokenNameMap["DEC"] = (char *)"\"--\"";
    niceTokenNameMap["DIVASS"] = (char *)"\"/=\"";
    niceTokenNameMap["DO"] = (char *)"\"do\"";
    niceTokenNameMap["ELSE"] = (char *)"\"else\"";
    niceTokenNameMap["EQ"] = (char *)"\"==\"";
    niceTokenNameMap["FOR"] = (char *)"\"for\"";
    niceTokenNameMap["GEQ"] = (char *)"\">=\"";
    niceTokenNameMap["ID"] = (char *)"identifier";
    niceTokenNameMap["IF"] = (char *)"\"if\"";
    niceTokenNameMap["INC"] = (char *)"\"++\"";
    niceTokenNameMap["INT"] = (char *)"\"int\"";
    niceTokenNameMap["LEQ"] = (char *)"\"<=\"";
    niceTokenNameMap["MAX"] = (char *)":>:";
    niceTokenNameMap["MIN"] = (char *)":<:";
    niceTokenNameMap["MULASS"] = (char *)"\"*=\"";
    niceTokenNameMap["NEQ"] = (char *)"\"!=\"";
    niceTokenNameMap["NOT"] = (char *)"\"not\"";
    niceTokenNameMap["NUMCONST"] = (char *)"numeric constant";
    niceTokenNameMap["OR"] = (char *)"\"or\"";
    niceTokenNameMap["RETURN"] = (char *)"\"return\"";
    niceTokenNameMap["SIZEOF"] = (char *)"\"*\"";
    niceTokenNameMap["STATIC"] = (char *)"\"static\"";
    niceTokenNameMap["STRINGCONST"] = (char *)"string constant";
    niceTokenNameMap["SUBASS"] = (char *)"\"-=\"";
    niceTokenNameMap["THEN"] = (char *)"\"then\"";
    niceTokenNameMap["TO"] = (char *)"\"to\"";
    niceTokenNameMap["WHILE"] = (char *)"\"while\"";
    niceTokenNameMap["SEMI"] = (char *)"\';'";
    niceTokenNameMap["GREATER"] = (char *)"'>'";
    niceTokenNameMap["ASS"] = (char *)"'='";
    niceTokenNameMap["OPEN_PAREN"] = (char *)"'('";
    niceTokenNameMap["CLOSE_PAREN"] = (char *)"')'";
    niceTokenNameMap["OPEN_BRACE"] = (char *)"'{'";
    niceTokenNameMap["CLOSE_BRACE"] = (char *)"'}'";
    niceTokenNameMap["OPEN_BRACK"] = (char *)"'['";
    niceTokenNameMap["CLOSE_BRACK"] = (char *)"']'";
    niceTokenNameMap["COMMA"] = (char *)"','";
    niceTokenNameMap["MOD"] = (char *)"'%'";
    niceTokenNameMap["DIV"] = (char *)"'/'";
    niceTokenNameMap["TRUE"] = (char *)"Boolean constant";
    niceTokenNameMap["FALSE"] = (char *)"Boolean constant";
    niceTokenNameMap["COLON"] = (char *)"':'";
    niceTokenNameMap["PLUS"] = (char *)"'+'";
    niceTokenNameMap["MINUS"] = (char *)"'-'";
    niceTokenNameMap["MULT"] = (char *)"'*'";
    niceTokenNameMap["$end"] = (char *)"end of input";
}

static char *niceTokenStr(char *tokenName)
{
    if (tokenName[0] == '\'')
        return tokenName;
    if (niceTokenNameMap.find(tokenName) == niceTokenNameMap.end())
    {
        printf("ERROR(SYSTEM): niceTokenStr fails to find string '%s'\n", tokenName);
        fflush(stdout);
        exit(1);
    }
    return niceTokenNameMap[tokenName];
}

// Is this a message that we need to elaborate with the current parsed token.
// This elaboration is some what of a crap shoot since the token could
// be already overwritten with a look ahead token.   But probably not.
static bool elaborate(char *s)
{
    return (strstr(s, "constant") || strstr(s, "identifier"));
}

// A tiny sort routine for SMALL NUMBERS of
// of char * elements.  num is the total length
// of the array but only every step elements will
// be sorted.  The "up" flag is direction of sort.
// For example:
//    tinySort(str, i, 2, direction);      // sorts even number elements in array
//    tinySort(str+1, i-1, 2, direction);  // sorts odd number elements in array
//    tinySort(str, i, 1, direction);      // sorts all elements in array
//
static void tinySort(char *base[], int num, int step, bool up)
{
    for (int i = step; i < num; i += step)
    {
        for (int j = 0; j < i; j += step)
        {
            if (up ^ (strcmp(base[i], base[j]) > 0))
            {
                char *tmp;
                tmp = base[i];
                base[i] = base[j];
                base[j] = tmp;
            }
        }
    }
}

// This is the yyerror called by the bison parser for errors.
// It only does errors and not warnings.
void yyerror(const char *msg)
{
    char *space;
    char *strs[100];
    int numstrs;
    // make a copy of msg string
    if (strcmp(msg, "syntax error, unexpected end of file, expecting ID or INT or BOOL or CHAR") == 0)
    {
        printf("ERROR(%d): Syntax error, unexpected end of input, expecting \"bool\" or \"char\" or \"int\" or identifier.\n",
               line);
        ERROR_COUNT++;
    }
    else
    {
        space = strdup(msg);

        // split out components
        numstrs = split(space, strs, ' ');

        if (numstrs > 4)
            trim(strs[3]);

        // translate components
        for (int i = 3; i < numstrs; i += 2)
        {
            strs[i] = niceTokenStr(strs[i]);
        }

        // print components
        printf("ERROR(%d): Syntax error, unexpected %s", line, strs[3]);
        if (elaborate(strs[3]))
        {
            if (lastToken[0] == '\'' || lastToken[0] == '"')
                printf(" %s", lastToken);
            else
                printf(" \"%s\"", lastToken);
        }

        if (numstrs > 4)
            printf(",");

        // print sorted list of expected
        tinySort(strs + 5, numstrs - 5, 2, true);
        for (int i = 4; i < numstrs; i++)
        {
            printf(" %s", strs[i]);
        }

        printf(".\n");
        fflush(stdout); // force a dump of the error

        ERROR_COUNT++; // count the number of errors

        free(space);
    }
}