#include "Functions.h"
#define DEBUG


int main(){
    SetConsoleTitle("smallHex");
    SetCursorVisible(false);
    SetBufferSizeY(25);
    byte *buf=(byte*)malloc(4096);
    FILE *file;
    char *path;
    #ifdef DEBUG
        path="test.bin";
        file=fopen("test.bin","r+b");
    #else
        printf("File to open: ");
        scanf("%s",path);
    #endif
    file=fopen(path,"r+b");
    size=FileSize(file);
BEGIN:
    cls();
    DrawLineX(1,GetBufferSizeY()-2,GetBufferSizeX()-2);
    Console(0);
WRITE:
    Console(1);
    fseek(file,p,SEEK_SET);
    fread(buf,1,4096,file);
    for(int y=0;y<23;y++){
        SetXY(1,y);
        for(int x=0;x<26;x++){
            printf("%02X ",buf[x+26*y]);
        }
    }
    while(1){
        Sleep(1);

        if (Key(VK_LEFT)&&p>0){
            p--;
            goto WRITE;
        }
        else if (Key(VK_RIGHT)){
            p++;
            goto WRITE;
        }
        else if (Key(VK_UP)){
            if (p>26) p-=26;
            else p=0;
            goto WRITE;
        }
        else if (Key(VK_DOWN)){
            p+=26;
            goto WRITE;
        }
        else if (Key(ESC))
            exit(0);
    }
}
