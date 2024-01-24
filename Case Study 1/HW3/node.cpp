#include "node.h"
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exprToStr(ExpType type, char *string);

TreeNode *newDeclNode(DeclKind kind, ExpType type, TokenData *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
    TreeNode *treeNode = new TreeNode;

    treeNode->child[0] = c0;
    treeNode->child[1] = c1;
    treeNode->child[2] = c2;
    treeNode->sibling = NULL;

    treeNode->lineno = token->lineNum;

    treeNode->nodekind = DeclK;

    treeNode->subkind.decl = kind;

    treeNode->expType = type;

    treeNode->isFunc = false;

    treeNode->attrSet = false;

    return treeNode;
}

TreeNode *newStmtNode(StmtKind kind, TokenData *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
    TreeNode *treeNode = new TreeNode;

    treeNode->child[0] = c0;
    treeNode->child[1] = c1;
    treeNode->child[2] = c2;
    treeNode->sibling = NULL;
    treeNode->lineno = token->lineNum;
    treeNode->nodekind = StmtK;
    treeNode->subkind.stmt = kind;
    treeNode->isRangeK = false;
    treeNode->isRangeKBy = false;
    treeNode->expType = UndefinedType;
    treeNode->isFunc = false;
    treeNode->attrSet = false;

    return treeNode;
}

TreeNode *newExpNode(ExpKind kind, TokenData *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
    TreeNode *treeNode = new TreeNode;

    treeNode->child[0] = c0;
    treeNode->child[1] = c1;
    treeNode->child[2] = c2;
    treeNode->sibling = NULL;
    treeNode->lineno = token->lineNum;
    treeNode->nodekind = ExpK;
    treeNode->subkind.exp = kind;
    treeNode->isFunc = false;
    treeNode->expType = UndefinedType;
    treeNode->attrSet = false;
    treeNode->isOp = false;

    if (kind == OpK)
    {
        treeNode->op = token->tokenClass;
        treeNode->isOp = true;
    }

    if (kind == AssignK)
        treeNode->op = token->tokenClass;

    return treeNode;
}

void printSpaces(int indent)
{
    if (indent > 0)
    {
        for (int i = 0; i < indent; i++)
        {
            printf(".");
            printf("   ");
        }
    }
}

TreeNode *addSibling(TreeNode *t, TreeNode *s)
{
    if (s == NULL)
    {
        printf("ERROR(SYSTEM): never add a NULL to a sibling list.\n");
        exit(1);
    }

    if (t != NULL)
    {
        TreeNode *tmp;
        tmp = t;

        while (tmp->sibling != NULL)
            tmp = tmp->sibling;

        tmp->sibling = s;

        return t;
    }
    return s;
}

void setType(TreeNode* t, ExpType type, bool isStatic)
{
    for (TreeNode* current = t; current; current = current->sibling)
    {
        current->expType = type;
        current->isStatic = isStatic;
    }
}

void exprToStr(ExpType type, char *string)
{
    switch (type)
    {
    case Void:
        strcpy(string, "void");
        break;
    case Integer:
        strcpy(string, "int");
        break;
    case Boolean:
        strcpy(string, "bool");
        break;
    case Char:
        strcpy(string, "char");
        break;
    case CharInt:
        strcpy(string, "charint");
        break;
    case Equal:
        strcpy(string, "Equal");
        break;
    case UndefinedType:
        strcpy(string, "Undefined");
        break;
    default:
        printf("Undefined EXP given to conversion function\n");
        strcpy(string, "FAILURE");
        break;
    }
}

void dumpNode(treeNode *node)
{
    char buff[64];

    exprToStr(node->expType, buff);

    printf("linenumber:%d\n", node->lineno);
    printf("token number: %d\n", node->op);

    if (node->unionType == string)
    {
        printf("Token string: %s\n", node->attr.string);
    }
    else if (node->unionType == cvalue)
    {
        printf("Token char: %s\n", node->attr.string);
    }
    else if (node->unionType == value)
        printf("Token value: %d\n", node->attr.value);
    else
    {
        printf("Unknown union type\n");
    }

    if (node->isInit)
        printf("is init: true\n");
    else
        printf("is init: false\n");

    if (node->isStatic)
        printf("is static: true\n");
    else
        printf("is static: false\n");

    if (node->isArray)
        printf("is array: true\n");
    else
        printf("is array: false\n");

    if (node->isFunc)
        printf("is Func: true\n");
    else
        printf("is Func: false\n");

    if (node->isInitError)
        printf("isInitError: true\n");
    else
        printf("isInitError: false\n");
    if (node->isUsed)
        printf("isUsed: true\n");
    else
        printf("IsUsed: false\n");

    printf("depth:%d\n", node->depth);
    printf("exptype: %s\n\n", buff);
}

void displayTree(TreeNode *node, int indent)
{
    int sibling_count = 1;

    char nodeType[64];

    while (node != NULL)
    {
        exprToStr(node->expType, nodeType);

        if (node->nodekind == StmtK)
        {
            switch (node->subkind.stmt)
            {
                case NullK:
                    printf("NULL\n");
                    break;
                case IfK:
                    printf("If [line: %d]\n", node->lineno);
                    break;
                case WhileK:
                    printf("While [line: %d]\n", node->lineno);
                    break;
                case ForK:
                    printf("For [line: %d]\n", node->lineno);
                    break;
                case CompoundK:
                    printf("Compound [line: %d]\n", node->lineno);
                    break;
                case ReturnK:
                    printf("Return [line: %d]\n", node->lineno);
                    break;
                case BreakK:
                    printf("Break [line: %d]\n", node->lineno);
                    break;
                case RangeK:
                    printf("Range [line: %d]\n", node->lineno);
                    break;

                default:
                    printf("Unknown stmtK subkind \n");
                    break;
            }
        }
        else if (node->nodekind == ExpK)
        {
            switch (node->subkind.exp)
            {
                case OpK:
                    if (node->isOp && node->op == CHSIGN)
                    {
                        printf("Op: CHSIGN [line: %d]\n", node->lineno);
                    }
                    else if (node->isOp && node->op == SIZEOF)
                    {
                        printf("Op: SIZEOF [line: %d]\n", node->lineno);
                    }
                    else
                        printf("Op: %s [line: %d]\n", node->attr.string, node->lineno);
                    break;
                case ConstantK:
                    if (strcmp(nodeType, "char") == 0)
                    {
                        if (node->isArray)
                        {
                            printf("Const is array of type %s: \"%s\" [line: %d]\n", nodeType, node->attr.string, node->lineno);
                        }
                        else
                            printf("Const of type %s: '%c' [line: %d]\n", nodeType, node->attr.value, node->lineno);
                    }
                    else if (strcmp(nodeType, "bool") == 0)
                    {
                        printf("Const of type %s: %s [line: %d]\n", nodeType, node->attr.value ? "true" : "false", node->lineno);
                    }
                    else
                        printf("Const of type %s: %d [line: %d]\n", nodeType, node->attr.value, node->lineno);
                    break;
                case IdK:
                    printf("Id: %s [line: %d]\n", node->attr.name, node->lineno);
                    break;
                case AssignK:
                    printf("Assign: %s [line: %d]\n", node->attr.string, node->lineno);
                    break;
                case InitK:
                    printf("Init:\n");
                    break;
                case CallK:
                    printf("Call: %s [line: %d]\n", node->attr.name, node->lineno);
                    break;
                default:
                    printf("Unknown ExpK Subkind\n");
                    break;
            }
        }
        else if (node->nodekind == DeclK)
        {
            switch (node->subkind.decl)
            {
                case VarK:
                    if (node->attr.name == NULL)
                    {
                        printf("internal error NULL REACHED in attrName Vark\n");
                    }

                    if (node->isArray)
                        printf("Var: %s is array of type %s [line: %d]\n", node->attr.name, nodeType, node->lineno);
                    else
                        printf("Var: %s of type %s [line: %d]\n", node->attr.name, nodeType, node->lineno);
                    break;
                case FuncK:
                    if (node->attr.name == NULL)
                    {
                        printf("internal error NULL REACHED in attrName funck\n");
                        break;
                    }
                    printf("Func: %s returns type %s [line: %d]\n", node->attr.string, nodeType, node->lineno);
                    break;
                case ParamK:
                    if (node->attr.name == NULL)
                    {
                        printf("internal error NULL REACHED in attrName Paramk\n");
                        break;
                    }

                    if (node->isArray)
                        printf("Parm: %s is array of type %s [line: %d]\n", node->attr.name, nodeType, node->lineno);
                    else
                        printf("Parm: %s of type %s [line: %d]\n", node->attr.name, nodeType, node->lineno);
                    break;
                default:
                    printf("Unknown Declk subKind\n");
                    break;
            }
        }
        else
            printf("Unknown node kind\n");

        for (int i = 0; i < MAX_CHILDREN; i++)
        {
            if (node->child[i] != NULL)
            {
                printSpaces(indent + 1);
                printf("Child: %d ", i);
                displayTree(node->child[i], indent + 1);
            }
        }

        if (node->sibling != NULL)
        {
            printSpaces(indent);
            printf("Sibling: %d ", sibling_count++);
            node = node->sibling;
        }
        else
            node = node->sibling;
    }
}

void displayTypedTree(TreeNode *node, int indent)
{
    int sibling_count = 1;

    char nodeType[64];

    while (node != NULL)
    {
        exprToStr(node->expType, nodeType);

        if (node->nodekind == StmtK)
        {
            switch (node->subkind.stmt)
            {
                case NullK:
                    printf("NULL\n");
                    break;
                case IfK:
                    printf("If [line: %d]\n", node->lineno);
                    break;
                case WhileK:
                    printf("While [line: %d]\n", node->lineno);
                    break;
                case ForK:
                    printf("For [line: %d]\n", node->lineno);
                    break;
                case CompoundK:
                    printf("Compound [line: %d]\n", node->lineno);
                    break;
                case ReturnK:
                    printf("Return [line: %d]\n", node->lineno);
                    break;
                case BreakK:
                    printf("Break [line: %d]\n", node->lineno);
                    break;
                case RangeK:
                    printf("Range [line: %d]\n", node->lineno);
                    break;

                default:
                    printf("Unknown stmtK subkind \n");
                    break;
            }
        }
        else if (node->nodekind == ExpK)
        {
            switch (node->subkind.exp)
            {
                case OpK:
                    if (node->isOp && node->op == CHSIGN)
                    {
                        if (node->expType == UndefinedType)
                        {
                            printf("Op: chsign of undefined type [line: %d]\n", node->lineno);
                        }
                        else
                            printf("Op: chsign of type %s [line: %d]\n", nodeType, node->lineno);
                    }
                    else if (node->isOp && node->op == SIZEOF)
                    {
                        if (node->expType == UndefinedType)
                        {
                            printf("Op: sizeof of undefined type [line: %d]\n", node->lineno);
                        }
                        else
                            printf("Op: sizeof of type %s [line: %d]\n", nodeType, node->lineno);
                    }
                    else
                    {
                        if (node->expType == UndefinedType)
                        {
                            printf("Op: %s of undefined type [line: %d]\n", node->attr.string, node->lineno);
                        }
                        else
                            printf("Op: %s of type %s [line: %d]\n", node->attr.string, nodeType, node->lineno);
                    }
                    break;
                case ConstantK:
                    if (strcmp(nodeType, "char") == 0)
                    {
                        if (node->isArray)
                        {
                            printf("Const is array \"%s\" of type %s [line: %d]\n", node->attr.string, nodeType, node->lineno);
                        }
                        else
                            printf("Const '%c' of type %s [line: %d]\n", node->attr.value, nodeType, node->lineno);
                    }
                    else if (strcmp(nodeType, "bool") == 0)
                    {
                        printf("Const %s of type %s [line: %d]\n", node->attr.value ? "true" : "false", nodeType, node->lineno);
                    }
                    else
                        printf("Const %d of type %s [line: %d]\n", node->attr.value, nodeType, node->lineno);
                    break;
                case IdK:
                    if (node->expType == UndefinedType)
                    {
                        printf("Id: %s of undefined type [line: %d]\n", node->attr.name, node->lineno);
                    }
                    else
                        printf("Id: %s of type %s [line: %d]\n", node->attr.name, nodeType, node->lineno);
                    break;
                case AssignK:
                    printf("Assign: %s of type %s [line: %d]\n", node->attr.string, nodeType, node->lineno);
                    break;
                case InitK:
                    printf("Init:\n");
                    break;
                case CallK:
                    printf("Call: %s of type %s [line: %d]\n", node->attr.name, nodeType, node->lineno);
                    break;
                default:
                    printf("Unknown ExpK Subkind\n");
                    break;
            }
        }
        else if (node->nodekind == DeclK)
        {
            switch (node->subkind.decl)
            {
                case VarK:
                    if (node->attr.name == NULL)
                    {
                        printf("internal error NULL REACHED in attrName Vark\n");
                    }

                    if (node->isArray)
                        printf("Var: %s is array of type %s [line: %d]\n", node->attr.name, nodeType, node->lineno);
                    else
                        printf("Var: %s of type %s [line: %d]\n", node->attr.name, nodeType, node->lineno);
                    break;
                case FuncK:
                    if (node->attr.name == NULL)
                    {
                        printf("internal error NULL REACHED in attrName funck\n");
                        break;
                    }
                    printf("Func: %s returns type %s [line: %d]\n", node->attr.string, nodeType, node->lineno);
                    break;
                case ParamK:
                    if (node->attr.name == NULL)
                    {
                        printf("internal error NULL REACHED in attrName Paramk\n");
                        break;
                    }

                    if (node->isArray)
                        printf("Parm: %s is array of type %s [line: %d]\n", node->attr.name, nodeType, node->lineno);
                    else
                        printf("Parm: %s of type %s [line: %d]\n", node->attr.name, nodeType, node->lineno);
                    break;
                default:
                    printf("Unknown Declk subKind\n");
                    break;
            }
        }
        else
            printf("Unknown node kind\n");

        for (int i = 0; i < MAX_CHILDREN; i++)
        {
            if (node->child[i] != NULL)
            {
                printSpaces(indent + 1);
                printf("Child: %d  ", i);
                displayTypedTree(node->child[i], indent + 1);
            }
        }

        if (node->sibling != NULL)
        {
            printSpaces(indent);
            printf("Sibling: %d  ", sibling_count++);
            node = node->sibling;
        }
        else
            node = node->sibling;
    }
}