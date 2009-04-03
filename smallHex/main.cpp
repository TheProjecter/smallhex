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
    if (displaymode!=2){
        for(int y=0;y<bufY;y++){  // HEX
            SetXY(posXH,y);
            for(int x=0;x<bufX;x++){
                printf("%02X ",buf[x+bufX*y]);
            }
        }
        SetXY(posXH,0); SetTextColor(LRED);
        printf("%02X",buf[0]);
        SetTextColor(DWHITE);
    }
    if (displaymode!=1){
        for(int y=0;y<bufY;y++){  // CHAR
            SetXY(posXC,y);
            for(int x=0;x<bufX;x++){
                Alias(buf[x+bufX*y]);
            }
        }
        SetXY(posXC,0); SetTextColor(LRED);
        Alias(buf[0]);
        SetTextColor(DWHITE);
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
        else if (Key(PAGEUP)){
            if (p>bufX*bufY) p-=bufX*bufY;
            else p=0;
            goto WRITE;
        }
        else if (Key(PAGEDWN)){
            p+=bufX*bufY;
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
                    bufX=78;
                    posXC=1;
                    break;
                case 2:
                    displaymode=0;
                    bufX=19;
                    posXC=59;
                    break;
            }
            goto BEGIN;
        }
    }
}
