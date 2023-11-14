#ifndef _OURGETOPT_H_
#define _OURGETOPT_H_
// do not include in outGetopt.cpp
int ourGetopt( int, char **, char*);
extern char *optarg;                   /* option argument if : in opts */
extern int optopt;                     /* last option (export dubious) */
#endif
