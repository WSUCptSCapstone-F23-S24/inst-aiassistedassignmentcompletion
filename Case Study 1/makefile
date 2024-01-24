BIN = parser
CC = g++
NAME = c-

SRCS = $(BIN).y  $(BIN).l
HDRS = scanType.h
OBJS = lex.yy.o $(BIN).tab.o

$(BIN) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

lex.yy.c : $(BIN).l $(BIN).tab.h $(HDR)
	flex $(BIN).l

$(BIN).tab.h $(BIN).tab.c : $(BIN).y
	bison -v -t -d $(BIN).y

clean :
	rm -f *~ $(OBJS) $(BIN) lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).output

tar : $(HDR) $(SRCS) makefile
	tar -cvf $(BIN).tar $(HDRS) $(SRCS) makefile

TEST_DIR = /home/evan/CS445-Homework/CS445-Homework/testDataA1
TEST_FILES = $(TEST_DIR)/textTest.c- $(TEST_DIR)/textTest2.c- $(TEST_DIR)/quote.c-


test: $(BIN) $(TEST_FILES)
	@for testfile in $(TEST_FILES); do \
		echo "Running test: $$testfile"; \
        ./c- < $$testfile; \
    done