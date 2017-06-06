#ifndef RW_H_INCLUDED
#define RW_H_INCLUDED

#include "main.h"
#include "buffer.h"

#define I_READ 0
#define I_WRITE 1

class rwFile {
    uchar iBuffer; /* Входной буффер */
    uchar sIBuffer; /* Кол-во бит во входном буффере */
    uchar oBuffer[32]; /* Выходной буффер */
    short sOBuffer; /* Кол-во бит в выходном буффере */
    void writeBuffer(uchar);
    buffer *binBuffer;
public:
    /** \brief
     *
     * \param buffer *binBuff Бинарный буфер
     * \param char stream Направление чтения: 0-из текстового в бинарный, 1-обратно
     *
     */
    rwFile(buffer *binBuff);
    ~rwFile();
    uchar readBit();
    void writeBit(uchar);
    void endBits();
};

#endif // RW_H_INCLUDED
