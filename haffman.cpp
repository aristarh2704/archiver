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
#include "haffman.h"

struct node {
    int64_t iCount;
    int next;
};

haffman::haffman(context *oContext, rwFile *oRw) {
    iContext=oContext;
    iRw=oRw;
}
void haffman::code() {
    unsigned pointerToA,pointerToB,pointerToC;
    uint64_t a,b,c;
    int symbol=iRw->readByte()+1;
    int aNode,bNode,cNode;
    unsigned current=1;
    unsigned *iTable=iContext->table;
    iContext->createTable();
    iContext->add();
    node table[257];
    for(int i=0; i<256; i++) {
        table[i+1].iCount=iTable[i];
        table[i].next=i+1;
    }
    table[256].next=0;
    while(table[current].next!=0) {
        // Сканирование минимумов
        pointerToA=0;
        aNode=table[0].next;
        a=table[aNode].iCount;
        pointerToB=aNode;
        bNode=table[pointerToB].next;
        b=table[bNode].iCount;
        pointerToC=bNode;
        cNode=table[pointerToC].next;
        while(cNode) {
            c=table[cNode].iCount;
            if(a>c && a>b) {
                pointerToA=pointerToB;
                aNode=bNode;
                a=b;
                pointerToB=pointerToC;
                bNode=cNode;
                b=c;
            } else {
                if(b>c) {
                    pointerToB=pointerToC;
                    bNode=cNode;
                    b=c;
                }
            }
            pointerToC=cNode;
            cNode=table[pointerToC].next;
        }
        if(symbol==aNode) {
            iRw->writeBit(0);
        } else if(symbol==bNode) {
            symbol=aNode;
            iRw->writeBit(1);
        }
        table[aNode].iCount=a+b;
        table[pointerToC].next=aNode;
        table[pointerToB].next=table[bNode].next;
        table[pointerToA].next=table[aNode].next;
        table[aNode].next=0;
        current=table[0].next;
    }
    iRw->endBits();
}
struct dNode {
    int64_t iCount;
    int next;
    int children[2];
};
void haffman::decode() {
    unsigned pointerToA,pointerToB,pointerToC;
    uint64_t a,b,c;
    int aNode,bNode,cNode;
    unsigned current=1;
    int iSize=257;
    dNode table[512];
    unsigned *iTable=iContext->table;
    iContext->createTable();
    for(int i=0; i<256; i++) {
        table[i+1].iCount=iTable[i];
        table[i].next=i+1;
    }
    table[256].next=0;
    while(table[current].next!=0) {
        // Сканирование минимумов
        pointerToA=0;
        aNode=table[0].next;
        a=table[aNode].iCount;
        pointerToB=aNode;
        bNode=table[pointerToB].next;
        b=table[bNode].iCount;
        pointerToC=bNode;
        cNode=table[pointerToC].next;
        while(cNode) {
            c=table[cNode].iCount;
            if(a>c && a>b) {
                pointerToA=pointerToB;
                aNode=bNode;
                a=b;
                pointerToB=pointerToC;
                bNode=cNode;
                b=c;
            } else {
                if(b>c) {
                    pointerToB=pointerToC;
                    bNode=cNode;
                    b=c;
                }
            }
            pointerToC=cNode;
            cNode=table[pointerToC].next;
        }
        table[iSize].iCount=a+b;
        table[pointerToC].next=iSize;
        table[pointerToB].next=table[bNode].next;
        table[pointerToA].next=table[aNode].next;
        table[iSize].next=0;
        table[iSize].children[0]=aNode;
        table[iSize].children[1]=bNode;
        current=table[0].next;
        iSize++;
    }
    current=iSize-1;
    while(current>256) {
        uchar temp=iRw->readBit();
        current=table[current].children[temp];
    }
    iRw->writeByte(current-1);
    iContext->add();
}

