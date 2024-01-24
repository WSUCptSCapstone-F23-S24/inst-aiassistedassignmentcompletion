#ifndef _MAIN_H_
#define _MAIN_H_

#include "customGetopt.h"
#include "node.h"
#include "symbolTable.h"

extern FILE * yyin;
extern int optind;

Node * AST;

int errCount;
int wrnCount;

#endif
