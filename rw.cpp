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
#include "rw.h"
#include <stdio.h>

uchar rwFile::readBit() {
    if(sIBuffer==0) {
        iBuffer=binBuffer->get();
        sIBuffer=8;
    }
    uchar temp=iBuffer%2;
    iBuffer/=2;
    sIBuffer--;
    return temp;
}

rwFile::rwFile(buffer *iBuffer) {
    sIBuffer=0;
    sOBuffer=0;
    binBuffer= iBuffer;
}

void rwFile::writeBit(uchar bit) {
    uchar temp=oBuffer[sOBuffer/8];
    if(bit) {
        temp|=(1<<sOBuffer%8);
    } else {
        temp&=~(1<<sOBuffer%8);
    }
    oBuffer[sOBuffer/8]=temp;
    sOBuffer++;
}

void rwFile::endBits() {
    for(short i=sOBuffer-1; i>=0; i--) {
        uchar temp1=oBuffer[i/8];
        uchar temp2=temp1&(1<<(i%8));
        temp2=temp2>>(i%8);
        writeBuffer(temp2);
    }
    sOBuffer=0;
}

void rwFile::writeBuffer(uchar bit) {
    if(bit) {
        iBuffer|=(1<<sIBuffer);
    } else {
        iBuffer&=~(1<<sIBuffer);
    }
    sIBuffer++;
    if(sIBuffer==8) {
        sIBuffer=0;
        binBuffer->put(iBuffer);
    }
}

rwFile::~rwFile() {
    if(sIBuffer!=0) {
        binBuffer->put(iBuffer);
    }
}
