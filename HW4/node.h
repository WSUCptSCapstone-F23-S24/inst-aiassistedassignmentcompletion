#ifndef _NODE_H
#define _NODE_H
#include "scanType.h"
#include <cstddef>

#define MAX_CHILDREN 3

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
    NodeKind nodekind;
    UnionType unionType;
    OpKind op;
    ExpType expType;

    struct treeNode *parent;
    struct treeNode *child[MAX_CHILDREN];
    struct treeNode *sibling;

    int lineno;
    int depth;
    int arraySize;
    int numParams;

    char* tokenStr;

    bool isRangeKBy;
    bool isRangeK;
    bool isFunc;
    bool isInitError;
    bool isOp;
    bool attrSet;
    bool isArray;
    bool isStatic;
    bool isUsed;
    bool isInit;
    bool undeclared;
    bool isConst;
    bool isIo;
    bool isParam;

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

TreeNode *addSibling(TreeNode *t, TreeNode *s);

void displayTree(TreeNode *node,int indent);
void displayTypedTree(TreeNode *node,int indent);
void dumpNode(TreeNode *node);
void setType(TreeNode *t, ExpType type, bool isStatic);
void exprToStr(ExpType type, char *string);
void printSpaces(int indent);
#endif