#include "node.h"
#include "parser.tab.h"
#include "symbolTable.h"
#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

int ERROR_COUNT = 0;
int WARNING_COUNT = 0;

#define SUPPRESS_CHILD_SCOPE true

ExpType verifyNodeTypes(TreeNode *parentNode, treeNode *leftNode, treeNode *rightNode);

void verifySize(TreeNode *node, SymbolTable *sTab)
{
    if (node->op == SIZEOF)
    {
        node->expType = Integer;

        if (node->child[0]->subkind.exp == IdK)
        {
            TreeNode *lookupNode;
            lookupNode = (treeNode *)sTab->lookup(std::string(node->child[0]->attr.name));

            if (lookupNode != NULL && !(lookupNode->isArray))
            {
                printf("ERROR(%d): The operation 'sizeof' only works with arrays.\n", node->lineno);
                ERROR_COUNT++;
            }
        }
        else
        {
            TreeNode *lookupNode;
            lookupNode = (treeNode *)sTab->lookup(std::string(node->child[0]->attr.name));

            if (lookupNode != NULL && !node->child[0]->isArray)
            {
                printf("ERROR(%d): The operation 'sizeof' only works with arrays.\n", node->lineno);
                ERROR_COUNT++;
            }
            else
            {
                if (!node->child[0]->undeclared)
                {
                    printf("ERROR(%d): The operation 'sizeof' only works with arrays.\n", node->lineno);
                    ERROR_COUNT++;
                }
            }
        }
    }
}

int localOffset = 0;
int globalOffset = 0;

void checkTree2(SymbolTable *sTab, TreeNode *node, bool parentSuppressScope, TreeNode *parent)
{
    char nodeType[64];
    int tmpLocalOffset = 0;

    static bool firstNode = true;
    static TreeNode *headOfTree = NULL;
    static TreeNode *tailOfTree = NULL;
    static bool returnStmtFound = false;

    static int loopDepth = 0;

    static TreeNode *functionNodePtr = NULL;

    treeNode *lookupNode;

    while (node != NULL)
    {

        if (firstNode)
        {
            headOfTree = node;
            firstNode = false;

            symbolLibrary(sTab);
        }

        node->parent = parent;
        exprToStr(node->expType, nodeType);

        if (node->nodekind == StmtK)
        {
            switch (node->subkind.stmt)
            {
                case NullK:
                    validateChildNodes(node, sTab, !SUPPRESS_CHILD_SCOPE);
                    break;

                case IfK:
                    validateChildNodes(node, sTab, !SUPPRESS_CHILD_SCOPE);

                    if (node->child[0] != NULL && node->child[0]->expType != Boolean)
                    {
                        char buffChild[64];
                        exprToStr(node->child[0]->expType, buffChild);

                        if (node->child[0]->expType != UndefinedType)
                        {
                            printf("ERROR(%d): Expecting Boolean test condition in if statement but got type %s.\n", node->lineno, buffChild);
                            ERROR_COUNT++;
                        }
                    }

                    if (node->child[0] != NULL && node->child[0]->isArray)
                    {
                        printf("ERROR(%d): Cannot use array as test condition in if statement.\n", node->lineno);
                        ERROR_COUNT++;
                    }

                    break;

                case WhileK:

                    loopDepth++;

                    validateChildNodes(node, sTab, !SUPPRESS_CHILD_SCOPE);

                    if (node->child[0] != NULL && node->child[0]->expType != Boolean)
                    {
                        char buffChild[64];
                        exprToStr(node->child[0]->expType, buffChild);

                        if (node->child[0]->expType != UndefinedType)
                        {
                            printf("ERROR(%d): Expecting Boolean test condition in while statement but got type %s.\n", node->lineno, buffChild);
                            ERROR_COUNT++;
                        }
                    }

                    if (node->child[0] != NULL && node->child[0]->isArray)
                    {
                        printf("ERROR(%d): Cannot use array as test condition in while statement.\n", node->lineno);
                        ERROR_COUNT++;
                    }

                    loopDepth--;

                    break;

                case ForK:
                    sTab->enter(std::string("this is a for loop"));

                    loopDepth++;

                    tmpLocalOffset = localOffset;
                    validateChildNodes(node, sTab, SUPPRESS_CHILD_SCOPE);

                    node->size = localOffset;

                    localOffset = tmpLocalOffset;

                    if (!(node->child[2] != NULL && node->child[2]->nodekind == StmtK && node->child[2]->subkind.stmt == CompoundK))
                    {
                        sTab->applyToAll(verifySymbolUsage);
                    }

                    sTab->leave();

                    loopDepth--;
                    break;

                case CompoundK:
                    if (!parentSuppressScope)
                        sTab->enter(std::string("THIS IS A COMPOUND"));

                    tmpLocalOffset = localOffset;
                    validateChildNodes(node, sTab, !SUPPRESS_CHILD_SCOPE);

                    node->size = localOffset;
                    localOffset = tmpLocalOffset;

                    if (node->parent != NULL && !(node->parent->nodekind == DeclK && node->parent->subkind.decl == FuncK))
                        sTab->applyToAll(verifySymbolUsage);

                    if (!parentSuppressScope)
                        sTab->leave();

                    parentSuppressScope = false;
                    break;

                case ReturnK:

                    validateChildNodes(node, sTab, !SUPPRESS_CHILD_SCOPE);

                    returnStmtFound = true;

                    if (node->child[0] != NULL && functionNodePtr != NULL)
                    {
                        char buffChild[64];
                        char buffFunc[64];

                        if (node->child[0]->expType != functionNodePtr->expType)
                        {

                            exprToStr(functionNodePtr->expType, buffFunc);
                            exprToStr(node->child[0]->expType, buffChild);

                            if (node->child[0]->expType != UndefinedType)
                            {

                                if (functionNodePtr->expType == Void)
                                {
                                    printf("ERROR(%d): Function '%s' at line %d is expecting no return value, but return has a value.\n",
                                           node->lineno,
                                           functionNodePtr->attr.string,
                                           functionNodePtr->lineno);

                                    ERROR_COUNT++;
                                }
                                else
                                {
                                    printf("ERROR(%d): Function '%s' at line %d is expecting to return type %s but returns type %s.\n",
                                           node->lineno,
                                           functionNodePtr->attr.string,
                                           functionNodePtr->lineno,
                                           buffFunc,
                                           buffChild);

                                    ERROR_COUNT++;
                                }
                            }
                        }
                    }

                    else if (functionNodePtr != NULL)
                    {
                        char buffFunc[64];

                        exprToStr(functionNodePtr->expType, buffFunc);

                        if (functionNodePtr->expType != Void)
                        {
                            printf("ERROR(%d): Function '%s' at line %d is expecting to return type %s but return has no value.\n",
                                   node->lineno,
                                   functionNodePtr->attr.string,
                                   functionNodePtr->lineno,
                                   buffFunc);

                            ERROR_COUNT++;
                        }
                    }

                    if (node->child[0] != NULL && node->child[0]->isArray)
                    {
                        printf("ERROR(%d): Cannot return an array.\n", node->lineno);
                        ERROR_COUNT++;
                    }
                    break;

                case BreakK:
                    validateChildNodes(node, sTab, !SUPPRESS_CHILD_SCOPE);

                    if (loopDepth == 0)
                    {
                        printf("ERROR(%d): Cannot have a break statement outside of loop.\n", node->lineno);
                        ERROR_COUNT++;
                    }

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
                    validateChildNodes(node, sTab, !SUPPRESS_CHILD_SCOPE);

                    for (int i = 0; node->child[i] != NULL; i++)
                    {
                        char buff[64];
                        exprToStr(node->child[i]->expType, buff);

                        if (node->child[i]->expType != Integer && node->child[i]->expType != UndefinedType && !(node->child[i]->isFunc && node->child[i]->expType == Void))
                        {
                            printf("ERROR(%d): Expecting type int in position %d in range of for statement but got type %s.\n",
                                   node->lineno,
                                   i + 1,
                                   buff);
                            ERROR_COUNT++;
                        }

                        if (node->child[i]->isArray)
                        {
                            printf("ERROR(%d): Cannot use array in position %d in range of for statement.\n",
                                   node->lineno,
                                   i + 1);
                            ERROR_COUNT++;
                        }
                    }
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

                    validateChildNodes(node, sTab, !SUPPRESS_CHILD_SCOPE);

                    if (sTab->insert(std::string(node->attr.name), (void *)node))
                    {
                        node->depth = sTab->depth();

                        node->isUsed = false;

                        if (!node->isArray)
                            node->size = 1;

                        if (node->parent != NULL && node->parent->nodekind == StmtK && node->parent->subkind.stmt == ForK)
                        {
                            node->isInit = true;
                        }
                        else
                        {
                            node->isInit = false;
                        }

                        node->isInitError = false;

                        if (node->depth == 1)
                        {
                            node->scope = Global;

                            node->loc = globalOffset;

                            globalOffset -= node->size;
                        }

                        else if (node->depth > 1)
                        {

                            if (node->isStatic)
                            {
                                node->scope = LocalStatic;

                                node->loc = globalOffset;
                                globalOffset -= node->size;
                            }
                            else
                            {
                                node->scope = Local;
                                node->loc = localOffset;

                                localOffset -= node->size;
                            }
                        }
                    }

                    else
                    {
                        lookupNode = (treeNode *)sTab->lookup(node->attr.name);
                        printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
                               node->lineno,
                               lookupNode->attr.name,
                               lookupNode->lineno);
                        ERROR_COUNT++;
                    }

                    if (node->child[0] != NULL)
                    {

                        if ((node->child[0]->tokenStr != NULL && node->tokenStr != NULL) && strcmp(node->child[0]->tokenStr, node->tokenStr) == 0)
                        {

                            lookupNode = (treeNode *)sTab->lookup(node->attr.name);
                            if (lookupNode == NULL)
                            {
                                node->isUsed = false;

                                printf("ERROR(%d): Symbol '%s' is not declared.\n", node->lineno, node->attr.name);
                                ERROR_COUNT++;
                            }
                            else
                            {
                            }
                        }

                        if (!node->child[0]->isConst)
                        {
                            printf("ERROR(%d): Initializer for variable '%s' is not a constant expression.\n",
                                   node->lineno,
                                   node->attr.name);

                            ERROR_COUNT++;
                        }

                        if (node->child[0]->expType != node->expType)
                        {
                            char buff[64];

                            exprToStr(node->child[0]->expType, buff);

                            if (node->child[0]->expType != UndefinedType)
                            {
                                printf("ERROR(%d): Initializer for variable '%s' of type %s is of type %s\n",
                                       node->lineno,
                                       node->attr.name,
                                       nodeType,
                                       buff);

                                ERROR_COUNT++;
                            }
                        }

                        if (node->isArray && !node->child[0]->isArray)
                        {
                            printf("ERROR(%d): Initializer for variable '%s' requires both operands be arrays or not but variable is an array and rhs is not an array.\n",
                                   node->lineno,
                                   node->attr.name);

                            ERROR_COUNT++;
                        }
                        else if (!node->isArray && node->child[0]->isArray)
                        {
                            printf("ERROR(%d): Initializer for variable '%s' requires both operands be arrays or not but variable is not an array and rhs is an array.\n",
                                   node->lineno,
                                   node->attr.name);

                            ERROR_COUNT++;
                        }

                        node->isInit = true;
                    }

                    break;

                case FuncK:
                    if (node->attr.name == NULL)
                    {
                        printf("internal error NULL REACHED in attrName funck\n");
                        break;
                    }

                    localOffset = -2;

                    node->isFunc = true;

                    if (sTab->insertGlobal(std::string(node->attr.string), node))
                    {
                        node->depth = sTab->depth();
                    }

                    else
                    {
                        lookupNode = (treeNode *)sTab->lookup(node->attr.string);
                        printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
                               node->lineno,
                               lookupNode->attr.string,
                               lookupNode->lineno);
                        ERROR_COUNT++;
                    }

                    sTab->enter(std::string(node->attr.string));

                    if (node->isFunc && !node->isIo)
                        functionNodePtr = node;
                    validateChildNodes(node, sTab, SUPPRESS_CHILD_SCOPE);

                    functionNodePtr = NULL;

                    if (!returnStmtFound)
                    {
                        if (!node->isIo)
                        {
                            if (node->expType != Void)
                            {
                                printf("WARNING(%d): Expecting to return type %s but function '%s' has no return statement.\n", node->lineno, nodeType, node->attr.string);
                                WARNING_COUNT++;
                            }
                        }
                    }

                    else
                    {

                        returnStmtFound = false;
                    }

                    sTab->applyToAll(verifySymbolUsage);

                    node->size = -2 - node->numParams;
                    node->scope = Global;

                    sTab->leave();

                    loopDepth = 0;
                    break;

                case ParamK:
                    if (node->attr.name == NULL)
                    {
                        printf("internal error NULL REACHED in attrName Paramk\n");
                        break;
                    }

                    node->isInit = true;
                    node->isParam = true;

                    if (!sTab->insert(std::string(node->attr.name), (void *)node))
                    {
                        lookupNode = (treeNode *)sTab->lookup(node->attr.string);
                        printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
                               node->lineno,
                               lookupNode->attr.string,
                               lookupNode->lineno);
                        ERROR_COUNT++;
                    }
                    node->depth = sTab->depth();

                    validateChildNodes(node, sTab, !SUPPRESS_CHILD_SCOPE);

                    node->scope = Parameter;
                    node->loc = localOffset;
                    node->size = 1;

                    localOffset--;

                    node->parent->numParams++;
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
                    validateChildNodes(node, sTab, !SUPPRESS_CHILD_SCOPE);

                    if (node->op == OPEN_BRACK)
                    {

                        if (node->child[0] != NULL)
                        {
                            node->expType = node->child[0]->expType;
                            node->undeclared = node->child[0]->undeclared;
                        }

                        lookupNode = (treeNode *)sTab->lookup(std::string(node->child[0]->attr.name));
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

                        if (node->child[1]->expType != Integer && node->child[1]->expType != UndefinedType)
                        {

                            if (!node->child[1]->isFunc)
                            {
                                char buff[64];
                                exprToStr(node->child[1]->expType, buff);
                                printf("ERROR(%d): Array '%s' should be indexed by type int but got type %s.\n",
                                       node->lineno, node->child[0]->attr.name, buff);
                                ERROR_COUNT++;
                            }
                        }

                        if (node->child[1]->nodekind == ExpK && node->child[1]->subkind.exp == IdK)
                        {
                            lookupNode = (treeNode *)sTab->lookup(std::string(node->child[1]->attr.name));
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
                            verifySize(node, sTab);

                        else
                            node->expType = verifyNodeTypes(node, node->child[0], node->child[1]);
                    }
                    break;
                case ConstantK:
                    validateChildNodes(node, sTab, !SUPPRESS_CHILD_SCOPE);

                    node->isConst = true;

                    node->scope = Global;

                    node->loc = globalOffset;
                    globalOffset -= node->size;

                    break;

                case IdK:

                    lookupNode = (treeNode *)sTab->lookup(std::string(node->attr.name));

                    if (lookupNode == NULL)
                    {

                        printf("ERROR(%d): Symbol '%s' is not declared.\n", node->lineno, node->attr.name);
                        ERROR_COUNT++;

                        node->undeclared = true;
                    }

                    else
                    {

                        lookupNode->isUsed = true;

                        node->expType = lookupNode->expType;
                        node->size = lookupNode->size;
                        node->scope = lookupNode->scope;
                        node->loc = lookupNode->loc;
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
                    validateChildNodes(node, sTab, !SUPPRESS_CHILD_SCOPE);

                    break;

                case AssignK:
                {
                    validateChildNodes(node, sTab, !SUPPRESS_CHILD_SCOPE);

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
                            lookupNode = (treeNode *)sTab->lookup(std::string(std::string(childNodeRef->attr.name)));

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
                            verifySize(node, sTab);

                        else
                            node->expType = verifyNodeTypes(node, node->child[0], node->child[1]);
                    }

                    break;
                }
                case InitK:
                    validateChildNodes(node, sTab, !SUPPRESS_CHILD_SCOPE);

                    break;

                case CallK:
                    lookupNode = (treeNode *)sTab->lookup(std::string(node->attr.name));
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

                    lookupNode = (treeNode *)sTab->lookupGlobal(std::string(node->attr.name));
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

                    validateChildNodes(node, sTab, !SUPPRESS_CHILD_SCOPE);

                    if (node != NULL)
                    {
                        TreeNode *tmpNode = node->child[0];
                        while (tmpNode != NULL)
                        {

                            node->numParams++;

                            tmpNode = tmpNode->sibling;
                        }
                    }

                    if (lookupNode != NULL)
                    {

                        if (node->numParams < lookupNode->numParams)
                        {

                            printf("ERROR(%d): Too few parameters passed for function '%s' declared on line %d.\n", node->lineno, lookupNode->attr.string, lookupNode->lineno);
                            ERROR_COUNT++;
                        }

                        if (node->numParams > lookupNode->numParams)
                        {

                            printf("ERROR(%d): Too many parameters passed for function '%s' declared on line %d.\n", node->lineno, lookupNode->attr.string, lookupNode->lineno);
                            ERROR_COUNT++;
                        }
                        char lookupBuff[64];
                        char currNodeBuff[64];

                        int paramIndex = 1;

                        for (TreeNode *tmpCurrNode = node->child[0], *tmpLookupNode = lookupNode->child[0];
                             (tmpCurrNode != NULL) && (tmpLookupNode != NULL);
                             tmpCurrNode = tmpCurrNode->sibling, tmpLookupNode = tmpLookupNode->sibling)
                        {

                            exprToStr(tmpLookupNode->expType, lookupBuff);
                            exprToStr(tmpCurrNode->expType, currNodeBuff);

                            if (tmpCurrNode->expType != tmpLookupNode->expType)
                            {

                                if (tmpCurrNode->expType != UndefinedType)
                                {
                                    printf("ERROR(%d): Expecting type %s in parameter %d of call to '%s' declared on line %d but got type %s.\n",
                                           node->lineno,
                                           lookupBuff,
                                           paramIndex,
                                           lookupNode->attr.string,
                                           lookupNode->lineno,
                                           currNodeBuff);
                                    ERROR_COUNT++;
                                }
                            }

                            if (tmpLookupNode->isArray && !tmpCurrNode->isArray)
                            {
                                printf("ERROR(%d): Expecting array in parameter %d of call to '%s' declared on line %d.\n",
                                       node->lineno,
                                       paramIndex,
                                       lookupNode->attr.string,
                                       lookupNode->lineno);
                                ERROR_COUNT++;
                            }
                            else if (!tmpLookupNode->isArray && tmpCurrNode->isArray)
                            {
                                printf("ERROR(%d): Not expecting array in parameter %d of call to '%s' declared on line %d.\n",
                                       node->lineno,
                                       paramIndex,
                                       lookupNode->attr.string,
                                       lookupNode->lineno);
                                ERROR_COUNT++;
                            }
                            paramIndex++;
                        }
                    }

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

        if (node->sibling == NULL && node->parent == NULL)
        {

            tailOfTree = node;
            sTab->applyToAllGlobal(verifySymbolUsage);
        }

        node = node->sibling;
    }
}

void verifySymbolUsage(std::string symbolName, void *ptr)
{
    treeNode *nodeptr;
    nodeptr = (treeNode *)ptr;

    if (!nodeptr->isUsed)
    {

        if (nodeptr->isFunc)
        {
            if (strcmp(nodeptr->attr.string, "main") != 0)
            {
                printf("WARNING(%d): The function '%s' seems not to be used.\n",
                       nodeptr->lineno, symbolName.c_str());
                WARNING_COUNT++;
            }
        }
        else if (nodeptr->isParam)
        {
            printf("WARNING(%d): The parameter '%s' seems not to be used.\n",
                   nodeptr->lineno, symbolName.c_str());
            WARNING_COUNT++;
        }
        else
        {
            printf("WARNING(%d): The variable '%s' seems not to be used.\n",
                   nodeptr->lineno, symbolName.c_str());
            WARNING_COUNT++;
        }
    }
}

void validateChildNodes(TreeNode *node, SymbolTable *sTab, bool suppressChildScope)
{

    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        if (node->child[i] != NULL)
        {

            checkTree2(sTab, node->child[i], suppressChildScope, node);
        }
    }
}

void symbolLibrary(SymbolTable *sTab)
{
    TreeNode *ioTree = NULL;
    TreeNode *ioTreeNode = NULL;
    TreeNode *childIoTreeNode = NULL;

    ioTree = newDeclNode(FuncK, Integer);
    ioTree->attr.name = strdup("input");
    ioTree->isFunc = true;
    ioTree->lineno = -1;
    ioTree->isUsed = true;
    ioTree->isIo = true;

    ioTreeNode = newDeclNode(FuncK, Boolean);
    ioTreeNode->attr.name = strdup("inputb");
    ioTreeNode->isFunc = true;
    ioTreeNode->lineno = -1;
    ioTreeNode->isUsed = true;
    ioTreeNode->isIo = true;

    addSibling(ioTree, ioTreeNode);

    ioTreeNode = newDeclNode(FuncK, Char);
    ioTreeNode->attr.name = strdup("inputc");
    ioTreeNode->isFunc = true;
    ioTreeNode->lineno = -1;
    ioTreeNode->isUsed = true;
    ioTreeNode->isIo = true;

    addSibling(ioTree, ioTreeNode);

    childIoTreeNode = newDeclNode(ParamK, Integer);
    childIoTreeNode->attr.name = strdup("*dummy*");
    childIoTreeNode->lineno = -1;
    childIoTreeNode->isUsed = true;
    childIoTreeNode->isIo = true;
    ioTreeNode->isIo = true;

    ioTreeNode = newDeclNode(FuncK, Void, NULL, childIoTreeNode);
    ioTreeNode->attr.name = strdup("output");
    ioTreeNode->isFunc = true;
    ioTreeNode->lineno = -1;
    ioTreeNode->isUsed = true;
    ioTreeNode->isIo = true;

    addSibling(ioTree, ioTreeNode);

    childIoTreeNode = newDeclNode(ParamK, Boolean);
    childIoTreeNode->attr.name = strdup("*dummy*");
    childIoTreeNode->lineno = -1;
    childIoTreeNode->isUsed = true;
    childIoTreeNode->isIo = true;
    ioTreeNode->isIo = true;

    ioTreeNode = newDeclNode(FuncK, Void, NULL, childIoTreeNode);
    ioTreeNode->attr.name = strdup("outputb");
    ioTreeNode->isFunc = true;
    ioTreeNode->lineno = -1;
    ioTreeNode->isUsed = true;
    ioTreeNode->isIo = true;

    addSibling(ioTree, ioTreeNode);

    childIoTreeNode = newDeclNode(ParamK, Char);
    childIoTreeNode->attr.name = strdup("*dummy*");
    childIoTreeNode->lineno = -1;
    childIoTreeNode->isUsed = true;
    childIoTreeNode->isIo = true;
    ioTreeNode->isIo = true;

    ioTreeNode = newDeclNode(FuncK, Void, NULL, childIoTreeNode);
    ioTreeNode->attr.name = strdup("outputc");
    ioTreeNode->isFunc = true;
    ioTreeNode->lineno = -1;
    ioTreeNode->isUsed = true;
    ioTreeNode->isIo = true;

    addSibling(ioTree, ioTreeNode);

    ioTreeNode = newDeclNode(FuncK, Void);
    ioTreeNode->attr.name = strdup("outnl");
    ioTreeNode->isFunc = true;
    ioTreeNode->lineno = -1;
    ioTreeNode->isUsed = true;
    ioTreeNode->isIo = true;

    addSibling(ioTree, ioTreeNode);

    checkTree2(sTab, ioTree, false, NULL);
}

ExpType verifyNodeTypes(TreeNode *parentNode, treeNode *leftNode, treeNode *rightNode)
{
    ExpType lhs, rhs;

    char buff1[64];
    char buff2[64];

    if (parentNode->subkind.exp == OpK)
    {
        OpKind op = parentNode->op;
        if (op == PLUS || op == MINUS || op == DIV || op == MOD || op == MAX || op == MIN || op == MULT)
        {
            lhs = leftNode->expType;
            rhs = rightNode->expType;

            if ((leftNode != NULL && rightNode != NULL) && (leftNode->isConst && rightNode->isConst))
                parentNode->isConst = true;

            if (lhs == Integer && rhs == Integer)
            {

                if (!leftNode->isArray && !rightNode->isArray)
                {

                    return Integer;
                }

                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                ERROR_COUNT++;

                return Integer;
            }

            exprToStr(lhs, buff1);
            exprToStr(rhs, buff2);
            if (lhs == Integer && rhs != Integer)
            {

                if (rhs != UndefinedType)
                {

                    if (rhs == Void && !rightNode->isFunc)
                    {
                        printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n",
                               parentNode->lineno, parentNode->attr.string,
                               buff2);
                        ERROR_COUNT++;
                    }
                    else if (rhs != Void && !rightNode->isFunc)
                    {
                        printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n",
                               parentNode->lineno, parentNode->attr.string,
                               buff2);
                        ERROR_COUNT++;
                    }
                }
            }
            else if (lhs != Integer && rhs == Integer)
            {

                if (lhs != UndefinedType)
                {

                    if (lhs == Void && !leftNode->isFunc)
                    {
                        printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n",
                               parentNode->lineno, parentNode->attr.string,
                               buff1);
                        ERROR_COUNT++;
                    }
                    else if (lhs != Void && !leftNode->isFunc)
                    {
                        printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n",
                               parentNode->lineno, parentNode->attr.string,
                               buff1);
                        ERROR_COUNT++;
                    }
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
                else if (lhs != UndefinedType)
                {
                    printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff1);
                    ERROR_COUNT++;
                }
                else if (rhs != UndefinedType)
                {
                    printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff2);
                    ERROR_COUNT++;
                }
            }
            if (leftNode->isArray || rightNode->isArray)
            {
                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                ERROR_COUNT++;
            }
            return Integer;
        }
        else if (op == CHSIGN || op == QUESTION)
        {

            if (leftNode->isConst && op == CHSIGN)
                parentNode->isConst = true;

            lhs = leftNode->expType;

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

                if (leftNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, op == CHSIGN ? "chsign" : "?");
                    ERROR_COUNT++;
                }

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

                if (leftNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, op == CHSIGN ? "chsign" : "?");
                    ERROR_COUNT++;
                }
            }

            return Integer;
        }

        else if (op == LEQ || op == LESS || op == GREATER || op == GEQ || op == EQ || op == NEQ)
        {
            lhs = leftNode->expType;
            rhs = rightNode->expType;

            if (op == EQ || op == NEQ)
            {
                if ((!leftNode->isArray && rightNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
                else if (leftNode->isArray && (!rightNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
            }
            else if (op == GEQ || op == LEQ || op == LESS || op == GREATER)
            {
                if ((!leftNode->isArray && rightNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
                else if (leftNode->isArray && (!rightNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
            }

            if (lhs == rhs)
            {
                parentNode->isConst = true;
                return Boolean;
            }

            exprToStr(lhs, buff1);
            exprToStr(rhs, buff2);

            if (lhs != UndefinedType && rhs != UndefinedType)
            {
                printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
                       parentNode->lineno, parentNode->attr.string, buff1, buff2);
                ERROR_COUNT++;
            }

            return Boolean;
        }
        else if (op == AND || op == OR)
        {
            lhs = leftNode->expType;
            rhs = rightNode->expType;
            if (lhs == Boolean && rhs == Boolean)
            {
                if (leftNode->isArray || rightNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                    return UndefinedType;
                }

                parentNode->isConst = true;

                return Boolean;
            }

            exprToStr(lhs, buff1);
            exprToStr(rhs, buff2);

            if (lhs != UndefinedType || rhs != UndefinedType)
            {

                if (lhs == Boolean && rhs != Boolean && rhs != UndefinedType)
                {
                    printf("ERROR(%d): '%s' requires operands of type bool but rhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff2);
                    ERROR_COUNT++;
                }
                else if (lhs != Boolean && lhs != UndefinedType && rhs == Boolean)
                {
                    printf("ERROR(%d): '%s' requires operands of type bool but lhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff1);
                    ERROR_COUNT++;
                }
                else
                {
                    if (lhs != UndefinedType && lhs != Boolean)
                    {
                        printf("ERROR(%d): '%s' requires operands of type bool but lhs is of type %s.\n",
                               parentNode->lineno, parentNode->attr.string,
                               buff1);
                        ERROR_COUNT++;
                    }

                    if (rhs != UndefinedType && rhs != Boolean)
                    {
                        printf("ERROR(%d): '%s' requires operands of type bool but rhs is of type %s.\n",
                               parentNode->lineno, parentNode->attr.string,
                               buff2);
                        ERROR_COUNT++;
                    }
                }

                if (leftNode->isArray || rightNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
                return Boolean;
            }
            else
                return Boolean;
        }

        else if (op == NOT)
        {
            lhs = leftNode->expType;

            if (lhs == Boolean)
            {
                if (leftNode->isArray)
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

            if (leftNode->isArray)
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
            lhs = leftNode->expType;
            rhs = rightNode->expType;

            exprToStr(lhs, buff1);
            exprToStr(rhs, buff2);
            if (lhs == rhs)
            {
                if (leftNode->isArray && rightNode->isArray)
                {
                    parentNode->isArray = true;
                    return lhs;
                }

                else if (leftNode->isArray && !(rightNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n",
                           parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
                else if (!(leftNode->isArray) && rightNode->isArray)
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n",
                           parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }

                return lhs;
            }
            else
            {

                if (lhs != UndefinedType && rhs != UndefinedType)
                {

                    if (!leftNode->isFunc && !rightNode->isFunc)
                    {
                        printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
                               parentNode->lineno, parentNode->attr.string, buff1, buff2);
                        ERROR_COUNT++;
                    }
                }

                if (lhs != UndefinedType && leftNode->isArray && !(rightNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n",
                           parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }

                if (rhs != UndefinedType && rightNode->isArray && !(leftNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n",
                           parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
            }

            return lhs;
        }
        else if (op == ADDASS || op == SUBASS || op == MULASS || op == DIVASS)
        {

            lhs = leftNode->expType;
            rhs = rightNode->expType;

            exprToStr(lhs, buff1);
            exprToStr(rhs, buff2);
            if (lhs == Integer && rhs == Integer)
            {

                if (leftNode->isArray || rightNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
                return Integer;
            }

            if (lhs != UndefinedType && rhs != UndefinedType)
            {
                if (lhs == Integer && rhs != Integer)
                {
                    printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff2);
                    ERROR_COUNT++;
                }
                else if (lhs != Integer && rhs == Integer)
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

                if (leftNode->isArray || rightNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }

                return Integer;
            }
            else
                return Integer;
        }

        else if (op == DEC || op == INC)
        {
            lhs = leftNode->expType;

            exprToStr(lhs, buff1);

            if (lhs == Integer)
            {
                if (leftNode->isArray)
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

                if (leftNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    ERROR_COUNT++;
                }
            }
            return Integer;
        }
        else if (op == AND || op == OR)
        {
            lhs = leftNode->expType;
            rhs = rightNode->expType;
            if (lhs == Boolean && rhs == Boolean)
            {
                parentNode->isConst = true;
                return Boolean;
            }

            exprToStr(lhs, buff1);
            exprToStr(rhs, buff2);

            if (lhs == Boolean && rhs != Boolean)
            {
                printf("ERROR(%d): '%s' requires operands of type bool but rhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff2);
                ERROR_COUNT++;
            }
            else if (lhs != Boolean && rhs == Boolean)
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
            lhs = leftNode->expType;

            if (lhs == Boolean)
            {
                if (leftNode->isArray)
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

            if (leftNode->isArray)
            {
                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                ERROR_COUNT++;
            }
            return Boolean;
        }
    }

    return UndefinedType;
}
