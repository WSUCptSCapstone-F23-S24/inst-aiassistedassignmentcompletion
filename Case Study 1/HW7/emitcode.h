#ifndef EMIT_CODE_H__
#define EMIT_CODE_H__

#define GP   0	//  The global pointer
#define FP   1	//  The local frame pointer
#define RT   2	//  Return value
#define AC   3  //  Accumulator
#define AC1  4  //  Accumulator
#define AC2  5  //  Accumulator
#define AC3  6  //  Accumulator
#define PC   7	//  The program counter

#define NO_COMMENT (char *)""

int emitWhereAmI();           int emitSkip(int howMany);    void emitNewLoc(int loc);
void emitComment(char *c);
void emitComment(char *c, char *cc);
void emitComment(char *c, int n);

void emitGoto(int d, long long int s, char *c);
void emitGoto(int d, long long int s, char *c, char *cc);
void emitGotoAbs(int a, char *c);
void emitGotoAbs(int a, char *c, char *cc);

void emitRM(char *op, long long int r, long long int d, long long int s, char *c);
void emitRM(char *op, long long int r, long long int d, long long int s, char *c, char *cc);
void emitRMAbs(char *op, long long int r, long long int a, char *c);
void emitRMAbs(char *op, long long int r, long long int a, char *c, char *cc);

void emitRO(char *op, long long int r, long long int s, long long int t, char *c);
void emitRO(char *op, long long int r, long long int s, long long int t, char *c, char *cc);

void backPatchAJumpToHere(int addr, char *comment);
void backPatchAJumpToHere(char *cmd, int reg, int addr, char *comment);

int emitStrLit(int goffset, char *s);
#endif