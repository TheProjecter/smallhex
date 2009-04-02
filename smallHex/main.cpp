#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "lib\DWTools.h"
#include "lib\DWToolsDef.h"
#include "Functions.h"

#define DEBUG 1

FILE *file;
char *path;

int main(){
    SetConsoleTitle("smallHex");
    #ifdef DEBUG
        file=fopen("test.bin","r+b");
    #else
        printf("File to open: ");
        scanf("%s",path);
        file=fopen(path,"r+b");
    #endif
    while(1){
        printf("OK! ;)");
        Pause();
        break;
    }
}
