#ifndef _SEMANTIC_H
#define _SEMANTIC_H

extern int ERROR_COUNT;
extern int WARNING_COUNT;

void checkTree(SymbolTable *symTab, TreeNode *node, int indent, bool supressScope, TreeNode *parent);
void checkTree2(SymbolTable *symTab, TreeNode *node, bool supressScope, TreeNode *parent);

#endif