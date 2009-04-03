#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "lib\DWTools.h"
#include "lib\DWToolsDef.h"

#define Key(i) GetAsyncKeyState(i)==-32767

int32 p=0,size;
byte displaymode=0;
byte bufX=19,bufY=23,
     posXH=1,posXC=59;

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
int FileSize(FILE *file){
    fseek(file,0,SEEK_END);
    return ftell(file);
}

void Console(int t){
    SetXY(2,24);
    printf("Console: ");
    switch (t){
        case 0:
            printf("Welcome to smallHex ^^");
            break;
        case 1:
            printf("Offset: %08X/%08X",p,size);
            break;
    }
}


