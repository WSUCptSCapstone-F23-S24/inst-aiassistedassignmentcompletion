#ifndef SCANTYPE_H
#define SCANTYPE_H

// Define token classes
#define BOOLCONST 1
#define NUMBER 2
#define IDENTIFIER 3
#define FLOAT 4
#define PLUS 5
#define MINUS 6
// Define other token classes as needed...

// Define the token data structure
struct TokenData {
    int tokenclass;   // Token class
    int linenum;      // Line where found
    char tokenstr;   // Actual string read
    char cvalue;      // Character value
    int nvalue;       // Numeric value or Boolean value
    charsvalue;     // String value, e.g., an identifier
};

#endif