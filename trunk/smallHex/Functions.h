#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "lib\DWTools.h"
#include "lib\DWToolsDef.h"

#define Key(i) GetAsyncKeyState(i)==-32767

int32 p=0,size;

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
