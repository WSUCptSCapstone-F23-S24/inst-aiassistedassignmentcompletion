#ifndef TREENODE_H
#define TREENODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "scanType.h"

#define MAXCHILDREN 3

typedef int OpKind;

typedef enum
{
    DeclK,
    StmtK,
    ExpK
} NodeKind;

typedef enum
{
    VarK,
    FuncK,
    ParamK
} DeclKind;

// Subkinds of Statements
typedef enum
{
    NullK,
    IfK,
    WhileK,
    ForK,
    CompoundK,
    ReturnK,
    BreakK,
    RangeK
} StmtKind;

// Subkinds of Expressions
typedef enum
{
    OpK,
    ConstantK,
    IdK,
    AssignK,
    InitK,
    CallK
} ExpKind;

typedef enum
{
    Void,
    Integer,
    Boolean,
    Char,
    CharInt,
    Equal,
    UndefinedType
} ExpType;

typedef enum
{
    None,
    Local,
    Global,
    Parameter,
    LocalStatic
} VarKind;

typedef struct treeNode
{
    struct treeNode *child[MAXCHILDREN]; // children of the node
    struct treeNode *sibling;            // siblings for the node

    int linenum;          // linenum relevant to this node
    NodeKind nodekind;    // type of this node
    TokenData *tokenData; // Token data for node

    union // subtype of type
    {
        DeclKind decl; // used when DeclK
        StmtKind stmt; // used when StmtK
        ExpKind exp;   // used when ExpK
    } subkind;

    union
    {
        OpKind op;
        int value;
        unsigned char cvalue;
        char *string;
        char *name;
    } attr;

    ExpType expType;
    bool isArray;
    bool isStatic;

} TreeNode;

// Functions
TreeNode *newDeclNode(DeclKind kind, TokenData *token);
TreeNode *newStmtNode(StmtKind kind, TokenData *token);
TreeNode *newExpNode(ExpKind kind, TokenData *token);
TreeNode *addSibling(TreeNode *t, TreeNode *s);

void printTree(TreeNode *t, int numSiblings);
void getExpType(ExpType t);
void printWhiteSpace(int WS);
void assignTyping(TreeNode *t, ExpType type);