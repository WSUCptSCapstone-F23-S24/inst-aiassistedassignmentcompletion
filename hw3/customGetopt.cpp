#include	<string.h>
#include	<stdio.h>

#if	M_I8086 || M_I286 || MSDOS
#define 	SWITCH	'/'
#else
#define 	SWITCH	'-'
#endif

char *argVal;         // stores option argument if ':' is present in opts
int argIdx = 1;       // index for the next argv element
int dispErr = 1;     // set to 1 to display error messages, 0 otherwise
int lastOpt;         // stores the last parsed option (exported for dubious cases)

// ------------ Private Section ---------------------------------------

static int off = 1;  // offset within the option word

static int invOpt(char *progName, char *errMsg)
{
    if (dispErr)      // display error message if dispErr is not 0
        fprintf(stderr, "%s: %s -- %c\n", progName, errMsg, lastOpt);

    return (int) '?';    // return '?' for an invalid option
}

// ------------ Exported Function ---------------------------------------

int customGetopt(int argc, char **argv, char *opts)
{
    char *pos, ch;

    if (off == 1) {
        if (argc <= argIdx || argv[argIdx][1] == '\0')
            return EOF;    // no more words or single '-'

        if ((ch = argv[argIdx][0]) != '-' && ch != SWITCH)
            return EOF;    // options must start with '-'

        if (!strcmp(argv[argIdx], "--")) {
            ++argIdx;    // move to the next word
            return EOF;    // '--' marks the end
        }
    }

    lastOpt = (int) (ch = argv[argIdx][off]);    // flag the option

    if (ch == ':' || (pos = strchr(opts, ch)) == NULL) {
        if (argv[argIdx][++off] == '\0') {
            ++argIdx;
            off = 1;    // move to the next word
        }
		// mark as an invalid operation
        return invOpt(argv[0], (char *)"illegal option");
    }

    if (*++pos == ':') {    // ':' option requires an argument
        argVal = &argv[argIdx][off + 1];    // if the argument is in the same word
        ++argIdx;
        off = 1;    // move to the next word

        if (*argVal == '\0') {    // check if the argument is in the next word
            if (argc <= argIdx)    // no more words
                return invOpt(argv[0], (char *)"option requires an argument");

            argVal = argv[argIdx++];    // move to the next word
        }
    }
    else {    // flag option without an argument
        argVal = NULL;

        if (argv[argIdx][++off] == '\0') {
            argIdx++;
            off = 1;    // move to the next word
        }
    }

    return lastOpt;
}