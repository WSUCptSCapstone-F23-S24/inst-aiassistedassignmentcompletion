#ifndef _YYERROR_H_
#define _YYERROR_H_

#define YYERROR_VERBOSE

extern int line;        extern char *lastToken; extern int ERROR_COUNT;
void initErrorProcessing();    void yyerror(const char *msg);
#endif