#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include "main.h"

class file {
    unsigned sizeBlock;
    unsigned count;
    char mode;
    FILE *bFile;
public:
    /** \brief
     *
     * \param FILE* Файл
     * \param char mode 0-чтение, 1-запись
     *
     */
    file(FILE*,char iMode,unsigned size);
    ~file();
    uchar *block;
    void put(uchar);
    uchar get();
};

#endif // FILE_H_INCLUDED
