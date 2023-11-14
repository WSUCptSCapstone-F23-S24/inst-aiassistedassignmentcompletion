#ifndef TREE_H
#define TREE_H

#include <cstddef>
#include <stdio.h>
#include <string>
#include "scanType.h"
#include "parser.tab.h"

#define MAXCHILDREN 3

class Node
{
public:
    Node *child[MAXCHILDREN];
    Node *sibling;
    int linenum;
    int depth;
    int index;
    bool isRoot;
    bool isChild;
    bool isConst;
    bool isArray;
    char *type;
    Node();
    void add(Node *);
    void addChild(int, Node *);
    void updateLoc();
    void printSelf();
    virtual void print();
};

class VarDecl : public Node
{
public:
    char *name;
    bool isFun;
    bool isStatic;
    bool isInited;
    int arrSize;
    VarDecl(TokenData *);
    VarDecl(TokenData *, TokenData *);
    void setType(char *, bool);
    void init();
    virtual void print();
};

class FunDecl : public VarDecl
{
public:
    FunDecl(TokenData *, Node *, Node *);
    FunDecl(TokenData *, TokenData *, Node *, Node *);
    virtual void print();
};

class Parm : public VarDecl
{
public:
    Parm(TokenData *, bool arr = false);
    virtual void print();
};

class CompoundStmt : public Node
{
public:
    CompoundStmt(int, Node *, Node *);
    virtual void print();
};

class IfStmt : public Node
{
public:
    IfStmt(int, Node *, Node *);
    IfStmt(int, Node *, Node *, Node *);
    virtual void print();
};

class WhileStmt : public Node
{
public:
    WhileStmt(int, Node *, Node *);
    virtual void print();
};

class ForStmt : public Node
{
public:
    ForStmt(int, TokenData *, Node *, Node *);
    virtual void print();
};

class IterRange : public Node
{
public:
    IterRange(int, Node *, Node *);
    IterRange(int, Node *, Node *, Node *);
    virtual void print();
};

class ReturnStmt : public Node
{
public:
    ReturnStmt(int);
    ReturnStmt(int, Node *);
    virtual void print();
};

class BreakStmt : public Node
{
public:
    BreakStmt(int);
    virtual void print();
};

class Op : public Node
{
public:
    char *opName;
    int opId;
    Op(TokenData *, Node *);
    Op(TokenData *, Node *, Node *);
    virtual void print();
};

class Assign : public Op
{
public:
    Assign(TokenData *, Node *);
    Assign(TokenData *, Node *, Node *);
    virtual void print();
};

class Id : public VarDecl
{
public:
    Id(TokenData *);
    virtual void print();
};

class Call : public Node
{
public:
    char *name;
    Call(TokenData *, Node *);
    virtual void print();
};

class Const : public Node
{
public:
    TokenData *token;
    Const(TokenData *);
    virtual void print();
};

#endif
