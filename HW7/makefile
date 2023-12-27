SRCS = parser.l parser.y ourgetopt.cpp node.cpp symbolTable.cpp semantic.cpp yyerror.cpp
HDRS = scanType.h ourgetopt.h node.h symbolTable.h semantic.h yyerror.h
OBJS = lex.yy.o parser.tab.o ourgetopt.o node.o symbolTable.o semantic.o yyerror.o
BIN  = c-
CC   = g++
CPPFLAGS = -std=c++11 -Wall -Wextra -pedantic -g
LEX = flex
BISONFLAGS = -v  -t -d
TARNAME = pas03.tar

$(BIN): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o $(BIN)

parser.tab.h parser.tab.c: parser.y
	bison $(BISONFLAGS) parser.y

lex.yy.c: parser.l parser.tab.h
	$(LEX) parser.l

all:
	touch $(SRCS)
	make

.PHONY : clean
clean:
	rm -f $(BIN) $(OBJS) lex.yy.c parser.tab.c parser.tab.h parser.output *~
	rm -rf $(TARNAME)
.PHONY : tar
tar:
	tar -cvf $(TARNAME) $(SRCS) $(HDRS) makefile
	ls -l $(TARNAME)