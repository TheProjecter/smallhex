// smallHex SVN => http://code.google.com/p/smallhex/
#include "Functions.h"

int main(){
#ifdef DEBUG
    SetConsoleTitle("smallHex SVN");
#else
    SetConsoleTitle("smallHex (Beta)");
#endif
    SetCursorVisible(false);
    SetBufferSizeY(25);
    DWORD dwThreadId, dwThrdParam = 1;
    HANDLE thFocus = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)FocusThread,&dwThrdParam,0,&dwThreadId);
    bool mu=0; int px;
    byte *buf=(byte*)malloc(2048);
    char *scrbuf=(char*)malloc(80*25);
    byte *pB=(byte*)malloc(0x7FFF);
    int  *pO=(int *)malloc(0x7FFF);
    byte *pX=(byte*)malloc(0x7FFF);
    int  *pA=(int *)malloc(0x7FFF);
    int pP=0,pY=0;
    char hexbuf[2];
    char *path;
OPEN:
    p=0;
    cls();
    #ifdef DEBUG
        path="test.bin";
    #else
        SetBackColor(DWHITE); SetTextColor(BLACK);
        DrawEmptyLineX(0,0,GetBufferSizeX());
        SetY(0); printCenter("- Welcome to smallHex -");
        SetBackColor(BLACK); SetTextColor(DWHITE);
        DrawLineX(1,21,GetBufferSizeX()-2);
        SetXY(1,22); printf("smallHex Beta Revision 22");
        printRight("Software created by Xeeynamo",1);
        SetXY(1,23); printf("DWTools Lib v.%i.%i.%i [%s]",GetLibVerMax(),GetLibVerMin(),GetLibVerRel(),GetLibVerDate());
        printRight("http://digitalwork.altervista.org",1);
        SetXY(2,3);
        printf("File to open: ");
        scanf("%s",path);
    #endif
    file=fopen(path,"r+b");
    size=FileSize(file)-1;
    register byte ky=0;
SWITCH:
    cls();
    COORD conbuf={GetBufferSizeX(),GetBufferSizeY()};
    DrawLineX(1,conbuf.Y-2,conbuf.X-2);
    ConsoleX(0xFF);
    for(int i=0;i<2048;i++) scrbuf[i]=0;
READ:
    fseek(file,p,SEEK_SET);
    fread(buf,1,2048,file);
    ConsoleX(1);
    SetXY(0,0);
    for(int y=0;y<bufY;y++){
        scrbuf[0+conbuf.X*y]=0x20;
        if (displaymode!=2){
            for(int x=0;x<bufX;x++){
                if (((x+bufX*y)+p)>size){
                    scrbuf[x*3+1+conbuf.X*y]=0x20;
                    scrbuf[x*3+2+conbuf.X*y]=0x20;
                }
                else {
                    sprintf(hexbuf,"%02X",buf[x+bufX*y]);
                    scrbuf[x*3+1+conbuf.X*y]=hexbuf[0];
                    scrbuf[x*3+2+conbuf.X*y]=hexbuf[1];
                }
                scrbuf[x*3+3+conbuf.X*y]=0x20;
            }
        }
        scrbuf[bufX*3+1+conbuf.X*y]=0x20;
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
                        if (displaymode==2) scrbuf[x+1+conbuf.X*y]=0x20;
                        else scrbuf[x+(bufX*3)+2+conbuf.X*y]=0x20;
                        break;
                    default:
                        if (((x+bufX*y)+p)>size) goto NULLCHAR;
                        else if (displaymode==2) scrbuf[x+1+conbuf.X*y]=buf[x+bufX*y];
                        else scrbuf[x+(bufX*3)+2+conbuf.X*y]=buf[x+bufX*y];
                }
            }
        scrbuf[conbuf.X-1-xd+conbuf.X*y]=' ';
        scrbuf[conbuf.X-1+conbuf.X*y]=' ';
    }
    printf("%s",scrbuf);
    if (0){
WRITE:
        pB[pP]=buf[0];
        pO[pP]=p;
        pP++;
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
        if (patch){
            bool z=0;
            for(int i=0;i<pY;i++){
                if (pA[i]==p){
                    pX[i]=buf[0];
                    z=1;
                }
            }
            if (!z){
                pA[pY]=p;
                pX[pY]=buf[0];
                pY++;
            }
        }
        write(buf[0]);
        if (md) p++;
        else if (!kh) p++;
        if (0){
UNDO:
            write(buf[0]);
        }
        goto READ;
    }
UPDATE:
    if (displaymode==0||displaymode==1){
        SetTextColor(LRED);
        if (!md){
            if (1){ // NEW HEXEDIT SYSTEM ACTIVATED!! ;)
                SetXY(posXH+kh,0);
                if (!kh) printf("%X",buf[0]>>4);
                else printf("%X",buf[0]-(buf[0]>>4<<4));
            }
            else {
                SetXY(posXH,0); printf("%02X",buf[0]);
            }

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
WHILEEX:
    ky=0;
    if (mu){
MENU:
        mu=0;
        switch(Menu()){
            case 0:
                goto READ;
            case 1:
                ChangeDisplayMode();
                mu=1;
                goto SWITCH;
            case 3:
GOTOOFFSET:
                ConsoleX(4);
                register byte k;
                px=0;
                while(1){
                    Sleep(1);
                    k=HexInput();
                    if (k<0x10){
                        px=(px<<4)+k;
OFFSET:
                        SetXY(11,24); printf("Offset %8X",px);
                    }
                    else if (Key(BACKSPC)){
                        px>>=4;
                        goto OFFSET;
                    }
                    else if (Key(RETURN)){
                        if (px<=size){
                            p=px;
                        }
                        else ConsoleX(5);
                        goto READ;
                    }
                }
            case 4:
                FILE *patch=fopen("test.shpatch","w+b");
                fwrite(pO,1,pY,patch);
                fwrite(pX,1,pY,patch);
                fclose(patch);
                ConsoleX(7);
                pX=0;
                pY=0;
                goto OPEN;
            case 5:
                goto OPEN;
        }
    }
    while(1){
NOFOCUS:
        Sleep(1);
        if (!focus) goto NOFOCUS;

        for(register int i=/*8*/1;i<0xA6;i++)
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
            case F1:
                FillRect(1,0,conbuf.X-3,conbuf.Y-2);
                Help();
                Pause(RETURN);
                DrawLineX(1,conbuf.Y-2,conbuf.X-2);
                break;
            case F2:
                if (pP>0){
                    pP--;
                    p=pO[pP];
                    buf[0]=pB[pP];
                    goto UNDO;
                }
                break;
            case F3:
                goto GOTOOFFSET;
            case F4:
                ChangeDisplayMode();
                goto SWITCH;
            case F5:
                patch=!patch;
                ConsoleX(6);
            case F12:
                goto OPEN;
            case TAB:
                if (displaymode==0){
                    md=!md;
                    up=0;
                    ConsoleX(3);
                    goto WHILEEX;
                }
            case 0xA0:
            case 0xA1:
                if (md){
                    up=!up;
                    ConsoleX(0);
                }
                goto WHILEEX;
            case 0x23: // END KEY
                p=size;
                goto READ;
            case 0x24: // START KEY
                p=0;
                goto READ;
            case CTRLDX:
            case CTRLSX:
                goto MENU;
            case ESC:
                fclose(file);
                cls();
                free(buf);
                free(scrbuf);
                exit(0);
        }
    }
}
