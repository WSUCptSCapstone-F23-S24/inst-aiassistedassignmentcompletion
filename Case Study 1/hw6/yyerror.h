#ifndef _YYERROR_H_
#define _YYERROR_H_

#define YYERROR_VERBOSE

extern int line;
extern char* yytext;
extern int numErrors;

void initErrorProcessing();
void yyerror(const char* msg);
#endif