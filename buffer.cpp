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
#include "main.h"
#include "buffer.h"

buffer::buffer(FILE *iFile,char iMode,unsigned size) {
    sizeBlock=size;
    mode=iMode;
    block=new uchar[size];
    rPos=0;
    wPos=0;
    bFile=iFile;
    if(!mode && bFile) {
        fseek(iFile,0,SEEK_SET);
        int temp=fread(block,1,size,iFile);
    }
}

buffer::~buffer() {
    if(mode && bFile) {
        fwrite(block,1,wPos,bFile);
    }
}

uchar buffer::get() {
    if(rPos==sizeBlock) {
        if(bFile)
            fread(block,1,sizeBlock,bFile);
        rPos=0;
    }
    rPos++;
    return block[rPos-1];

}

void buffer::put(uchar symbol) {
    if(wPos==sizeBlock) {
        if(bFile)
            fwrite(block,1,sizeBlock,bFile);
        wPos=0;
    }
    block[wPos]=symbol;
    wPos++;
}
