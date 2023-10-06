#ifndef _SCANTYPE_H_
#define _SCANTYPE_H_

enum {
    NUM = 258,
    BOOLCONST,
    CHAR,
    ID
};

struct TokenData {
    int tokenclass;
    int linenum;
    char* tokenstr;
    char cvalue;
    int nvalue;
    char* svalue;
};

#endif