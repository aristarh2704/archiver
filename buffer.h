#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include "main.h"

/*
    Класс buffer служит для буферизованного чтения-записи в файл.
    Поддерживает одновременную запись и чтение.
    Может быть не привязанным к файлу, и быть просто блоком памяти.
*/

class buffer {
    unsigned rPos; /* Позиция для get() */
    unsigned wPos; /* Позиция для put() */
    char mode;
    FILE *bFile;
public:
    /** \brief
     *
     * \param FILE* Файл
     * \param char mode 0-чтение, 1-запись, 2-чтение и запись (пока не поддерживается).
     *
     */
    buffer(FILE*,char iMode,unsigned size);
    ~buffer();
    uchar *block; /* Для прямого доступа к буферу */
    unsigned sizeBlock;
    void put(uchar);
    uchar get();
};

#endif // FILE_H_INCLUDED
