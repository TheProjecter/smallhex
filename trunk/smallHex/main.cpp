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
    if (displaymode!=2)
        for(int y=0;y<bufY;y++){  // HEX CODE
            SetXY(1,y);
            for(int x=0;x<bufX;x++){
                printf("%02X ",buf[x+bufX*y]);
            }
        }
    if (displaymode!=1)
        for(int y=0;y<bufY;y++){  // HEX CODE
            SetXY(59,y);
            for(int x=0;x<bufX;x++){
                printf("%c",buf[x+bufX*y]);
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
            if (p>bufX) p-=bufX;
            else p=0;
            goto WRITE;
        }
        else if (Key(VK_DOWN)){
            p+=bufX;
            goto WRITE;
        }
        else if (Key(ESC))
            exit(0);
        else if (Key(F5)){
            switch(displaymode){
                case 0:
                    displaymode=1;
                    bufX=26;
                    break;
                case 1:
                    displaymode=2;
                    break;
                case 2:
                    displaymode=0;
                    bufX=16;
                    break;
            }
            goto BEGIN;
        }
    }
}
