#ifndef HAFFMAN_H_INCLUDED
#define HAFFMAN_H_INCLUDED

#include "context.h"
#include "rw.h"

class haffman{
    context *iContext;
    rwFile *iRw;
public:
    haffman(context*,rwFile*);
    void code();
    void decode();
};

#endif // HAFFMAN_H_INCLUDED
