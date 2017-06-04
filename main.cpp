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
#include <stdio.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include "context.h"
#include "haffman.h"
#include "rw.h"

#define BLOCK 0xFFFFFF
#define WINDOW 0xFFF
#define DEEP 0

void usage() {
    printf("Usage:  ./compressor c|d input_file output_file\n\
           c - compress mode\n\
           d - decompress mode\n");
    getchar();
}

int main(int argc,char *argv[]) {
    if(argc!=4) {
        usage();
        _exit(1);
    }
    char mode=0;
    if(argv[1][1]!=0) {
        printf("Unknown mode %s\n",argv[1]);
        _exit(1);
    }
    if(*argv[1]=='c') {

    } else if(*argv[1]=='d') {
        mode=1;
    } else {
        printf("Unknown mode %s\n",argv[1]);
        _exit(1);
    }

    FILE *a=fopen(argv[2],"rb");
    if(a==0) {
        printf("Error opening file %s\n",argv[2]);
        _exit(1);
    }
    FILE *b=fopen(argv[3],"wb");
    unsigned sizeTFile;
    rwFile *myRw;
    if(mode){
        fread(&sizeTFile,4,1,a);
        myRw=new rwFile(a,b,sizeTFile,BLOCK,1);
    }else{
        struct stat myStat;
        stat(argv[2],&myStat);
        sizeTFile=myStat.st_size;
        fwrite(&sizeTFile,4,1,b);
        myRw=new rwFile(b,a,sizeTFile,BLOCK,0);
    }

    context myContext(DEEP,BLOCK,WINDOW,myRw->textFile->block);
    haffman myHaffman(&myContext,myRw);
    while(sizeTFile!=0){
        if(mode){
            myHaffman.decode();
        }else{
            myHaffman.code();
        }
        sizeTFile--;
        if(sizeTFile%1000==0){
            printf("%d\n",sizeTFile);
        }
    }
    delete myRw;
    fclose(a);
    fclose(b);
}
