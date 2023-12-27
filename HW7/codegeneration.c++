#include "node.h"
#include "parser.tab.h"
#include "symbolTable.h"
#include "emitcode.h"
#include "codegeneration.h"
#include <string.h>
#include <string>
#include <stack>

std::stack<int> locationStack;
SymbolTable *globalSymTab;

extern int localOffset;
extern int globalOffset;

extern char inputFile[256];

static bool suppressCompoundBody = false;

int tempOffset = 0;
int mainOffset = 0;

treeNode *lookupSymbol(char *nodeName, char *calledFrom, SymbolTable *symTab)
{
    treeNode *tmpNode = NULL;
    tmpNode = (treeNode *)symTab->lookup(std::string(nodeName));
    if (tmpNode == NULL)
    {
        printf("Symbol cannot be found \n");
        exit(-1);
    }

    return tmpNode;
}

void funcPrint(char *funcName, bool isTop)
{
    if (isTop)
    {
        emitComment((char *)"FUNCTION", funcName);
    }
    else
    {
        emitComment((char *)"END FUNCTION", funcName);
        emitComment((char *)"");
        emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");
    }
}

void ioSetup(SymbolTable *symTab)
{
    emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");

    TreeNode *lookupNode = NULL;
    lookupNode = (treeNode *)symTab->lookup(std::string("input"));

    if (lookupNode == NULL)
    {
        printf("Symbol Table lookup failed \n");
        exit(-1);
    }

    lookupNode->loc = emitWhereAmI();

    funcPrint("input", true);

    emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
    emitRO((char *)"IN", 2, 2, 2, (char *)"Grab int input");
    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
    emitGoto(0, 3, (char *)"Return");

    funcPrint("input", false);

    lookupNode = (treeNode *)symTab->lookup(std::string("input"));

    if (lookupNode == NULL)
    {
        printf("Symbol Table lookup failed \n");
        exit(-1);
    }

    lookupNode->loc = emitWhereAmI();

    funcPrint("output", true);

    emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
    emitRM((char *)"LD", 3, -2, 1, (char *)"Load parameter");
    emitRO((char *)"OUT", 3, 3, 3, (char *)"Output integer");
    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
    emitGoto(0, 3, (char *)"Return");

    funcPrint("output", false);

    lookupNode = (treeNode *)symTab->lookup(std::string("input"));

    if (lookupNode == NULL)
    {
        printf("Symbol Table lookup failed \n");
        exit(-1);
    }

    lookupNode->loc = emitWhereAmI();

    funcPrint("inputb", true);

    emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
    emitRO((char *)"INB", 2, 2, 2, (char *)"Grab bool input");
    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
    emitGoto(0, 3, (char *)"Return");

    funcPrint("inputb", false);

    lookupNode = (treeNode *)symTab->lookup(std::string("input"));

    if (lookupNode == NULL)
    {
        printf("Symbol Table lookup failed \n");
        exit(-1);
    }

    lookupNode->loc = emitWhereAmI();

    funcPrint("outputb", true);

    emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
    emitRM((char *)"LD", 3, -2, 1, (char *)"Load parameter");
    emitRO((char *)"OUTB", 3, 3, 3, (char *)"Output bool");
    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
    emitGoto(0, 3, (char *)"Return");

    funcPrint("outputb", false);

    lookupNode = (treeNode *)symTab->lookup(std::string("input"));

    if (lookupNode == NULL)
    {
        printf("Symbol Table lookup failed \n");
        exit(-1);
    }

    lookupNode->loc = emitWhereAmI();

    funcPrint("inputc", true);

    emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
    emitRO((char *)"INC", 2, 2, 2, (char *)"Grab char input");
    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
    emitGoto(0, 3, (char *)"Return");

    funcPrint("inputc", false);

    lookupNode = (treeNode *)symTab->lookup(std::string("input"));

    if (lookupNode == NULL)
    {
        printf("Symbol Table lookup failed \n");
        exit(-1);
    }

    lookupNode->loc = emitWhereAmI();

    funcPrint("outputc", true);

    emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
    emitRM((char *)"LD", 3, -2, 1, (char *)"Load parameter");
    emitRO((char *)"OUTC", 3, 3, 3, (char *)"Output char");
    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
    emitGoto(0, 3, (char *)"Return");

    funcPrint("outputc", false);

    lookupNode = (treeNode *)symTab->lookup(std::string("input"));

    if (lookupNode == NULL)
    {
        printf("Symbol Table lookup failed \n");
        exit(-1);
    }

    lookupNode->loc = emitWhereAmI();

    funcPrint("outnl", true);

    emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
    emitRO((char *)"OUTNL", 3, 3, 3, (char *)"Output a newline");
    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
    emitGoto(0, 3, (char *)"Return");

    funcPrint("outnl", false);
}

void validateChildNodes(TreeNode *node, SymbolTable *symTab)
{

    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        if (node->child[i] != NULL)
        {
                        traverse(symTab, node->child[i]);
        }
    }
}

void adjustTempOffset(int amount)
{
    if (amount > 0)
    {
        tempOffset++;
        emitComment((char *)"TOFF inc:", tempOffset);
        adjustTempOffset(amount - 1);
    }
    else if (amount < 0)
    {
        tempOffset--;
        emitComment((char *)"TOFF dec:", tempOffset);
        adjustTempOffset(amount + 1);
    }
}

void emitOperator(treeNode *node)
{
    switch (node->op)
    {
        case MULT:
            emitRO((char *)"MUL", 3, 4, 3, (char *)"Op *");
            break;
        case PLUS:
            emitRO((char *)"ADD", 3, 4, 3, (char *)"Op +");
            break;
        case MINUS:
            emitRO((char *)"SUB", 3, 4, 3, (char *)"Op -");
            break;
        case DIV:
            emitRO((char *)"DIV", 3, 4, 3, (char *)"Op /");
            break;
        case MOD:
            emitRO((char *)"MOD", 3, 4, 3, (char *)"Op %");
            break;
        case AND:
            emitRO((char *)"AND", 3, 4, 3, (char *)"Op AND");
            break;
        case OR:
            emitRO((char *)"OR", 3, 4, 3, (char *)"Op OR");
            break;
        case EQ:
            emitRO((char *)"TEQ", 3, 4, 3, (char *)"Op ==");
            break;
        case NEQ:
            emitRO((char *)"TNE", 3, 4, 3, (char *)"Op !=");
            break;
        case CHSIGN:
            emitRO((char *)"NEG", 3, 3, 3, (char *)"Op unary -");
            break;
        case NOT:
            emitRM((char *)"LDC", 4, 1, 6, (char *)"Load 1");
            emitRO((char *)"XOR", 3, 3, 4, (char *)"Op XOR to get logical not");
            break;
        case QUESTION:
            emitRO((char *)"RND", 3, 3, 6, (char *)"Op ?");
            break;
        case GREATER:
            emitRO((char *)"TGT", 3, 4, 3, (char *)"Op >");
            break;
        case LESS:
            emitRO((char *)"TLT", 3, 4, 3, (char *)"Op <");
            break;
        case GEQ:
            emitRO((char *)"TGE", 3, 4, 3, (char *)"Op >=");
            break;
        case LEQ:
            emitRO((char *)"TLE", 3, 4, 3, (char *)"Op <=");
            break;
        case ADDASS:
            emitRO((char *)"ADD", 3, 4, 3, (char *)"Op +=");
            break;
        case SUBASS:
            emitRO((char *)"SUB", 3, 4, 3, (char *)"Op -=");
            break;
        case MULASS:
            emitRO((char *)"MUL", 3, 4, 3, (char *)"Op *=");
            break;
        case DIVASS:
            emitRO((char *)"DIV", 3, 4, 3, (char *)"Op /=");
            break;

        default:
            printf("Error: Unknown operator in emitOperator\n");
            exit(-1);
    }
}


void processIfK(TreeNode *node, SymbolTable *symTab) {
    int jumpTrue, jumpFalse;

        if (node->child[2] == NULL)
    {
                emitComment((char *)"IF");
        traverse(symTab, node->child[0]);
        jumpTrue = emitSkip(1);
        emitComment((char *)"THEN");
        traverse(symTab, node->child[1]);

        backPatchAJumpToHere((char *)"JZR", 3, jumpTrue, (char *)"Jump around the THEN if false [backpatch]");

        emitComment((char *)"END IF");
    }
    else
    {
                emitComment((char *)"IF");
        traverse(symTab, node->child[0]);
        jumpTrue = emitSkip(1);
        emitComment((char *)"THEN");
        traverse(symTab, node->child[1]);
        jumpFalse = emitSkip(1);

        backPatchAJumpToHere((char *)"JZR", 3, jumpTrue, (char *)"Jump around the THEN if false [backpatch]");

                emitComment((char *)"ELSE");
        traverse(symTab, node->child[2]);

        backPatchAJumpToHere(jumpFalse, (char *)"Jump around the ELSE [backpatch]");

        emitComment((char *)"END IF");
    }
}

void processBreakK()
{
    emitComment((char *)"BREAK");
    emitGotoAbs(locationStack.top(), (char *)"break");
}


void processOpK(TreeNode *node, SymbolTable *symTab)
{

        if (node->op == OPEN_BRACK && node->side == Left)
    {
        validateChildNodes(node, symTab);
        emitRM((char *)"ST", 3, tempOffset, 1, (char *)"Push index");
        adjustTempOffset(-1);

    }
    else if (node->op == OPEN_BRACK && (node->parent->op == INC || node->parent->op == DEC))
    {
        validateChildNodes(node, symTab);
    }
            else if (node->op == OPEN_BRACK)
    {

                if (node->child[0]->scope == Local)
            emitRM((char *)"LDA", 3, (node->child[0]->loc) - 1, 1, (char *)"Load address of base of array", node->child[0]->attr.name);
        else if (node->child[0]->scope == Global || node->child[0]->scope == LocalStatic)
            emitRM((char *)"LDA", 3, (node->child[0]->loc) - 1, 0, (char *)"Load address of base of array", node->child[0]->attr.name);
        else if (node->child[0]->scope == Parameter)
            emitRM((char *)"LD", 3, (node->child[0]->loc), 1, (char *)"Load address of base of array", node->child[0]->attr.name);

                emitRM((char *)"ST", 3, tempOffset, 1, (char *)"Push left side");
        adjustTempOffset(-1);
                validateChildNodes(node, symTab);

                adjustTempOffset(1);
        emitRM((char *)"LD", 4, tempOffset, 1, (char *)"Pop left into ac1");

                emitRO((char *)"SUB", 3, 4, 3, (char *)"compute location from index");

                emitRM((char *)"LD", 3, 0, 3, (char *)"Load array element");
    }
    else if (node->op == SIZEOF)
    {
        traverse(symTab, node->child[0]);
        emitRM((char *)"LD", 3, 1, 3, "Load array size");
    }
            else
    {
        if (node->child[0] == NULL)
        {
            printf("ERROR CODE GEN OPK, EXPECTING LHS IN BINARY OPERATOR, RECIEVED NULL...\nNOW QUITTING\n");
            exit(-1);
        }

                traverse(symTab, node->child[0]);

                        if (node->child[1] != NULL)
        {
                        emitRM((char *)"ST", 3, tempOffset, 1, (char *)"Push left side");
            adjustTempOffset(-1);
                        traverse(symTab, node->child[1]);

                        adjustTempOffset(1);
            emitRM((char *)"LD", 4, tempOffset, 1, (char *)"Pop left into ac1");
        }

                emitOperator(node);
    }
}
void processConstK(TreeNode *node)
{
    if (node->parent->subkind.decl == VarK && node->isArray) {}
    else if (node->expType == Integer)
    {
        emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load integer constant");
    }
    else if (node->expType == Boolean)
    {
        emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load Boolean constant");
    }
    else if (node->expType == Char)
    {
        emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load char constant");
    }
}

void processIdK(TreeNode *node, SymbolTable *symTab)
{
    if (node->parent->isOp && node->parent->op == OPEN_BRACK)
    {
                if (node->parent->child[1] == node)
        {
            if (node->scope == Local)
                emitRM((char *) "LD", 3, node->loc, 1, (char *) "Load variable", node->attr.string);
            else if (node->scope == Global || node->scope == LocalStatic)
                emitRM((char *) "LD", 3, node->loc, 0, (char *) "Load variable", node->attr.string);
            else if (node->scope == Parameter)
                emitRM((char *) "LD", 3, node->loc, 1, (char *) "Load variable", node->attr.string);
        }
    }
}

void processInitK(TreeNode *node, SymbolTable *symTab)
{
    validateChildNodes(node, symTab);
}

void processCallK(TreeNode *node, SymbolTable *symTab)
{
    treeNode *tmpNode;
    treeNode *lookupNode;

    int ghostFrameToff = 0;

    emitComment((char *)"EXPRESSION");
    emitComment((char *)"CALL", node->attr.name);

        ghostFrameToff = tempOffset;
    emitRM((char *)"ST", 1, tempOffset, 1, (char *)"Store fp in ghost frame for", node->attr.name);
        adjustTempOffset(-2);
        tmpNode = node;

        node = node->child[0];

    for (int i = 1; node != NULL; i++)
    {
        emitComment((char *)"Param", i);

        processTreeNode(symTab, node);

                emitRM((char *)"ST", 3, tempOffset, 1, (char *)"Push parameter");
                adjustTempOffset(-1);

        node = node->sibling;
    }
        node = tmpNode;
    emitComment((char *)"Param end", node->attr.name);

    lookupNode = lookupSymbol(node->attr.name, (char *)"CallK", symTab);

    emitRM((char *)"LDA", 1, ghostFrameToff, 1, (char *)"Ghost frame becomes new active frame");
    emitRM((char *)"LDA", 3, 1, 7, (char *)"Return address in ac");
    if (lookupNode->isIo)
        emitGotoAbs(lookupNode->loc, (char *)"CALL", node->attr.name);
                    else
        emitGotoAbs(lookupNode->loc + 39, (char *)"CALL", node->attr.name);

    emitRM((char *)"LDA", 3, 0, 2, (char *)"Save the result in ac");

    emitComment((char *)"Call end", node->attr.name);

        tempOffset = ghostFrameToff;
    emitComment((char *)"TOFF set:", tempOffset);
}

void processAssignK(TreeNode *node, SymbolTable *symTab)
{

    validateChildNodes(node, symTab);

    if (node->op == ADDASS || node->op == SUBASS || node->op == DIVASS || node->op == MULASS || node->op == ASS)
    {

                if (node->child[0]->isOp && node->child[0]->op == OPEN_BRACK)
        {
                        adjustTempOffset(1);
            emitRM((char *)"LD", 4, tempOffset, 1, (char *)"Pop index");

                        if (node->child[0]->scope == Local)
                emitRM((char *)"LDA", 5, (node->child[0]->loc) - 1, 1, (char *)"Load address of base of array", node->child[0]->indentArray);
            else if (node->child[0]->scope == Global || node->child[0]->scope == LocalStatic)
                emitRM((char *)"LDA", 5, (node->child[0]->loc) - 1, 0, (char *)"Load address of base of array", node->child[0]->indentArray);
            else if (node->child[0]->scope == Parameter)
                emitRM((char *)"LD", 5, (node->child[0]->loc), 1, (char *)"Load address of base of array", node->child[0]->indentArray);

                        emitRO((char *)"SUB", 5, 5, 4, (char *)"Compute offset of value");

            if (node->op != ASS)
            {
                                emitRM((char *)"LD", 4, 0, 5, (char *)"load lhs variable of", node->child[0]->indentArray);

                                emitOperator(node);
            }

                        emitRM((char *)"ST", 3, 0, 5, (char *)"Store variable", node->child[0]->indentArray);
        }
                    else
        {

            if (node->op != ASS)
            {
                                if (node->child[0]->scope == Local)
                    emitRM((char *)"LD", 4, (node->child[0]->loc), 1, (char *)"Load lhs variable", node->child[0]->attr.name);
                else if (node->child[0]->scope == Global || node->child[0]->scope == LocalStatic)
                    emitRM((char *)"LD", 4, (node->child[0]->loc), 0, (char *)"Load lhs variable", node->child[0]->attr.name);
                else if (node->child[0]->scope == Parameter)
                    emitRM((char *)"LD", 4, (node->child[0]->loc), 1, (char *)"Load lhs variable", node->child[0]->attr.name);

                                emitOperator(node);
            }
                            else if (node->op == ASS && node->child[0]->isArray && node->child[1]->isArray)
            {
                emitRM((char *)"LDA", 4, (node->child[0]->loc - 1), 1, (char *)"address of lhs");
                emitRM((char *)"LD", 5, 1, 3, (char *)"size of rhs");
                emitRM((char *)"LD", 6, 1, 4, (char *)"size of lhs");

                emitRO((char *)"SWP", 5, 6, 6, (char *)"pick smallest size");

                emitRO((char *)"MOV", 4, 3, 5, (char *)"array op =");
            }

            if(!(node->op == ASS && node->child[0]->isArray && node->child[1]->isArray))
                if (node->child[0]->scope == Local)
                    emitRM((char *)"ST", 3, (node->child[0]->loc), 1, (char *)"Store variable", node->child[0]->attr.name);
                else if (node->child[0]->scope == Global || node->child[0]->scope == LocalStatic)
                    emitRM((char *)"ST", 3, (node->child[0]->loc), 0, (char *)"Store variable", node->child[0]->attr.name);
                else if (node->child[0]->scope == Parameter)
                    emitRM((char *)"ST", 3, (node->child[0]->loc), 1, (char *)"Store variable", node->child[0]->attr.name);
        }
    }
    else if (node->op == INC || node->op == DEC)
    {
                if (node->child[0]->isOp && node->child[0]->op == OPEN_BRACK)
        {
                                    if (node->child[0]->scope == Local)
                emitRM((char *)"LDA", 5, (node->child[0]->loc) - 1, 1, (char *)"Load address of base of array", node->child[0]->indentArray);
            else if (node->child[0]->scope == Global || node->child[0]->scope == LocalStatic)
                emitRM((char *)"LDA", 5, (node->child[0]->loc) - 1, 0, (char *)"Load address of base of array", node->child[0]->indentArray);
            else if (node->child[0]->scope == Parameter)
                emitRM((char *)"LD", 5, (node->child[0]->loc), 1, (char *)"Load address of base of array", node->child[0]->indentArray);

                        emitRO((char *)"SUB", 5, 5, 3, (char *)"Compute offset of value");

                        emitRM((char *)"LD", 3, 0, 5, (char *)"load lhs variable", node->child[0]->indentArray);

                        if (node->op == INC)
                emitRM((char *)"LDA", 3, 1, 3, (char *)"increment value of", node->child[0]->indentArray);
            else
                emitRM((char *)"LDA", 3, -1, 3, (char *)"decrement value of", node->child[0]->indentArray);

                        emitRM((char *)"ST", 3, 0, 5, (char *)"Store variable", node->child[0]->indentArray);
        }
        else if (node->child[0]->subkind.exp == IdK)
        {

            if (node->child[0]->scope == Local)
                emitRM((char *)"LD", 3, (node->child[0]->loc), 1, (char *)"Load lhs variable", node->child[0]->attr.name);
            else if (node->child[0]->scope == Global || node->child[0]->scope == LocalStatic)
                emitRM((char *)"LD", 3, (node->child[0]->loc), 0, (char *)"Load lhs variable", node->child[0]->attr.name);
            else if (node->child[0]->scope == Parameter)
                emitRM((char *)"LD", 3, (node->child[0]->loc), 1, (char *)"Load lhs variable", node->child[0]->attr.name);

            if (node->op == INC)
                emitRM((char *)"LDA", 3, 1, 3, (char *)"increment value of", node->child[0]->attr.name);
            else
                emitRM((char *)"LDA", 3, -1, 3, (char *)"decrement value of", node->child[0]->attr.name);

            if (node->child[0]->scope == Local)
                emitRM((char *)"ST", 3, (node->child[0]->loc), 1, (char *)"Store variable", node->child[0]->attr.name);
            else if (node->child[0]->scope == Global || node->child[0]->scope == LocalStatic)
                emitRM((char *)"ST", 3, (node->child[0]->loc), 0, (char *)"Store variable", node->child[0]->attr.name);
            else if (node->child[0]->scope == Parameter)
                emitRM((char *)"ST", 3, (node->child[0]->loc), 1, (char *)"Store variable", node->child[0]->attr.name);
        }
    }

}

void processParamK(TreeNode *node, SymbolTable *symTab)
{
    validateChildNodes(node, symTab);
}

void processForK(TreeNode *node, SymbolTable *symTab)
{
        tempOffset -= 3;
    emitComment((char *)"TOFF set:", tempOffset);
    emitComment((char *)"FOR");

        int tmpToff = tempOffset;
    int beginOfFor;
    int forFixup;

        processTreeNode(symTab, node->child[0]);

        processTreeNode(symTab, node->child[1]);

        beginOfFor = emitSkip(0);

        emitRM((char *)"LD", 4, tmpToff + 3, 1, (char *)"loop index");
    emitRM((char *)"LD", 5, tmpToff + 2, 1, (char *)"stop value");
    emitRM((char *)"LD", 3, tmpToff + 1, 1, (char *)"step value");
    emitRO((char *)"SLT", 3, 4, 5, (char *)"Op <");
    emitRM((char *)"JNZ", 3, 1, 7, (char *)"Jump to loop body");

    forFixup = emitSkip(1);

        processTreeNode(symTab, node->child[2]);

        emitComment((char *)"Bottom of loop increment and jump");
    emitRM((char *)"LD", 3, tmpToff + 3, 1, (char *)"Load index");
    emitRM((char *)"LD", 5, tmpToff + 1, 1, (char *)"Load step");
    emitRO((char *)"ADD", 3, 3, 5, (char *)"increment");
    emitRM((char *)"ST", 3, tmpToff + 3, 1, (char *)"store back to index");
    emitGotoAbs(beginOfFor, (char *)"go to beginning of loop");
    backPatchAJumpToHere(forFixup, (char *)"Jump past loop [backpatch]");

    emitComment((char *)"END LOOP");
}

void processCompoundK(TreeNode *node, SymbolTable *symTab)
{
    emitComment((char *)"COMPOUND");

    if (node->parent->subkind.stmt != ForK)
        tempOffset = node->size;

    emitComment((char *)"TOFF set:", tempOffset);

    if (node->child[0] != NULL && node->child[0]->nodekind == DeclK && node->child[0]->subkind.decl == VarK)
        suppressCompoundBody = true;
    else
        emitComment((char *)"Compound Body");

    validateChildNodes(node, symTab);

    emitComment((char *)"TOFF set:", tempOffset);

    emitComment((char *)"END COMPOUND");

    suppressCompoundBody = false;
}

void processWhileK(TreeNode *node, SymbolTable *symTab)
{
        int loopStartJump = emitSkip(0);

        emitComment((char *)"WHILE");

        traverse(symTab, node->child[0]);

        int doJump = emitSkip(1);

        int exitJump = emitSkip(1);

        locationStack.push(exitJump);

        backPatchAJumpToHere((char *)"JNZ", 3, doJump, (char *)"Jump to while part");

        emitComment((char *)"DO");

        traverse(symTab, node->child[1]);

        emitGotoAbs(loopStartJump, (char *)"go to beginning of loop");

        backPatchAJumpToHere(exitJump, (char *)"Jump past loop [backpatch]");

        locationStack.pop();

        emitComment((char *)"END WHILE");
}

void processReturnK(TreeNode *node, SymbolTable *symTab)
{
    emitComment((char *)"RETURN");
    validateChildNodes(node, symTab);

        if (node->child[0] != NULL)
        emitRM((char *)"LDA", 2, 0, 3, (char *)"Copy result to return register");

    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
    emitGoto(0, 3, (char *)"Return");
}

void processRangeK(TreeNode *node, SymbolTable *symTab)
{
        processTreeNode(symTab, node->child[0]);
    emitRM((char *)"ST", 3, tempOffset + 3, 1, (char *)"save starting value in index variable");

    processTreeNode(symTab, node->child[1]);
    emitRM((char *)"ST", 3, tempOffset + 2, 1, (char *)"save stop value");

    if (node->child[2] != NULL)
    {
        processTreeNode(symTab, node->child[2]);
        emitRM((char *)"ST", 3, tempOffset + 1, 1, (char *)"save step value");
    }
    else
    {
        emitRM((char *)"LDC", 3, 1, 6, (char *)"default increment by 1");
        emitRM((char *)"ST", 3, tempOffset + 1, 1, (char *)"save step value");
    }
}

void processVarK(TreeNode *node, SymbolTable *symTab)
{
    if (node->child[0] != NULL && node->depth > 1 && !node->isStatic)
    {
        validateChildNodes(node, symTab);

        if (!node->isArray)
            emitRM((char *)"ST", 3, node->loc, 1, (char *)"Store variable", node->attr.name);
    }

    if (node->isArray && node->depth > 1 && !node->isStatic)
    {
        if (node->child[0] == NULL)
            validateChildNodes(node, symTab);

        emitRM((char *)"LDC", 3, node->size - 1, 6, (char *)"load size of array", node->attr.name);
        emitRM((char *)"ST", 3, node->loc, 1, (char *)"save size of array", node->attr.name);
    }

    if (node->child[0] != NULL && node->isArray)
    {
        emitStrLit(node->child[0]->loc - 1, node->child[0]->attr.string);

        emitRM((char *)"LDA", 3, node->child[0]->loc - 1, 0, (char *)"Load address of char array");
        emitRM((char *)"LDA", 4, node->loc - 1, 1, (char *)"address of lhs");
        emitRM((char *)"LD", 5, 1, 3, (char *)"size of rhs");
        emitRM((char *)"LD", 6, 1, 4, (char *)"size of lhs");
        emitRO((char *)"SWP", 5, 6, 6, (char *)"pick smallest size");
        emitRO((char *)"MOV", 4, 3, 5, (char *)"array op =");
    }

    if (node->sibling == NULL && suppressCompoundBody)
    {
        emitComment((char *)"Compound Body");
        emitComment((char *)"EXPRESSION");
    }
}

void processFuncK(TreeNode *node, SymbolTable *symTab)
{
    tempOffset = node->size;

    if (strcmp("main", node->attr.string) == 0)
        mainOffset = emitWhereAmI();

    emitComment((char *)"FUNCTION", node->attr.string);
    emitComment((char *)"TOFF set:", tempOffset);

    emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");

    validateChildNodes(node, symTab);

    emitComment((char *)"Add standard closing in case there is no return statement");

    emitRM((char *)"LDC", 2, 0, 6, (char *)"Set return value to 0");
    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");

    emitGoto(0, 3, (char *)"Return");

    emitComment((char *)"END FUNCTION", node->attr.string);

    if (strcmp("main", node->attr.string) == 0) {}
    else
        emitComment((char *)"");
}

void checkInitGlobal(std::string symbolName, void *ptr)
{
    treeNode *nodeptr;
    nodeptr = (treeNode *)ptr;

        if (!nodeptr->isFunc)
    {

        if (nodeptr->isArray)
        {
            char *tmp = strdup(symbolName.c_str());
            emitRM((char *)"LDC", 3, nodeptr->size - 1, 6, (char *)"load size of array", tmp);
            emitRM((char *)"ST", 3, nodeptr->loc, 0, (char *)"save size of array", tmp);
        }
        else
        {
            char *tmp = strdup(symbolName.c_str());
            if (nodeptr->child[0] != NULL)
            {
                processTreeNode(globalSymTab, nodeptr->child[0]);
                emitRM((char *)"ST", 3, nodeptr->loc, 0, (char *)"Store variable", tmp);
            }
        }
    }
}

void emitInit(SymbolTable *symTab)
{
    backPatchAJumpToHere(0, (char *)"Jump to init [backpatch]");

    emitComment((char *)"INIT");

    emitRM((char *)"LDA", 1, globalOffset, 0, (char *)"set first frame at end of globals");
    emitRM((char *)"ST", 1, 0, 1, (char *)"store old fp (point to self)");

    emitComment((char *)"INIT GLOBALS AND STATICS");

    symTab->applyToAllGlobal(checkInitGlobal);

    emitComment((char *)"END INIT GLOBALS AND STATICS");

    emitRM((char *)"LDA", 3, 1, 7, (char *)"Return address in ac");

    emitGotoAbs(mainOffset, (char *)"Jump to main");

    emitRO((char *)"HALT", 0, 0, 0, (char *)"DONE!");
    emitComment((char *)"END INIT");
}

void traverse(SymbolTable *symTab, TreeNode *node)
{

    while (node != NULL)
    {
        processTreeNode(symTab, node);
        node = node->sibling;
    }
}

void processTreeNode(SymbolTable *symTab, TreeNode *node)
{
    char nodeType[64];
    char scoping[64];

    exprToStr(node->expType, nodeType);
    scopeToStr(node->scope, scoping);

            if (node->nodekind == StmtK)
    {
        switch (node->subkind.stmt)
        {
            case NullK:
                validateChildNodes(node, symTab);
                break;
            case IfK:
                processIfK(node, symTab);
                break;

            case WhileK:
                processWhileK(node, symTab);
                break;

            case ForK:
                processForK(node, symTab);
                break;

            case CompoundK:
                processCompoundK(node, symTab);
                break;

            case ReturnK:
                processReturnK(node, symTab);
                break;

            case BreakK:
                processBreakK();
                break;

            case RangeK:
                processRangeK(node, symTab);
                break;

            default:
                exit(-1);
        }
    }
            else if (node->nodekind == DeclK)
    {
        switch (node->subkind.decl)
        {
            case VarK:
                processVarK(node, symTab);
                break;

            case FuncK:
                processFuncK(node, symTab);
                break;

            case ParamK:
                processParamK(node, symTab);
                break;

            default:
                exit(-1);
        }
    }
            else if (node->nodekind == ExpK)
    {

        switch (node->subkind.exp)
        {
            case OpK:
                processOpK(node, symTab);
                break;

            case ConstantK:
                processConstK(node);
                break;

            case IdK:
                processIdK(node, symTab);
                break;

            case AssignK:
                processAssignK(node, symTab);
                break;

            case InitK:
                processInitK(node, symTab);
                break;

            case CallK:
                processCallK(node, symTab);
                break;

            default:
                exit(-1);
        }
    }

    else
    {
        exit(-1);
    }
}

void emitInit(SymbolTable *symTab)
{
    backPatchAJumpToHere(0, (char *)"Jump to init [backpatch]");

    emitComment((char *)"INIT");

    emitRM((char *)"LDA", 1, globalOffset, 0, (char *)"set first frame at end of globals");
    emitRM((char *)"ST", 1, 0, 1, (char *)"store old fp (point to self)");

    emitComment((char *)"INIT GLOBALS AND STATICS");
        symTab->applyToAllGlobal(checkInitGlobal);

    emitComment((char *)"END INIT GLOBALS AND STATICS");
    emitRM((char *)"LDA", 3, 1, 7, (char *)"Return address in ac");
    emitGotoAbs(mainOffset, (char *)"Jump to main");
    emitRO((char *)"HALT", 0, 0, 0, (char *)"DONE!");
    emitComment((char *)"END INIT");
}

void emit(SymbolTable *symTab, TreeNode *tree)
{
    globalSymTab = symTab;

    emitSkip(1);
    ioSetup(symTab);
    traverse(symTab, tree);
    init_and_globals(symTab);
}