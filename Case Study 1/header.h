#ifndef SCANTYPE_H
#define SCANTYPE_H

// Define the token data structure
struct TokenData {
    int tokenclass;   // Token class
    int linenum;      // Line where found
    char tokenstr;   // Actual string read
    char cvalue;      // Character value
    int nvalue;       // Numeric value or Boolean value
    char * svalue;     // String value, e.g., an identifier
};

#endif
