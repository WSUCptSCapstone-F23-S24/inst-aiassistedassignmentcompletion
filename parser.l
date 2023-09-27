
int main(int argc, char* argv[]) {
    if (argc > 1) {
        FILE* input_file = fopen(argv[1], "r");
        if (input_file == NULL) {
            fprintf(stderr, "Error: Unable to open input file\n");
            return 1;
        }
        yyin = input_file;
    }

    // Initialize the Flex scanner
    yylex();

    return 0;
}