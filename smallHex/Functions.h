#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "lib\DWTools.h"
#include "lib\DWToolsDef.h"

#define Key(i) GetAsyncKeyState(i)==-32767

bool kh=0;
int32 p=0,size;
byte displaymode=0;
byte bufX=19,bufY=23,
     posXH=1;
FILE *file;

byte KeyX(){
    for(int i=8;i<0xA6;i++) if(Key(i)) return i;
}

void Console(int t){
    SetXY(2,24);
    printf("Console: ");
    switch (t){
        case 0:
            printf("Welcome to smallHex ^^");
            break;
        case 1:
            printf("Reading to Offset: %08X/%08X",p,size);
            kh=0;
            break;
        case 2:
            printf("Writing to Offset: %08X/%08X",p,size);
            break;
    }
}

void Alias(register char Char){
    switch(Char){
        case 0x00: // NULL
        case 0x07: // BEEP
        case 0x08: // BACKSPACE
        case 0x09: // TAB
        case 0x0A: // NEW LINE
        case 0x0D: // RETURN
            printf(" ");
            break;
        default:
            printf("%c",Char);
    }
}

void write(byte code){
    fseek(file,p,SEEK_SET);
    fprintf(file,"%c",code);
    Console(2);
}

int FileSize(FILE *file){
    fseek(file,0,SEEK_END);
    return ftell(file);
}

