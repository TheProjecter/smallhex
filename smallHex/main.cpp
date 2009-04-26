// smallHex SVN => http://code.google.com/p/smallhex/
#include "Functions.h"

int main(){
    SetConsoleTitle("smallHex");
    SetCursorVisible(false);
    SetBufferSizeY(25);
    DWORD dwThreadId, dwThrdParam = 1;
    HANDLE thFocus = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)FocusThread,&dwThrdParam,0,&dwThreadId);
    byte *buf=(byte*)malloc(4096);
    char *scrbuf=(char*)malloc(2048);
    char hexbuf[2];
    char *path;
OPEN:
    #ifdef DEBUG
        path="test.bin";
    #else
        printf("File to open: ");
        scanf("%s",path);
    #endif
    file=fopen(path,"r+b");
    size=FileSize(file)-1;
    register byte ky=0;
SWITCH:
    cls();
    DrawLineX(1,GetBufferSizeY()-2,GetBufferSizeX()-2);
    ConsoleX(0xFF);
READ:
    ConsoleX(1);
    fseek(file,p,SEEK_SET);
    fread(buf,1,4096,file);
    SetXY(0,0);
    for(int y=0;y<bufY;y++){
        scrbuf[0]=0x20;
        if (displaymode!=2){
            for(int x=0;x<bufX;x++){
                if (((x+bufX*y)+p)>size){
                    scrbuf[x*3+1]=0x20;
                    scrbuf[x*3+2]=0x20;
                }
                else {
                    sprintf(hexbuf,"%02X",buf[x+bufX*y]);
                    scrbuf[x*3+1]=hexbuf[0];
                    scrbuf[x*3+2]=hexbuf[1];
                }
                scrbuf[x*3+3]=0x20;
                Debug("Buffer",x+bufX*y);
            }
        }
        scrbuf[bufX*3+1]=0x20;
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
                        if (displaymode==2) scrbuf[x+1]=0x20;
                        else scrbuf[x+(bufX*3)+2]=0x20;
                        break;
                    default:
                        if (((x+bufX*y)+p)>size) goto NULLCHAR;
                        else if (displaymode==2) scrbuf[x+1]=buf[x+bufX*y];
                        else scrbuf[x+(bufX*3)+2]=buf[x+bufX*y];
                }
            }
        scrbuf[GetBufferSizeX()-1-xd]='\n';
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
            if (up) buf[0]=ky;
            else buf[0]=ky+0x20;
        }
        write(buf[0]);
        if (md){
            p++;
            goto READ;
        }
    }
UPDATE:
    if (displaymode==0||displaymode==1){
        if (!md) SetTextColor(LRED);{
            SetXY(posXH,0); printf("%02X",buf[0]);
/*   //     NEW HEXEDIT SYSTEM, BUT I DON'T LIKE IT :S
            SetXY(posXH+kh,0);
            if (!kh) printf("%X",buf[0]>>4);
            else printf("%X",buf[0]-(buf[0]>>4<<4));
*/
        }
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
            case VK_UP:
                if (p>bufX) p-=bufX;
                else p=0;
                goto READ;
            case VK_DOWN:
                if (p+bufX<size) p+=bufX;
                else p=size;
                goto READ;
            case PAGEUP:
                if (p>bufX*bufY) p-=bufX*bufY;
                else p=0;
                goto READ;
            case PAGEDWN:
                if (p+bufX*bufY<size) p+=bufX*bufY;
                else p=size;
                goto READ;
            case ' ':
                if (md) goto WRITE;
            case '0':
            case '0'+0x30:
                if (!md) ky=0x0;
                goto WRITE;
            case '1':
            case '1'+0x30:
                if (!md) ky=0x1;
                goto WRITE;
            case '2':
            case '2'+0x30:
                if (!md) ky=0x2;
                goto WRITE;
            case '3':
            case '3'+0x30:
                if (!md) ky=0x3;
                goto WRITE;
            case '4':
            case '4'+0x30:
                if (!md) ky=0x4;
                goto WRITE;
            case '5':
            case '5'+0x30:
                if (!md) ky=0x5;
                goto WRITE;
            case '6':
            case '6'+0x30:
                if (!md) ky=0x6;
                goto WRITE;
            case '7':
            case '7'+0x30:
                if (!md) ky=0x7;
                goto WRITE;
            case '8':
            case '8'+0x30:
                if (!md) ky=0x8;
                goto WRITE;
            case '9':
            case '9'+0x30:
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
                        xd=!xd;
                        break;
                    case 1:
                        displaymode=2;
                        bufX=78;
                        md=0;
                        break;
                    case 2:
                        displaymode=0;
                        bufX=19;
                        md=1;
                        xd=!xd;
                        break;
                }
                for(int i=0;i<2048;i++) scrbuf[i]=0;
                goto SWITCH;
            case F12:
                goto OPEN;
            case TAB:
                md=!md;
                ConsoleX(3);
                goto UPDATE;
                break;
            case 0xA0:
            case 0xA1:
                up=!up;
                ConsoleX(0);
                break;
            case 0x23: // END KEY
                p=size;
                goto READ;
            case 0x24: // START KEY
                p=0;
                goto READ;
            case ESC:
                fclose(file);
                cls();
                free(scrbuf);
                exit(0);
        }
    }
}
