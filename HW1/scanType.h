#ifndef _SCANTYPE_H_
#define _SCANTYPE_H_

typedef struct
{
    int tokenClass;
    int numericVal;
    char *lexeme;
    int lineNo;
} TOKEN;

#endif // _SCANTYPE_H_
