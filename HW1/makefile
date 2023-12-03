c-: parser.l parser.y scanType.h
    flex parser.l
    bison -d parser.y
    gcc -o c- lex.yy.c parser.tab.c -lfl -lm

clean:
    rm -f lex.yy.c parser.tab.c parser.tab.h c-
