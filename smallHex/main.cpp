#include "Functions.h"

int main(){
    SetConsoleTitle("smallHex");
    SetCursorVisible(false);
    SetBufferSizeY(25);
    DWORD dwThreadId, dwThrdParam = 1;
    HANDLE thFocus = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)FocusThread,&dwThrdParam,0,&dwThreadId);
    byte *buf=(byte*)malloc(2048);
    char *scrbuf=(char*)malloc(2048);
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
    register byte ky=0;
BEGIN:
    cls();
    DrawLineX(1,GetBufferSizeY()-2,GetBufferSizeX()-2);
    Console(0);
READ:
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
                switch (buf[x+bufX*y]){
                    case 0x00: // NULL
                    case 0x07: // BEEP
                    case 0x08: // BACKSPACE
                    case 0x09: // TAB
                    case 0x0A: // NEW LINE
                    case 0x0D: // RETURN
NULLCHAR:
                        scrbuf[x]=0x20;
                        break;
                    default:
                        if (((x+bufX*y)+p)>size) goto NULLCHAR;
                        scrbuf[x]=buf[x+bufX*y];
                }
            }
            printf("%s",scrbuf);
    }
    if (0){
WRITE:
        if (!md){
            if (!kh)
                buf[0]=buf[0]-((buf[0]>>4)<<4)+(ky<<4);
            else
                buf[0]=((buf[0]>>4)<<4)+ky;
            kh=!kh;
        }
        else {
            buf[0]=ky;
        }
        write(buf[0]);
        if (md){
            p++;
            goto READ;
        }

    }
UPDATE:
    if (displaymode==0||displaymode==1){
        if (!md) SetTextColor(LRED);
        SetXY(posXH,0); printf("%02X",buf[0]);
    }
    if (displaymode==0){
        SetXY(bufX*3+2,0);
        if (!md) SetTextColor(DWHITE);
        else SetTextColor(LRED);
        Alias(buf[0]);
    }
    else if (displaymode==2){
        SetXY(posXH,0);
        Alias(buf[0]);
    }
    SetTextColor(DWHITE);
    ky=0;
    while(1){
NOFOCUS:
        Sleep(1);
        if (!focus) goto NOFOCUS;

        for(register int i=8;i<0xA6;i++)
            if(Key(i)) ky=i;

        switch(ky){
            case VK_LEFT:
                if (p>0){
                    p--;
                    goto READ;
                }
                break;
            case VK_RIGHT:
                if (p<size) p++;
                goto READ;
                break;
            case VK_UP:
                if (p>bufX) p-=bufX;
                else p=0;
                goto READ;
                break;
            case VK_DOWN:
                p+=bufX;
                goto READ;
                break;
            case PAGEUP:
                if (p>bufX*bufY) p-=bufX*bufY;
                else p=0;
                goto READ;
                break;
            case PAGEDWN:
                p+=bufX*bufY;
                goto READ;
                break;
            case ESC:
                exit(0);
            case '0':
                if (!md) ky=0x0;
                goto WRITE;
            case '1':
                if (!md) ky=0x1;
                goto WRITE;
            case '2':
                if (!md) ky=0x2;
                goto WRITE;
            case '3':
                if (!md) ky=0x3;
                goto WRITE;
            case '4':
                if (!md) ky=0x4;
                goto WRITE;
            case '5':
                if (!md) ky=0x5;
                goto WRITE;
            case '6':
                if (!md) ky=0x6;
                goto WRITE;
            case '7':
                if (!md) ky=0x7;
                goto WRITE;
            case '8':
                if (!md) ky=0x8;
                goto WRITE;
            case '9':
                if (!md) ky=0x9;
                goto WRITE;
            case 'A':
                if (!md) ky=0xA;
                goto WRITE;
            case 'B':
                if (!md) ky=0xB;
                goto WRITE;
            case 'C':
                if (!md) ky=0xC;
                goto WRITE;
            case 'D':
                if (!md) ky=0xD;
                goto WRITE;
            case 'E':
                if (!md) ky=0xE;
                goto WRITE;
            case 'F':
                if (!md) ky=0xF;
                goto WRITE;
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                if (md) goto WRITE;
            case BACKSPC:
                kh=!kh;
                break;
            case F5:
                switch(displaymode){
                    case 0:
                        displaymode=1;
                        bufX=26;
                        md=0;
                        break;
                    case 1:
                        displaymode=2;
                        bufX=78;
                        md=1;
                        break;
                    case 2:
                        displaymode=0;
                        bufX=19;
                        md=0;
                        break;
                }
                goto BEGIN;
                break;
            case TAB:
                md=!md;
                Console(3);
                goto UPDATE;
                break;
        }
    }
}
