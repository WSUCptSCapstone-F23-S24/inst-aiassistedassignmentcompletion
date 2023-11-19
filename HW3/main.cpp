#include "main.h"

int main (int argc, char *argv[])
{
    errCount = wrnCount = 0;

    AST = new Node();
    AST->index = -1;

    // read in flags
    int dpt = 0, Dpt = 0, ppt = 0, Ppt = 0, hpt = 0;
    int flg;
    while ((flg = customGetopt(argc, argv, (char *)"dDpPh")) != EOF) {
        switch (flg) {
            case 'd': dpt = 1; break;
            case 'D': Dpt = 1; break;
            case 'p': ppt = 1; break;
            case 'P': Ppt = 1; break;
            case 'h': hpt = 1; break;
        }
    }

    // print the usage message if the h flag was raised
    if (hpt)
        printf("usage: -c [options] [sourcefile]\noptions:\n-d\t- turn on parser debugging\n-D\t- turn on symbol table debugging\n-h\t- print this usage messagea\n-p\t- print the abstract syntax tree\n-P\t- print the abstract syntax tree plus type information\n");

    // turn on parser debugging
    if (dpt)
        yydebug = 1;

    // do parsing
    if (optind < argc) {
        // a file was specified on the command line, so read it
        if ((yyin = fopen(argv[optind], "r"))) {
            yyparse();
            fclose(yyin);
        } else {
            printf("ERROR(ARGLIST): source file \"%s\" could not be opened.\n", argv[optind]);
            errCount++;
        }
    } else {
        // no command line file was specified, so read from the input stream instead
        yyparse();
    }

    // check that the AST was generated
    if (!AST) {
        // if AST wasn't generated, print error mesasage and exit
        printf("ERROR: No abstract syntax tree was generated.\n");
        return -1;
    }

    // create the symbol table
    SymbolTable * syms = new SymbolTable();

    // set the symbol table's debug flag 
    syms->debug(Dpt);

    if (errCount == 0) {
        AST->updateLoc();
        if (ppt) AST->print(false);
        AST->sem(syms);
        if (Ppt && errCount == 0) AST->print(true);
    }

    printf("Number of warnings: %d\nNumber of errors: %d\n", wrnCount, errCount);

    return 0;
}

