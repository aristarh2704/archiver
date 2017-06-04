#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include "main.h"
#include "fifo.h"

class context{
    char *indexes;
    uchar *buffer;
    unsigned deep; /* Глубина контекста */
    unsigned block; /* Размер блока */
    unsigned window; /* Размер окна */
public:
    context(unsigned  /* Глубина */,unsigned /* Размер блока */,unsigned /*Размер окна */,uchar* /* Указатель на буфер */);
    ~context();
    void add();
    void createTable();
    unsigned size; /* Количество символов в блоке */
    unsigned table[256]; /* Таблица вероятности символов */
    unsigned step;
};

#endif // CONTEXT_H_INCLUDED
