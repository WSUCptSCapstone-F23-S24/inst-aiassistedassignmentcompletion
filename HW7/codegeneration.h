#ifndef _CODEGENERATION_H
#define _CODEGENERATION_H
#include "symbolTable.h"

void traverse(SymbolTable *symTab, TreeNode *node);
void processTreeNode(SymbolTable *symTab, TreeNode *node);
void gen_code(SymbolTable *symTab,TreeNode *tree);

#endif