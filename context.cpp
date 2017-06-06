/*
    This file is part of archiver project
    Copyright © 2017  Feshchukov Aristarh <fe.arik@yandex.ru>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "context.h"
#include <string.h>
#include "buffer.h"

context::context(unsigned int ord,unsigned iWindow,buffer *iBuffer) {
    size=0;
    indexes=new char[deep+1];
    block=iBuffer->sizeBlock;
    window=iWindow;
    deep=ord;
    pBlock=iBuffer->block;
    for(int i=0; i<256; i++) {
        table[i]=0;
    }
}
context::~context() {
    delete[] indexes;
}
void context::add() {
    if(size>block)
        size=0;
    table[pBlock[size]]++;
    size++;
}
void context::createTable() {
    /*
    uchar *pWindow=&buffer[size-1];
    for(int i=0;i<deep;i++){
        indexes[i]=0;
    }
    for(int i=0;i<256;i++){
        table[i]=0; /* Сброс таблицы
    }
    for(int i=0;i<min(window,size);i++){
        table[pWindow[-i]]++;
        for(int k=deep-1;k>=0;k--){
            if(indexes[k]){
                if(pWindow[-i]==pWindow[-k-1]){
                    indexes[k+1]=1;
                    table[pWindow[-i+k+1]]++;
                }else{
                    indexes[k+1]=0;
                }
            }
        }
        if(pWindow[-i]==pWindow[0]){
            indexes[0]=1;
        }else{
            indexes[0]=0;
        }
    }
    */
}
