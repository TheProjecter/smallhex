#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "lib\DWTools.h"
#include "lib\DWToolsDef.h"

#define KeyA(i) GetAsyncKeyState(i)
#define Key(i) GetAsyncKeyState(i)==-32767

bool kh=0,md=0,up=0,xd=1,mu=0,focus;
int32 p=0,size,divid;
byte displaymode=0;
byte bufX=19,bufY=23,
     posXH=1;
FILE *file;

DWORD FocusThread(){
    while(1){
        Sleep(5);
        focus=GetConsoleFocus();
    }
}
void ConsoleX(byte t){
    SetXY(11,24);
    switch (t){
        case 0:
INFO:
            SetXY(66,24);
            divid=1;
            for(divid=1;divid*1024<size;divid*=1024) if(divid>1073741823) break;
            printf("[ %4u",size/divid);
            if (divid<1<<10) printf("B ");
            else if (divid<(1<<20)) printf("KB");
            else if (divid<(1<<30)) printf("MB");
            else printf("GB");
            if (!md) printf(" H ]");
            else if (!up) printf(" c ]");
            else printf(" C ]");
            break;
        case 1:
            printf("Reading to Offset: %08X/%08X",p,size);
            kh=0;
            break;
        case 2:
            printf("Writing to Offset: %08X/%08X",p,size);
            break;
        case 3:
            printf("Switched the input mode             ");
            goto INFO;
        case 0xFF:
            SetXY(2,24);
            printf("Console: ");
            goto INFO;
    }
}
void ChangeDisplayMode(){
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
            md=1;
            break;
        case 2:
            displaymode=0;
            bufX=19;
            md=0;
            xd=!xd;
            break;
    }
}
char Alias(register char Char){
    switch(Char){
        case 0x00: // NULL
        case 0x07: // BEEP
        case 0x08: // BACKSPACE
        case 0x09: // TAB
        case 0x0A: // NEW LINE
        case 0x0D: // RETURN
            return 0x20;
        default:
            return Char;
    }
}
void write(byte code){
    fseek(file,p,SEEK_SET);
    fprintf(file,"%c",code);
    ConsoleX(2);
}
int FileSize(FILE *file){
    fseek(file,0,SEEK_END);
    return ftell(file);
}
void Menu(){
    #define MENUX 18
    #define MENUY 5
    const char *mode[3]={"Hex/Char Mode","Only Hex Mode","Only Char Mode"};
    const char *edit[3]={"Hex Edit","Char Edit","CHAR Edit"};
    const char *menu[2]={"Go to Offset","New File"};
    int cx=(GetBufferSizeX()-MENUX)/2;
    int cy=(GetBufferSizeY()-MENUY)/2-3;
    FillDRect(cx,cy,MENUX,MENUY);
REMENU:
    SetXY(cx+3,cy+1); printf("%s",mode[displaymode]);
    SetXY(cx+3,cy+2); printf("%s",edit[md+up]);
    for(int i=0;i<2;i++){
        SetXY(cx+3,cy+3+i); printf("%s",menu[i]);
    }
    SetXY(cx+1,cy+GetMenuOption()); printf(">");
    while(!(Key(ESC))&&!(Key(CTRLSX))&&!(Key(CTRLDX))&&!mu){
        Sleep(1);
        MenuCycle(cx+1,cy,MENUY-1);
        if (Key(RETURN)){
            switch(GetMenuOption()){
                case 1:
                    ChangeDisplayMode();
                    mu=1;
                    break;
            }
        }
    }
}
