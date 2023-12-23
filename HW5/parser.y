%{
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "scanType.h"
#include "node.h"
#include "ourgetopt.h"
#include "symbolTable.h"
#include "semantic.h"
#include "yyerror.h"

extern int yylex();
extern FILE *yyin;
extern int yydebug;

#define YYERROR_VERBOSE

static char *toUpperString(char *str)
{
    int i = 0;
    while(str[i])
    {
        str[i]=toupper(str[i]);
        i++;
    }
    return str;
}

TreeNode *syntaxTree;


%}

%define parse.error verbose

%union {
    ExpType expType;
    TokenData *tokenData;
    TreeNode *treenode;
}

%token <tokenData> ID NUMCONST CHARCONST STRINGCONST
%token <tokenData> INT BOOL CHAR IF THEN ELSE WHILE DO FOR TO
%token <tokenData> BY RETURN BREAK STATIC NOT AND OR TRUE FALSE
%token <tokenData> OPEN_BRACE CLOSE_BRACE OPEN_PAREN CLOSE_PAREN
%token <tokenData> SEMI COMMA LESS GREATER LEQ GEQ
%token <tokenData> COLON EQ DIV MULT MOD ADDASS ASS
%token <tokenData> OPEN_BRACK CLOSE_BRACK DEC INC PLUS NEQ
%token <tokenData> MIN MAX QUESTION SUBASS MULASS DIVASS
%token <tokenData> MINUS CHSIGN SIZEOF


%type <treenode> program declList decl

%type <treenode> varDecl scopedVarDecl varDeclList varDeclInit varDeclId

%type <treenode> funDecl params paramList paramTypeList paramIdList paramId

%type <treenode> stmt expStmt compoundStmt localDecls stmtList
%type <treenode> iterRange returnStmt breakStmt

%type <treenode> exp simpleExp andExp unaryRelExp relExp  minMaxExp
%type <treenode> sumExp  mulExp unaryExp factor mutable immutable
%type <treenode> call args argList constant matched unmatched
%type <treenode> unmatchedSelectStmt matchedSelectStmt matchedIterStmt unmatchedIterStmt

%type <tokenData> unaryOp relOp sumOp mulOp minMaxOp assignOp

%type <expType> typeSpec




%%

program         : declList {syntaxTree = $1;}
                ;

declList        : declList decl  {
                                   $$ = addSibling($1,$2);
                                   ;
                                   }
                | decl {$$ = $1;}
                ;

decl            : varDecl {$$ = $1;}
                | funDecl {$$ = $1;}
                | error {$$ = NULL;}
                ;

varDecl         : typeSpec varDeclList SEMI { setType($2,$1,false); $$ = $2;}
                | error varDeclList SEMI {$$ = NULL; yyerrok;}
                | typeSpec error SEMI {$$ = NULL; yyerrok; yyerrok;}
                ;
scopedVarDecl   : STATIC typeSpec varDeclList SEMI  { setType($3,$2,true);
                                                    $$=$3;
                                                    yyerrok;
                                                    }
                | typeSpec varDeclList SEMI {   setType($2,$1,false);
                                                $$ = $2;
                                                yyerrok;
                                            }
                ;

varDeclList     : varDeclList COMMA varDeclInit   {
                                                  $$ = addSibling($1,$3); yyerrok;}
                | varDeclInit { $$ = $1; }
                | varDeclList COMMA error {$$ = NULL;}
                | error {$$ = NULL;}
                ;

varDeclInit     : varDeclId {$$ = $1;}
                | varDeclId COLON simpleExp     {$$ = $1;
                                                 if($$ != NULL && $3 != NULL)$$->child[0] = $3;}
                | error COLON simpleExp {$$ = NULL; yyerrok;}
                ;

varDeclId       : ID                                    {$$ = newDeclNode(VarK,UndefinedType,$1);
                                                         $$->attr.name = $1->tokenStr;
                                                         $$->isArray = false;
                                                         $$->attrSet = true;

                                                        }
                | ID OPEN_BRACK NUMCONST CLOSE_BRACK    {$$ = newDeclNode(VarK,UndefinedType,$1);
                                                         $$->attr.name = $1->tokenStr;
                                                         $$->attrSet = true;
                                                         $$->isArray = true;
                                                         $$->arraySize = $3->nValue;
                                                        }
                | ID OPEN_BRACK error {$$= NULL;}
                | error CLOSE_BRACK {$$ = NULL; yyerrok;}
                ;

typeSpec        : INT {$$ = Integer;}
                | BOOL {$$ = Boolean;}
                | CHAR {$$ = Char;}
                ;

funDecl         : typeSpec ID OPEN_PAREN params CLOSE_PAREN stmt    {$$ = newDeclNode(FuncK,$1,$2,$4,$6);
                                                                    $$->attr.name = $2->tokenStr;
                                                                    $$->attrSet = true;

                                                                    }
                | ID OPEN_PAREN params CLOSE_PAREN stmt             {$$ = newDeclNode(FuncK,Void,$1,$3,$5);
                                                                    $$->attr.name = $1->tokenStr;
                                                                    $$->attrSet = true;
                                                                    }
                | typeSpec error {$$ = NULL;}
                | typeSpec ID OPEN_PAREN error {$$ = NULL;}
                | ID OPEN_PAREN error {$$ = NULL;}
                | ID OPEN_PAREN params CLOSE_PAREN error {$$ = NULL;}
                ;

params          : paramList {$$ = $1;}
                |  {$$ = NULL;}
                ;

paramList       : paramList SEMI paramTypeList {
                                                $$ = addSibling($1,$3);}
                | paramTypeList {$$ = $1;}
                | paramList SEMI error {$$ = NULL;}
                | error {$$ = NULL;}
                ;

paramTypeList   : typeSpec paramIdList  {setType($2,$1,false); $$ = $2;}
                | typeSpec error {$$ = NULL;}
                ;

paramIdList     : paramIdList COMMA paramId {
                                              $$ = addSibling($1,$3); yyerrok;}
                | paramId {$$ = $1;}
                | paramIdList COMMA error {$$ = NULL;}
                | error {$$ = NULL;}
                ;

paramId         : ID                        {$$ = newDeclNode(ParamK,UndefinedType,$1);
                                            $$->attr.name = $1->tokenStr;
                                            $$->attrSet = true;
                                            $$->isArray = false;
                                            }
                | ID OPEN_BRACK CLOSE_BRACK {$$ = newDeclNode(ParamK,UndefinedType,$1);
                                            $$->attr.name = $1->tokenStr;
                                            $$->attrSet = true;
                                            $$->isArray = true;
                                            }
                ;

stmt            : matched   {$$ = $1;}
                | unmatched {$$ = $1;}
                ;

matched         : expStmt           {$$ = $1;}
                | compoundStmt      {$$ = $1;}
                | matchedSelectStmt {$$ = $1;}
                | matchedIterStmt   {$$ = $1;}
                | returnStmt        {$$ = $1;}
                | breakStmt         {$$ = $1;}
                ;

unmatched       : unmatchedSelectStmt   {$$ = $1;}
                | unmatchedIterStmt     {$$ = $1;}
                ;


expStmt         : exp SEMI {$$ = $1;}
                | SEMI {$$ = NULL;}
                | error SEMI {$$ = NULL; yyerrok;}
                ;

compoundStmt    : OPEN_BRACE localDecls stmtList CLOSE_BRACE    { $$ = newStmtNode(CompoundK,$1,$2,$3);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                  yyerrok;
                                                                }

                ;

localDecls      : localDecls scopedVarDecl {
                                            $$ = addSibling($1,$2);}
                | {$$ = NULL;}
                ;

stmtList        : stmtList stmt         {
                                        if($2 != NULL)$$ = addSibling($1,$2);else $$=$1;}
                | {$$ = NULL;}
                ;

matchedSelectStmt   : IF simpleExp THEN matched ELSE matched    { $$ = newStmtNode(IfK,$1,$2,$4,$6);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                    | IF error {$$ = NULL;}
                    | IF error ELSE matched {$$ = NULL; yyerrok;}
                    | IF error THEN matched ELSE matched {$$ = NULL; yyerrok;}
                    ;

unmatchedSelectStmt : IF simpleExp THEN matched ELSE unmatched  { $$ = newStmtNode(IfK,$1,$2,$4,$6);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                    | IF simpleExp THEN stmt                    { $$ = newStmtNode(IfK,$1,$2,$4);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                    | IF error THEN stmt {$$ = NULL; yyerrok;}
                    | IF error THEN matched ELSE unmatched {$$ = NULL; yyerrok;}
                    ;

unmatchedIterStmt   : WHILE simpleExp DO unmatched              { $$ = newStmtNode(WhileK,$1,$2,$4);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                    | FOR ID ASS iterRange DO unmatched         {
                                                                  treeNode *node = newDeclNode(VarK,Integer,$2);
                                                                  node->attr.string = $2->tokenStr;
                                                                  node->attrSet = true;

                                                                  $$ = newStmtNode(ForK,$1,node,$4,$6);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                    ;

matchedIterStmt     : WHILE simpleExp DO matched                { $$ = newStmtNode(WhileK,$1,$2,$4);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }

                    | FOR ID ASS iterRange DO matched           {
                                                                  treeNode *node = newDeclNode(VarK,Integer,$2);
                                                                  node->attr.string = $2->tokenStr;
                                                                  node->attrSet = true;

                                                                  $$ = newStmtNode(ForK,$1,node,$4,$6);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                    | WHILE error DO matched {$$ = NULL; yyerrok;}
                    | WHILE error {$$ = NULL;}
                    | FOR ID ASS error DO matched {$$ = NULL; yyerrok;}
                    | FOR error {$$ = NULL;}
                    ;

iterRange       : simpleExp TO simpleExp                        { $$ = newStmtNode(RangeK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                }

                | simpleExp TO simpleExp BY simpleExp           { $$ = newStmtNode(RangeK,$4,$1,$3,$5);
                                                                  $$->attr.string = $4->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                | simpleExp TO error {$$ = NULL;}
                | error BY error {$$ = NULL; yyerrok;}
                | simpleExp TO simpleExp BY error {$$ = NULL;}
                ;

returnStmt      : RETURN SEMI                                   { $$ = newStmtNode(ReturnK,$1);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                | RETURN exp SEMI                               { $$ = newStmtNode(ReturnK,$1,$2);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                  yyerrok;
                                                                }
                | RETURN error SEMI {$$ = NULL; yyerrok;}
                ;

breakStmt       : BREAK SEMI                                    { $$ = newStmtNode(BreakK,$1);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                ;

exp             : mutable assignOp exp                          { $$ = newExpNode(AssignK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                }

                | mutable INC                                   { $$ = newExpNode(AssignK,$2,$1);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                | mutable DEC                                   { $$ = newExpNode(AssignK,$2,$1);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                | simpleExp  {$$ = $1;}
                | error assignOp exp {$$ = NULL; yyerrok;}
                | mutable assignOp error {$$ = NULL;}
                | error INC {$$ = NULL; yyerrok;}
                | error DEC {$$ = NULL; yyerrok;}
                ;

assignOp        : ASS                      {$$ = $1;}
                | ADDASS                   {$$ = $1;}
                | SUBASS                   {$$ = $1;}
                | MULASS                   {$$ = $1;}
                | DIVASS                   {$$ = $1;}


simpleExp       : simpleExp OR andExp                           { $$ = newExpNode(OpK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                | andExp   {$$ = $1;}
                | simpleExp OR error {$$ = NULL;}
                ;

andExp          : andExp AND unaryRelExp                        { $$ = newExpNode(OpK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                | unaryRelExp   {$$ = $1;}
                | andExp AND error {$$ = NULL;}
                ;

unaryRelExp     : NOT unaryRelExp                               { $$ = newExpNode(OpK,$1,$2);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                | relExp {$$ = $1;}
                | NOT error {$$ = NULL;}
                ;

relExp          : minMaxExp relOp minMaxExp                     { $$ = newExpNode(OpK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                | minMaxExp {$$ = $1;}
                | minMaxExp relOp error {$$ = NULL;}
                ;

relOp           : LEQ                   {$$ = $1;}
                | LESS                  {$$ = $1;}
                | GREATER               {$$ = $1;}
                | GEQ                   {$$ = $1;}
                | EQ                    {$$ = $1;}
                | NEQ                   {$$ = $1;}
                ;

minMaxExp       : minMaxExp minMaxOp sumExp                      {$$ = newExpNode(OpK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                 }
                | sumExp {$$ = $1;}
                ;

minMaxOp        : MAX  {$$ = $1;}
                | MIN  {$$ = $1;}
                ;

sumExp          : sumExp sumOp mulExp                            {$$ = newExpNode(OpK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                 }
                | mulExp   {$$ = $1;}
                | sumExp sumOp error {$$ = NULL;}
                ;

sumOp           : PLUS {$$ = $1;}
                | MINUS {$$ = $1;}
                ;

mulExp          : mulExp mulOp unaryExp                         { $$ = newExpNode(OpK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                | unaryExp {$$ = $1;}
                | mulExp mulOp error {$$ = NULL;}
                ;

mulOp           : MULT {$$ = $1;}
                | DIV {$$ = $1;}
                | MOD {$$ = $1;}
                ;

unaryExp        : unaryOp unaryExp                              { $$ = newExpNode(OpK,$1,$2);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                | factor {$$ = $1;}
                | unaryOp error {$$ = NULL;}
                ;

unaryOp         : MINUS {$$ = $1; $$->tokenClass = CHSIGN;}
                | MULT  {$$ = $1; $$->tokenClass = SIZEOF;}
                | QUESTION {$$ = $1;}
                ;

factor          : immutable {$$ = $1; }
                | mutable   {$$ = $1;}
                ;

mutable         : ID                                            { $$ = newExpNode(IdK,$1);
                                                                  $$->attr.name = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                  $$->isArray = false;
                                                                }
                | ID OPEN_BRACK exp CLOSE_BRACK                 {
                                                                  TreeNode * node = newExpNode(IdK,$1);
                                                                  node->attr.name = $1->tokenStr;
                                                                  node->attrSet = true;
                                                                  node->isArray = true;
                                                                  $$ = newExpNode(OpK,$2,node,$3);
                                                                  $$->attr.name = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                  $$->isArray = true;
                                                                }
                ;

immutable       : OPEN_PAREN exp CLOSE_PAREN  { $$ = $2; yyerrok;}
                | call  {$$ = $1;}
                | constant {$$ = $1;}
                | OPEN_PAREN error {$$ = NULL;}
                ;

call            : ID OPEN_PAREN args CLOSE_PAREN    { $$ = newExpNode(CallK,$1,$3);
                                                      $$->attr.name = $1->tokenStr;
                                                      $$->attrSet = true;

                                                    }
                | error OPEN_PAREN {$$ = NULL; yyerrok;}

                ;

args            : argList   {$$ = $1;}
                | {$$ = NULL;}
                ;

argList         : argList COMMA exp     {
                                        $$ = addSibling($1,$3); yyerrok;}
                | exp                   {$$ = $1;}
                | argList COMMA error {$$ = NULL; yyerrok;}

                ;

constant        : NUMCONST      { $$ = newExpNode(ConstantK,$1);
                                  $$->attr.value = $1->nValue;
                                  $$->attrSet = true;
                                  $$->expType = Integer;
                                  $$->unionType = value;
                                }
                | CHARCONST     { $$ = newExpNode(ConstantK,$1);
                                  $$->attr.cvalue = $1->cValue;
                                  $$->attrSet = true;
                                  $$->expType = Char;
                                  $$->unionType = cvalue;
                                }
                | STRINGCONST   { $$ = newExpNode(ConstantK,$1);
                                  $$->attr.string = $1->sValue;
                                  $$->attrSet = true;
                                  $$->expType = Char;
                                  $$->isArray = true;
                                  $$->unionType = string;
                                }
                | TRUE          { $$ = newExpNode(ConstantK,$1);
                                  $$->attr.value = $1->nValue;
                                  $$->attrSet = true;
                                  $$->expType = Boolean;
                                  $$->unionType = value;
                                }
                | FALSE         { $$ = newExpNode(ConstantK,$1);
                                  $$->attr.value = $1->nValue;
                                  $$->attrSet = true;
                                  $$->expType = Boolean;
                                  $$->unionType = value;
                                }
                ;


%%
extern int yydebug;



int main(int argc, char *argv[])
{
    char c;
    bool printflag = false;
    bool errorflag = false;
    extern int optind;
    extern int NUM_WARNINGS;
    extern int NUM_ERRORS;

    initErrorProcessing();

    while(1)
    {
        while((c = ourGetopt(argc,argv,(char*)"Ppd")) != -1)
        {
            switch(c)
            {
                case 'd':
                    errorflag = true;
                    break;
                case 'p':
                    printflag = true;
                    break;
                case 'P':
                    printflag = true;
                    break;
                default:
                    fprintf(stderr,"Usage: -p(print tree) -d(yydebug enable) are the only supported options\n./c- -[p|d] -[d|p] [FILENAME]\n");
                    exit(-1);
            }
        }

        if(optind < argc)
        {
            if ((yyin = fopen(argv[optind], "r"))) {}
            else
            {
                printf("ERROR(ARGLIST): source file \"%s\" could not be opened.\n", argv[optind]);
                NUM_ERRORS++;
                printf("Number of warnings: %d\n",NUM_WARNINGS);
                printf("Number of errors: %d\n",NUM_ERRORS);

                exit(1);
            }
            optind++;
        }
        else
        {
            break;
        }
    }
    if(errorflag)
        yydebug = 1;

    yyparse();
    SymbolTable *symTab;
    symTab = new SymbolTable();
    if(printflag && NUM_ERRORS == 0)
    {
      checkTree2(symTab,syntaxTree,false,NULL);
      treeNode *tmpLookupNode = (treeNode *) symTab->lookupGlobal(std::string("main"));

      if( (tmpLookupNode == NULL || tmpLookupNode->child[0] != NULL) || !tmpLookupNode->isFunc)
      {

        printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
        NUM_ERRORS++;
      }

        if(NUM_ERRORS == 0)
          printTypedTree(syntaxTree,0);

      printf("Number of warnings: %d\n",NUM_WARNINGS);
      printf("Number of errors: %d\n",NUM_ERRORS);

    }
    else
    {
        printf("Number of warnings: %d\n",NUM_WARNINGS);
        printf("Number of errors: %d\n",NUM_ERRORS);
    }

    return 0;
}

