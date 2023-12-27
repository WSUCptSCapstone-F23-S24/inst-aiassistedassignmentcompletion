
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emitcode.h"

extern FILE *code;


static int emitLoc = 0;   static int litLoc = 1;

void emitComment(char *c, char *cc)
{
    fprintf(code, "* %s %s\n", c, cc);
}

void emitComment(char *c, int n)
{
    fprintf(code, "* %s %d\n", c, n);
}

void emitComment(char *c)
{
    fprintf(code, "* %s\n", c);
}

void emitRO(char *op, long long int r, long long int s, long long int t, char *c, char *cc)
{
    fprintf(code, "%3d:  %5s  %lld,%lld,%lld\t%s %s\n", emitLoc, op, r, s, t, c, cc);
    fflush(code);
    emitLoc++;
}

void emitRO(char *op,long long int r,long long int s,long long int t, char *c)
{
    emitRO(op, r, s, t, c, (char *)"");
}

void emitRM(char *op, long long int r, long long int d, long long int s, char *c, char *cc)
{
    fprintf(code, "%3d:  %5s  %lld,%lld(%lld)\t%s %s\n", emitLoc, op, r, d, s, c, cc);
    fflush(code);
    emitLoc++;
}

void emitRM(char *op,long long int r,long long int d,long long int s, char *c)
{
    emitRM(op, r, d, s, c, (char *)"");
}

void emitGoto(int d,long long int s, char *c, char *cc)
{
    emitRM((char *)"JMP", (long long int)PC, d, s, c, cc);
}

void emitGoto(int d,long long int s, char *c)
{
    emitGoto(d,  s, c, (char *)"");
}

void emitRMAbs(char *op, long long int r, long long int a, char *c, char *cc)
{
    fprintf(code, "%3d:  %5s  %lld,%lld(%lld)\t%s %s\n", emitLoc, op, r, a - (long long int)(emitLoc + 1), (long long int)PC, c, cc);
    fflush(code);
    emitLoc++;
}

void emitRMAbs(char *op,long long int r,long long int a, char *c)
{
    emitRMAbs(op, r, a, c, (char *)"");
}

void emitGotoAbs(int a, char *c, char *cc)
{
    emitRMAbs((char *)"JMP", (long long int)PC, a, c, cc);
}

void emitGotoAbs(int a, char *c)
{
    emitGotoAbs(a, c, (char *)"");
}

// 9995  r
// 9994  s
// 9993  e
// 9992  blah
// 9991  blah
// 9990  blah
int emitStrLit(int goffset, char *s)
{
    fprintf(code, "%3d:  %5s  \"%s\"\n", -goffset, (char *)"LIT", s);
    return goffset;
}


//
//  Backpatching Functions
//

// asks where the next instruction will go.   Same as emitSkip(0).
int emitWhereAmI()
{
    return emitLoc;
}

// emitSkip skips "howMany" code
// locations for later backpatch.
// It also returns the current code position.
// emitSkip(0) tells you where you are and reserves no space.
//

int emitSkip(int howMany)
{
    int i = emitLoc;
    emitLoc += howMany;

    return i;
}

// emitNewLoc sets the emitLoc to a new location
// often loc = a previously skipped location
//
void emitNewLoc(int loc)
{
    emitLoc = loc;
}

// this back patches a LDA at the instruction address addr that
// jumps to the current instruction location now that it is known.
// This is essentially a backpatched "goto"
void backPatchAJumpToHere(int addr, char *comment)
{
    int currloc;

    currloc = emitWhereAmI();       // remember where we are
    emitNewLoc(addr);               // go to addr
    emitGotoAbs(currloc, comment);  // the LDA to here
    emitNewLoc(currloc);            // restore addr
}

// this back patches a JZR or JNZ at the instruction address addr that
// jumps to the current instruction location now that it is known.
void backPatchAJumpToHere(char *cmd, int reg, int addr, char *comment)
{
    int currloc;

    currloc = emitWhereAmI();       // remember where we are
    emitNewLoc(addr);               // go to addr
    emitRMAbs(cmd, reg, currloc, comment);  // cmd = JZR, JNZ
    emitNewLoc(currloc);            // restore addr
}