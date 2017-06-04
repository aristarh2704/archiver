#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <limits.h>

typedef unsigned char uchar;
#define min(a,b) (a<b?a:b)
#define inAbs(a) (a>0?a:-a)

#ifndef _INT64_T_DECLARED
typedef signed long int64_t;
#define _INT64_T_DECLARED
#endif // _INT64_T_DECLARED

#ifndef _UINT64_T_DECLARED
typedef unsigned long uint64_t;
#define _UINT64_T_DECLARED
#endif // _UINT64_T_DECLARED

#endif // MAIN_H_INCLUDED
