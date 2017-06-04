#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED

#include "main.h"

class fifo{
    uchar *buffer;
    unsigned int size;
    unsigned int offset;
public:
    fifo(unsigned int);
    void add(uchar);
    ~fifo();
    uchar& operator[](unsigned int);
};

#endif // FIFO_H_INCLUDED
