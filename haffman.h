#ifndef HAFFMAN_H_INCLUDED
#define HAFFMAN_H_INCLUDED

#include "context.h"
#include "rw.h"

class haffman {
    context *iContext;
    rwFile *iRw;
    buffer *iTextBuffer;
public:
    haffman(context*,rwFile*,buffer*);
    void code();
    void decode();
};

#endif // HAFFMAN_H_INCLUDED
