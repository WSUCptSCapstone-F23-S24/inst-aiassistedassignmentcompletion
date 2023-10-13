CC = gcc
LEX = flex
YACC = bison

CFLAGS = -Wall -g -w

LEX_SOURCE = parser.l
YACC_SOURCE = parser.y
YACC_HEADER = parser.tab.h
YACC_C = parser.tab.c

SOURCES = header.h $(LEX_SOURCE) $(YACC_SOURCE)
OBJECTS = $(YACC_C:.c=.o) $(LEX_C:.c=.o) 

EXECUTABLE = parser

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(YACC_C): $(YACC_SOURCE)
	$(YACC) -d -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECUTABLE) $(YACC_C) $(YACC_HEADER) $(OBJECTS)