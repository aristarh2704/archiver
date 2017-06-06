#ifndef RW_H_INCLUDED
#define RW_H_INCLUDED

#include "main.h"
#include "file.h"

#define I_READ 0
#define I_WRITE 1

class rwFile {
    uchar iBuffer; /* Входной буффер */
    uchar sIBuffer; /* Кол-во бит во входном буффере */
    uchar oBuffer[32]; /* Выходной буффер */
    short sOBuffer; /* Кол-во бит в выходном буффере */
    unsigned int posInText; /* Для хранения позиции в текстовом файле */
    unsigned int sizeTextFile; /* Размер текстового файла */
    void writeBuffer(uchar);
public:
    /** \brief
     *
     * \param FILE* binFile Бинарный файл
     * \param FILE* tFile Текстовый файл
     * \param unsigned sizeTFile Размер текстого файла
     * \param unsigned sizeBlock Размер одного блока
     * \param char stream Направление чтения: 0-из текстового в бинарный, 1-обратно
     *
     */
    rwFile(FILE* binFile,FILE* tFile,unsigned sizeTFile,unsigned sizeBlock,char stream);
    ~rwFile();
    uchar readBit();
    void writeBit(uchar);
    void endBits();
    uchar readByte();
    void writeByte(uchar);
    file *binarFile,*textFile;
};

#endif // RW_H_INCLUDED
