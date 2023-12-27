#ifndef EMIT_CODE_H__
#define EMIT_CODE_H__

#define GP   0	#define FP   1	#define RT   2	#define AC   3  #define AC1  4  #define AC2  5  #define AC3  6  #define PC   7
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