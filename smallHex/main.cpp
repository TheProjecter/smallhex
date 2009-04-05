#include "Functions.h"
#define DEBUG


int main(){
    SetConsoleTitle("smallHex");
    SetCursorVisible(false);
    SetBufferSizeY(25);
    byte *buf=(byte*)malloc(2048);
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

        byte i=KeyX();
        switch(i){
            case VK_LEFT:
                if (p>0){
                    p--;
                    goto WRITE;
                }
                break;
            case VK_RIGHT:
                p++;
                goto WRITE;
                break;
            case VK_UP:
                if (p>bufX) p-=bufX;
                else p=0;
                goto WRITE;
                break;
            case VK_DOWN:
                p+=bufX;
                goto WRITE;
                break;
            case PAGEUP:
                if (p>bufX*bufY) p-=bufX*bufY;
                else p=0;
                goto WRITE;
                break;
            case PAGEDWN:
                p+=bufX*bufY;
                goto WRITE;
                break;
            case ESC:
                exit(0);
            case F5:
                switch(displaymode){
                    case 0:
                        displaymode=1;
                        bufX=26;
                        break;
                    case 1:
                        displaymode=2;
                        bufX=78;
                        break;
                    case 2:
                        displaymode=0;
                        bufX=19;
                        break;
                }
                goto BEGIN;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
                SetTextColor(LRED);
                if (!kh){
                    SetXY(1,0); printf("%c",i);
                    kh=1;
                    buf[0]=buf[0]-((buf[0]>>4)<<4)+(i<<4);
                    write(buf[0]);
                }
                else {
                    SetXY(2,0); printf("%c",i);
                    kh=0;
                    buf[0]=((buf[0]>>4)<<4)+i
                    write(buf[0]);
                }
                SetTextColor(DWHITE);
                break;
            case BACKSPC:
                if (kh) kh=0;
        }
    }
}
