#ifndef _SCANTYPE_H_
#define _SCANTYPE_H_

struct TokenData {
    int tokenclass;
    int linenum;
    char* tokenstr;
    char cvalue;
    int nvalue;
    char* svalue;
};

enum {
    NUM,
    BOOLCONST,
    CHAR,
    ID
};

#endif
