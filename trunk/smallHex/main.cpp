#include "Functions.h"
#define DEBUG


int main(){
    SetConsoleTitle("smallHex");
    SetCursorVisible(false);
    SetBufferSizeY(25);
    byte *buf=(byte*)malloc(2048);
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
    fread(buf,1,2048,file);

    for(int y=0;y<bufY;y++){
        SetXY(posXH,y);
        if (displaymode!=2){
            for(int x=0;x<bufX;x++){
                printf("%02X ",buf[x+bufX*y]);
            }
            printf(" ");
        }
        if (displaymode!=1)
            for(int x=0;x<bufX;x++){
                Alias(buf[x+bufX*y]);
            }
    }
    SetTextColor(LRED);
    if (displaymode==0||displaymode==1){
        SetXY(posXH,0); printf("%02X",buf[0]);
    }
    if (displaymode==0){
        SetXY(bufX*3+2,0);
        Alias(buf[0]);
    }
    else if (displaymode==2){
        SetXY(posXH,0);
        Alias(buf[0]);
    }
    SetTextColor(DWHITE);

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
