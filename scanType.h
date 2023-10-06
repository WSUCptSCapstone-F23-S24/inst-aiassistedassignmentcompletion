#ifndef _SCANTYPE_H_
#define _SCANTYPE_H_

// Define token enumerators
enum {
    NUM = 258,
    BOOLCONST,
    CHAR,
    ID
};

// Define a struct to hold token data
struct TokenData {
    int tokenclass; // Token class
    int linenum;    // Line number where found
    char* tokenstr; // String representation of the token
    char cvalue;    // Character value (for CHAR tokens)
    int nvalue;     // Numeric value or Boolean value
    char* svalue;   // String value (e.g., for ID tokens)
};

#endif
