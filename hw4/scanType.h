#ifndef SCANTYPE_H
#define SCANTYPE_H

struct TokenData
{
    
    char *tokenStrprint; 
    int idIndex;
    int lineno;         // what line did this token occur on?
    char *tokenstr;    
    char cvalue;         
    int nvalue;          
    char *stringvalue;       
    int strlength;

};

#endif