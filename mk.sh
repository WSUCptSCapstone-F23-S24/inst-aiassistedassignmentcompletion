#!/bin/bash

# Clean previous build files
rm -f parser parser.l.c parser.y.c parser.y.h

# Compile Flex and Bison files
flex -o parser.y parser.l
bison -d -o parser.y parser.l

# Compile the C- scanner
gcc -o parser parser.y parser.l -ll -ly

# Check for compilation success
if [ $? -eq 0 ]; then
    echo "Compilation successful."

    # Run the program with an input file (e.g., filename.c-)
    ./parser filename.c-
else
    echo "Compilation failed."
fi