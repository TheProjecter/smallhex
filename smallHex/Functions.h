#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "lib\DWTools.h"
#include "lib\DWToolsDef.h"

#define KeyA(i) GetAsyncKeyState(i)
#define Key(i) GetAsyncKeyState(i)==-32767

bool kh=0,md=0;
int32 p=0,size;
byte displaymode=0;
byte bufX=19,bufY=23,
     posXH=1;
FILE *file;

byte ky=0;
DWORD KeyThread(LPDWORD lpdwParam){
    while(1){
        Sleep(1);
        for(int i=8;i<0xA6;i++){
RE:
            if(Key(i)){
                ky=i;
                goto RE;
            }
        }
    }
}

void Console(int t){
    SetXY(2,24);
    printf("Console: ");
    switch (t){
        case 0:
INFO:
            SetXY(77,24); if (!md) printf("H"); else printf("C");
            break;
        case 1:
            printf("Reading to Offset: %08X/%08X",p,size);
            kh=0;
            break;
        case 2:
            printf("Writing to Offset: %08X/%08X",p,size);
            break;
        case 3:
            printf("Switched the input mode             ");
            goto INFO;
    }
}

char Alias(register char Char){
    switch(Char){
        case 0x00: // NULL
        case 0x07: // BEEP
        case 0x08: // BACKSPACE
        case 0x09: // TAB
        case 0x0A: // NEW LINE
        case 0x0D: // RETURN
            return 0x20;
        default:
            return Char;
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

