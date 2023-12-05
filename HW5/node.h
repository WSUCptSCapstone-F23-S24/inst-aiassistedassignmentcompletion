#ifndef _NODE_H
#define _NODE_H
#include "scanType.h"
#include <cstddef>

#define MAXCHILDREN 3

typedef int OpKind;

enum UnionType
{
    cvalue,
    value,
    string
};

enum NodeKind
{
    DeclK,
    StmtK,
    ExpK
};

enum DeclKind
{
    VarK,
    FuncK,
    ParamK
};

enum StmtKind
{
    NullK,
    IfK,
    WhileK,
    ForK,
    CompoundK,
    ReturnK,
    BreakK,
    RangeK
};

enum ExpKind
{
    OpK,
    ConstantK,
    IdK,
    AssignK,
    InitK,
    CallK
};

typedef enum
{
    Void,
    Integer,
    Boolean,
    Char,
    CharInt,
    Equal,
    UndefinedType
}ExpType;

enum VarKind
{
    None,
    Local,
    Global,
    Parameter,
    LocalStatic
};

typedef struct treeNode
{
    struct treeNode *parent;
    struct treeNode *child[MAXCHILDREN];
    struct treeNode *sibling;


    int lineno;
    NodeKind nodekind;
    union
    {
        DeclKind decl;
        StmtKind stmt;
        ExpKind exp;
    } subkind;

    union
    {
        int value;
        unsigned char cvalue;
        char *string;
        char *name;
    } attr;
    UnionType unionType;
    bool isRangeKBy;
    bool isRangeK;
    int depth;
    bool isFunc;
    bool isInitErrorThrown;
    OpKind op;
    bool isOp;
    bool attrSet;
    ExpType expType;
    bool isArray;
    int arraySize;
    bool isStatic;
    bool isUsed;
    bool isInit;
    char* tokenStr
    bool undeclared
    bool isConst

} TreeNode;

TreeNode *newDeclNode(DeclKind kind,
                      ExpType type,
                      TokenData *token = NULL,
                      TreeNode *c0 = NULL,
                      TreeNode *c1 = NULL,
                      TreeNode *c2 = NULL);

TreeNode *newStmtNode(StmtKind kind,
                      TokenData *token,
                      TreeNode *c0 = NULL,
                      TreeNode *c1 = NULL,
                      TreeNode *c2 = NULL);

TreeNode *newExpNode(ExpKind kind,
                     TokenData *token,
                     TreeNode *c0 = NULL,
                     TreeNode *c1 = NULL,
                     TreeNode *c2 = NULL);

void printTree(TreeNode *node,int indentLevel);
void printTypedTree(TreeNode *node,int indentLevel);
void dumpNode(TreeNode *node);
TreeNode *addSibling(TreeNode *t, TreeNode *s);
void setType(TreeNode *t, ExpType type, bool isStatic);
void convertExpTypeToString(ExpType type, char *string);
void printSpaces(int indentLevel);

#endif