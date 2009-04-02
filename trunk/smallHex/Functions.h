#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "lib\DWTools.h"
#include "lib\DWToolsDef.h"

#define Key(i) GetAsyncKeyState(i)==-32767

int FileSize(FILE *file){
    fseek(file,0,SEEK_END);
    return ftell(file);
}
