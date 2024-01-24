#include "node.h"
#include "parser.tab.h"
#include "symbolTable.h"
#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

#define SUPPRESS_CHILD_SCOPE true

ExpType typeTable(TreeNode *parentNode, treeNode *lhsNode, treeNode *rhsNode);
void checkChildren(TreeNode *node, SymbolTable *symTab, bool suppressChildScope);
void checkIsUsed(std::string symbolName, void *ptr);
void checkIsInit(std::string symbolName, void *ptr);
void checkSizeOf(TreeNode *node);

int ERROR_COUNT = 0;
int WARNING_COUNT = 0;

void checkSizeOf(TreeNode *node, SymbolTable *symTab)
{
    if (node->op == SIZEOF)
    {
        if (node->parent->isRangeK)
        {
            node->expType = UndefinedType;
            if (node->child[0] != NULL && node->child[0]->nodekind == ExpK && node->child[0]->subkind.exp == IdK)
            {
                node->child[0]->expType = UndefinedType;
            }
        }
        else
            node->expType = Integer;

        if (node->child[0]->subkind.exp == IdK)
        {
            TreeNode *lookupNode;
            lookupNode = (treeNode *)symTab->lookup(std::string(node->child[0]->attr.name));

            if (lookupNode != NULL && !(lookupNode->isArray))
            {
                printf("ERROR(%d): The operation 'sizeof' only works with arrays.\n", node->lineno);
                ERROR_COUNT++;
            }
        }
        else
            printf("size of lookup failed. child node is not IDk\n");
    }
}

void checkChildren(TreeNode *node, SymbolTable *symTab, bool suppressChildScope)
{

    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        if (node->child[i] != NULL)
        {
            checkTree2(symTab, node->child[i], suppressChildScope, node);
        }
    }
}

void checkTree2(SymbolTable *symTab, TreeNode *node, bool parentSuppressScope, TreeNode *parent)
{
    char nodeType[64];

    treeNode *lookupNode;

    while (node != NULL)
    {
        node->parent = parent;
        exprToStr(node->expType, nodeType);

        if (node->nodekind == StmtK)
        {
            switch (node->subkind.stmt)
            {
            case NullK:
                checkChildren(node, symTab, !!SUPPRESS_CHILD_SCOPE);
                break;

            case IfK:
                checkChildren(node, symTab, !SUPPRESS_CHILD_SCOPE);
                break;

            case WhileK:
                checkChildren(node, symTab, !SUPPRESS_CHILD_SCOPE);
                break;

            case ForK:
                symTab->enter(std::string("this is a for loop"));

                checkChildren(node, symTab, SUPPRESS_CHILD_SCOPE);

                if (!(node->child[2] != NULL && node->child[2]->nodekind == StmtK && node->child[2]->subkind.stmt == CompoundK))
                {
                    symTab->applyToAll(checkIsUsed);
                }

                symTab->leave();
                break;

            case CompoundK:
                if (!parentSuppressScope)
                    symTab->enter(std::string("THIS IS A COMPOUND"));

                checkChildren(node, symTab, !SUPPRESS_CHILD_SCOPE);

                symTab->applyToAll(checkIsUsed);

                if (!parentSuppressScope)
                    symTab->leave();

                parentSuppressScope = false;
                break;

            case ReturnK:

                checkChildren(node, symTab, !SUPPRESS_CHILD_SCOPE);

                if (node->child[0] != NULL && node->child[0]->isArray)
                {
                    printf("ERROR(%d): Cannot return an array.\n", node->lineno);
                    ERROR_COUNT++;
                }
                break;

            case BreakK:
                checkChildren(node, symTab, !SUPPRESS_CHILD_SCOPE);
                break;

            case RangeK:
                if (node->child[0] != NULL && node->child[1] != NULL)
                {
                    node->child[0]->isInit = true;
                    node->child[0]->isRangeK = true;
                    node->child[1]->isInit = true;
                    node->child[1]->isRangeK = true;

                    if (node->child[2] != NULL)
                    {
                        node->child[2]->isInit = true;
                        node->child[2]->isRangeKBy = true;
                    }
                }
                checkChildren(node, symTab, !SUPPRESS_CHILD_SCOPE);
                break;

            default:
                printf("PROGRAMMER ERROR UNKNOWN STATMENT TYPE\nSHOULD NOT GET HERE\n");
                exit(-1);
            }
        }

        else if (node->nodekind == DeclK)
        {
            switch (node->subkind.decl)
            {
            case VarK:
                if (symTab->insert(std::string(node->attr.name), (void *)node))
                {
                    node->depth = symTab->depth();
                    node->isUsed = false;

                    if (node->parent != NULL && node->parent->nodekind == StmtK && node->parent->subkind.stmt == ForK)
                        node->isInit = true;
                    else
                        node->isInit = false;

                    node->isInitError = false;
                }
                else
                {
                    lookupNode = (treeNode *)symTab->lookup(node->attr.name);
                    printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
                           node->lineno,
                           lookupNode->attr.name,
                           lookupNode->lineno);
                    ERROR_COUNT++;
                }

                checkChildren(node, symTab, !SUPPRESS_CHILD_SCOPE);

                if (node->child[0] != NULL)
                    node->isInit = true;

                break;

            case FuncK:
                if (node->attr.name == NULL)
                {
                    printf("internal error NULL REACHED in attrName funck\n");
                    break;
                }

                if (symTab->insertGlobal(std::string(node->attr.string), node))
                {
                    node->depth = symTab->depth();
                    node->isUsed = false;
                    node->isFunc = true;
                }
                else
                {
                    lookupNode = (treeNode *)symTab->lookup(node->attr.string);
                    printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
                           node->lineno,
                           lookupNode->attr.string,
                           lookupNode->lineno);
                    ERROR_COUNT++;
                }
                symTab->enter(std::string(node->attr.string));

                checkChildren(node, symTab, SUPPRESS_CHILD_SCOPE);

                if (node->child[1] != NULL)
                {
                    if (node->child[1]->nodekind == StmtK && node->child[1]->subkind.stmt == ReturnK)
                        symTab->applyToAll(checkIsUsed);
                }

                symTab->leave();
                break;

            case ParamK:
                if (node->attr.name == NULL)
                {
                    printf("internal error NULL REACHED in attrName Paramk\n");
                    break;
                }

                node->isUsed = false;
                node->isInit = true;

                if (!symTab->insert(std::string(node->attr.name), (void *)node))
                {
                    lookupNode = (treeNode *)symTab->lookup(node->attr.string);
                    printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
                           node->lineno,
                           lookupNode->attr.string,
                           lookupNode->lineno);
                    ERROR_COUNT++;
                }
                node->depth = symTab->depth();

                checkChildren(node, symTab, !SUPPRESS_CHILD_SCOPE);
                break;

            default:
                printf("PROGRAMMER ERROR UNKNOWN DECL TYPE\nSHOULD NOT GET HERE\n");
                exit(-1);
            }
        }

        else if (node->nodekind == ExpK)
        {
            switch (node->subkind.exp)
            {
            case OpK:
                checkChildren(node, symTab, !SUPPRESS_CHILD_SCOPE);

                if (node->op == OPEN_BRACK)
                {
                    if (node->child[0] != NULL)
                        node->expType = node->child[0]->expType;

                    if (node->child[1]->expType != Integer)
                    {
                        char buff[64];
                        exprToStr(node->child[1]->expType, buff);
                        printf("ERROR(%d): Array '%s' should be indexed by type int but got type %s.\n",
                               node->lineno, node->child[0]->attr.name, buff);
                        ERROR_COUNT++;
                    }

                    lookupNode = (treeNode *)symTab->lookup(std::string(node->child[0]->attr.name));
                    if (lookupNode != NULL && !(lookupNode->isArray))
                    {
                        printf("ERROR(%d): Cannot index nonarray '%s'.\n", node->child[0]->lineno, node->child[0]->attr.name);
                        ERROR_COUNT++;
                    }
                    else if (lookupNode == NULL)
                    {
                        printf("ERROR(%d): Cannot index nonarray '%s'.\n", node->child[0]->lineno, node->child[0]->attr.name);
                        ERROR_COUNT++;
                    }

                    if (node->child[1]->nodekind == ExpK && node->child[1]->subkind.exp == IdK)
                    {
                        lookupNode = (treeNode *)symTab->lookup(std::string(node->child[1]->attr.name));
                        if (lookupNode != NULL && lookupNode->isArray)
                        {
                            printf("ERROR(%d): Array index is the unindexed array '%s'.\n", node->child[1]->lineno, node->child[1]->attr.name);
                            ERROR_COUNT++;
                        }
                    }
                    node->isArray = false;
                }
                else
                {
                    if (node->op == SIZEOF)
                        checkSizeOf(node, symTab);
                    else
                        node->expType = typeTable(node, node->child[0], node->child[1]);
                }
                break;
            case ConstantK:
                checkChildren(node, symTab, !SUPPRESS_CHILD_SCOPE);
                break;

            case IdK:
                lookupNode = (treeNode *)symTab->lookup(std::string(node->attr.name));

                if (lookupNode == NULL)
                {
                    if (!node->isRangeK)
                    {
                        printf("ERROR(%d): Symbol '%s' is not declared.\n", node->lineno, node->attr.name);
                        ERROR_COUNT++;
                    }
                }
                else
                {
                    if (node->isRangeK || node->parent->isRangeKBy || node->isRangeKBy)
                    {
                        lookupNode->isInit = true;
                    }
                    else
                        lookupNode->isUsed = true;

                    if ((node->parent->nodekind == StmtK && node->parent->subkind.stmt == RangeK) || node->isRangeKBy || node->parent->isRangeKBy)
                    {
                        node->expType = UndefinedType;
                    }
                    else
                        node->expType = lookupNode->expType;

                    node->isArray = lookupNode->isArray;
                    node->isStatic = lookupNode->isStatic;
                    node->isFunc = lookupNode->isFunc;

                    if (!lookupNode->isInit)
                    {
                        bool suppressWarning = false;
                        treeNode *currParent = node->parent;
                        treeNode *currNode = node;

                        if (currParent->parent != NULL && currParent->parent->op == OPEN_BRACK)
                        {
                            currNode = currParent->parent;
                            currParent = currParent->parent->parent;
                        }

                        if (currParent->op == OPEN_BRACK)
                        {
                            currNode = currParent;
                            currParent = currParent->parent;
                        }

                        if (currNode->parent->op == ADDASS)
                        {
                            suppressWarning = true;
                        }

                        if (currParent != NULL && currParent->nodekind == ExpK && currParent->subkind.exp == AssignK && currParent->child[0] == currNode && currParent->op == ASS)
                        {
                            suppressWarning = true;
                        }

                        if (lookupNode->isStatic || lookupNode->depth == 1)
                        {
                            suppressWarning = true;
                        }

                        if (!suppressWarning)
                        {
                            if (!lookupNode->isInitError && !lookupNode->isFunc)
                            {

                                printf("WARNING(%d): Variable '%s' may be uninitialized when used here.\n", node->lineno, node->attr.name);
                                WARNING_COUNT++;
                                lookupNode->isInitError = true;
                            }
                        }
                    }

                    if (lookupNode->isFunc)
                    {
                        printf("ERROR(%d): Cannot use function '%s' as a variable.\n", node->lineno, node->attr.name);
                        ERROR_COUNT++;
                    }
                }
                checkChildren(node, symTab, !SUPPRESS_CHILD_SCOPE);
                break;

            case AssignK:
            {
                checkChildren(node, symTab, !SUPPRESS_CHILD_SCOPE);

                bool isArrayRef = false;

                if (node->child[0] == NULL)
                {
                    printf("Unexpected Null child when checking init for assignk's\n");
                }
                else
                {
                    treeNode *lookupNode;
                    treeNode *childNodeRef;

                    childNodeRef = node->child[0];

                    if (childNodeRef->op == OPEN_BRACK)
                    {
                        isArrayRef = true;
                        childNodeRef = childNodeRef->child[0];
                    }

                    if (childNodeRef == NULL)
                    {
                        printf("Unexpected Null child when checking init for assignk's\n");
                    }
                    else
                    {
                        lookupNode = (treeNode *)symTab->lookup(std::string(std::string(childNodeRef->attr.name)));

                        if (lookupNode != NULL)
                        {
                            lookupNode->isInit = true;
                        }
                    }

                    if (isArrayRef)
                    {
                        childNodeRef->parent->isArray = false;
                        childNodeRef->parent->expType = childNodeRef->expType;
                    }
                }

                if (node->op != OPEN_BRACK)
                {
                    if (node->op == SIZEOF)
                        checkSizeOf(node, symTab);
                    else
                        node->expType = typeTable(node, node->child[0], node->child[1]);
                }

                break;
            }
            case InitK:
                checkChildren(node, symTab, !SUPPRESS_CHILD_SCOPE);
                break;

            case CallK:
                lookupNode = (treeNode *)symTab->lookup(std::string(node->attr.name));
                if (lookupNode != NULL)
                {
                    lookupNode->isUsed = true;
                    if (!lookupNode->isFunc)
                    {
                        printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", node->lineno, node->attr.name);
                        ERROR_COUNT++;
                        break;
                    }
                }

                lookupNode = (treeNode *)symTab->lookupGlobal(std::string(node->attr.name));
                if (lookupNode == NULL)
                {
                    printf("ERROR(%d): Symbol '%s' is not declared.\n", node->lineno, node->attr.name);
                    ERROR_COUNT++;
                }
                else
                {
                    lookupNode->isUsed = true;
                    node->expType = lookupNode->expType;
                }

                checkChildren(node, symTab, !SUPPRESS_CHILD_SCOPE);

                break;

            default:
                printf("PROGRAMMER ERROR UNKNOWN EXP\nSHOULD NOT GET HERE\n");
                exit(-1);
            }
        }

        else
        {
            printf("PROGRAMMER ERROR UNKNOWN NODEKIND\nSHOULD NOT GET HERE\n");
            exit(-1);
        }

        node = node->sibling;
    }
}

void checkIsUsed(std::string symbolName, void *ptr)
{
    treeNode *nodeptr;
    nodeptr = (treeNode *)ptr;

    if (!nodeptr->isUsed && nodeptr->depth != 1)
    {
        printf("WARNING(%d): The variable '%s' seems not to be used.\n",
               nodeptr->lineno, symbolName.c_str());
        WARNING_COUNT++;
    }
}

ExpType typeTable(TreeNode *parentNode, treeNode *lhsNode, treeNode *rhsNode)
{
    ExpType lhs, rhs;

    char buff1[64];
    char buff2[64];

    if (parentNode->subkind.exp == OpK)
    {
        OpKind op = parentNode->op;
        if (op == PLUS || op == MINUS || op == DIV || op == MOD || op == MAX || op == MIN || op == MULT)
        {
            lhs = lhsNode->expType;
            rhs = rhsNode->expType;

            if (parentNode->isRangeK || parentNode->isRangeKBy)
                return UndefinedType;

            if (lhs == Integer && rhs == Integer)
            {
                if (!lhsNode->isArray && !rhsNode->isArray)
                {
                    if (parentNode->parent->nodekind == StmtK && parentNode->parent->subkind.stmt == RangeK)
                    {
                        return UndefinedType;
                    }
                    return Integer;
                }

                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                ERROR_COUNT++;

                return Integer;
            }

            exprToStr(lhs, buff1);
            exprToStr(rhs, buff2);
            if (lhs == Integer)
            {
                if (rhs != UndefinedType && rhs != Void)
                {
                    printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff2);
                    ERROR_COUNT++;
                }
            }
            else if (rhs == Integer)
            {
                if (lhs != UndefinedType && lhs != Void)
                {
                    printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff1);
                    ERROR_COUNT++;
                }
            }
            else
            {
                if (lhs != UndefinedType && rhs != UndefinedType)
                {
                    printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff1);
                    ERROR_COUNT++;

                    printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff2);
                    ERROR_COUNT++;
                }
            }
            if (lhsNode->isArray || rhsNode->isArray)
            {
                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                ERROR_COUNT++;
            }
            return Integer;
        }
        else if (op == CHSIGN || op == QUESTION)
        {
            lhs = lhsNode->expType;

            if (lhsNode->isArray)
            {
                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, op == CHSIGN ? "chsign" : "?");
                ERROR_COUNT++;
            }

            exprToStr(lhs, buff1);

            if (op == CHSIGN)
            {
                if (lhs != Integer && lhs != UndefinedType)
                {
                    printf("ERROR(%d): Unary 'chsign' requires an operand of type %s but was given type %s.\n",
                           parentNode->lineno,
                           "int",
                           buff1);
                    ERROR_COUNT++;
                }

                if (parentNode->parent->nodekind == StmtK && parentNode->parent->subkind.stmt == RangeK)
                    return UndefinedType;

                return Integer;
            }
            else
            {
                if (lhs != Integer)
                {
                    printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           "int",
                           buff1);
                    ERROR_COUNT++;
                }
            }

            return Integer;
        }
        else if (op == LEQ || op == LESS || op == GREATER || op == GEQ || op == EQ || op == NEQ)
        {
            lhs = lhsNode->expType;
            rhs = rhsNode->expType;

            if (op == EQ || op == NEQ)
            {
                if ((!lhsNode->isArray && rhsNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
                else if (lhsNode->isArray && (!rhsNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
            }
            else if (op == GEQ || op == LEQ || op == LESS || op == GREATER)
            {
                if ((!lhsNode->isArray && rhsNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
                else if (lhsNode->isArray && (!rhsNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
            }

            if (lhs == rhs)
            {
                return Boolean;
            }

            exprToStr(lhs, buff1);
            exprToStr(rhs, buff2);

            if (lhs != UndefinedType)
            {
                printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
                       parentNode->lineno, parentNode->attr.string, buff1, buff2);
                ERROR_COUNT++;
            }

            return Boolean;
        }
        else if (op == AND || op == OR)
        {
            lhs = lhsNode->expType;
            rhs = rhsNode->expType;
            if (lhs == Boolean && rhs == Boolean)
            {
                if (lhsNode->isArray || rhsNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                    return UndefinedType;
                }
                return Boolean;
            }

            exprToStr(lhs, buff1);
            exprToStr(rhs, buff2);

            if (lhs == Boolean)
            {
                printf("ERROR(%d): '%s' requires operands of type bool but rhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff2);
                ERROR_COUNT++;
            }
            else if (rhs == Boolean)
            {
                printf("ERROR(%d): '%s' requires operands of type bool but lhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff1);
                ERROR_COUNT++;
            }
            else
            {
                printf("ERROR(%d): '%s' requires operands of type bool but lhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff1);
                ERROR_COUNT++;

                printf("ERROR(%d): '%s' requires operands of type bool but rhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff2);
                ERROR_COUNT++;
            }

            if (lhsNode->isArray || rhsNode->isArray)
            {
                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                ERROR_COUNT++;
            }
            return Boolean;
        }

        else if (op == NOT)
        {
            lhs = lhsNode->expType;

            if (lhs == Boolean)
            {
                if (lhsNode->isArray)
                {
                    printf("ERROR(%d): The operation 'not' does not work with arrays.\n", parentNode->lineno);
                    ERROR_COUNT++;
                }

                return Boolean;
            }

            exprToStr(lhs, buff1);

            printf("ERROR(%d): Unary 'not' requires an operand of type %s but was given type %s.\n",
                   parentNode->lineno,
                   "bool",
                   buff1);
            ERROR_COUNT++;

            if (lhsNode->isArray)
            {
                printf("ERROR(%d): The operation 'not' does not work with arrays.\n", parentNode->lineno);
                ERROR_COUNT++;
            }
            return Boolean;
        }
    }
    else if (parentNode->subkind.exp == AssignK)
    {
        OpKind op = parentNode->op;

        if (op == ASS)
        {
            lhs = lhsNode->expType;
            rhs = rhsNode->expType;

            exprToStr(lhs, buff1);
            exprToStr(rhs, buff2);
            if (lhs == rhs)
            {
                if (lhsNode->isArray && rhsNode->isArray)
                    return lhs;
                else if (lhsNode->isArray && !(rhsNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n",
                           parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
                else if (!(lhsNode->isArray) && rhsNode->isArray)
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n",
                           parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }

                return lhs;
            }
            else
            {
                if (lhs != UndefinedType && lhs != Void)
                {
                    printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
                           parentNode->lineno, parentNode->attr.string, buff1, buff2);
                    ERROR_COUNT++;
                }
            }

            return lhs;
        }
        else if (op == ADDASS || op == SUBASS || op == MULASS || op == DIVASS)
        {
            lhs = lhsNode->expType;
            rhs = rhsNode->expType;

            exprToStr(lhs, buff1);
            exprToStr(rhs, buff2);
            if (lhs == Integer && rhs == Integer)
            {
                if (lhsNode->isArray || rhsNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
                return Integer;
            }

            if (lhs == Integer)
            {
                printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff2);
                ERROR_COUNT++;
            }
            else if (rhs == Integer)
            {
                printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff1);
                ERROR_COUNT++;
            }
            else
            {
                printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff1);
                ERROR_COUNT++;

                printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff2);
                ERROR_COUNT++;
            }

            return Integer;
        }
        else if (op == DEC || op == INC)
        {
            lhs = lhsNode->expType;

            exprToStr(lhs, buff1);

            if (lhs == Integer)
            {
                if (lhsNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
                return lhs;
            }

            else
            {
                if (lhs != UndefinedType)
                {
                    printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           "int",
                           buff1);
                    ERROR_COUNT++;
                }

                if (lhsNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
            }
            return Integer;
        }
        else if (op == AND || op == OR)
        {
            lhs = lhsNode->expType;
            rhs = rhsNode->expType;
            if (lhs == Boolean && rhs == Boolean)
                return Boolean;

            exprToStr(lhs, buff1);
            exprToStr(rhs, buff2);

            if (lhs == Boolean)
            {
                printf("ERROR(%d): '%s' requires operands of type bool but rhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff2);
                ERROR_COUNT++;
            }
            else if (rhs == Boolean)
            {
                printf("ERROR(%d): '%s' requires operands of type bool but lhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff1);
                ERROR_COUNT++;
            }
            else
            {
                printf("ERROR(%d): '%s' requires operands of type bool but lhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff1);
                ERROR_COUNT++;

                printf("ERROR(%d): '%s' requires operands of type bool but rhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff2);
                ERROR_COUNT++;
            }
            return Boolean;
        }

        else if (op == NOT)
        {
            lhs = lhsNode->expType;

            if (lhs == Boolean)
            {
                if (lhsNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
                return Boolean;
            }

            exprToStr(lhs, buff1);

            printf("ERROR(%d): Unary 'not' requires an operand of type %s but was given type %s.\n",
                   parentNode->lineno,
                   "bool",
                   buff1);
            ERROR_COUNT++;

            if (lhsNode->isArray)
            {
                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                ERROR_COUNT++;
            }
            return Boolean;
        }
    }

    return UndefinedType;
}
