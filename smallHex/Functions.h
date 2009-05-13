#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "lib\DWTools.h"
#include "lib\DWToolsDef.h"

#define KeyA(i) GetAsyncKeyState(i)
#define Key(i) GetAsyncKeyState(i)==-32767

bool kh=0,md=0,up=0,xd=1,patch=1,focus;
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
byte HexInput(){
    byte ky=0;
    for(register int i=0x2F;i<0x70;i++) if(Key(i)) ky=i;
    if (ky>=0x30&&ky<=0x39) return ky-0x30;
    else if (ky>=0x60&&ky<=0x69) return ky-0x60;
    else if (ky>='A'&&ky<='F') return ky-0x37;
    else return 0xFF;
}
void ConsoleX(byte t){
    SetXY(11,24);
    switch (t){
        case 0:
INFO:
            SetXY(65,24);
            divid=1;
            for(divid=1;divid*1024<size;divid*=1024) if(divid>1073741823) break;
            printf("[ %4u",size/divid);
            if (divid<1<<10) printf("B ");
            else if (divid<(1<<20)) printf("KB");
            else if (divid<(1<<30)) printf("MB");
            else printf("GB");
            if (patch) printf(" P");
            else printf("  ");
            if (!md) printf("H ]");
            else if (!up) printf("c ]");
            else printf("C ]");
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
        case 4:
            printf("Offset                              ");
            break;
        case 5:
            printf("Error: The offset is too big...     ");
            Sleep(1000);
            break;
        case 6:
            printf("Patch Mode changed                  ");
            goto INFO;
            break;
        case 7:
            printf("Patch Created :D                    ");
            Sleep(1000);
            break;
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
int Menu(){
    #define MENUX 18
    #define MENUY 6
    const char *mode[3]={"Hex/Char Mode","Only Hex Mode","Only Char Mode"};
    const char *edit[3]={"Hex Edit ","Char Edit","CHAR Edit"};
    const char *menu[3]={"Go to Offset","Create Patch","New File"};
    int cx=(GetBufferSizeX()-MENUX)/2;
    int cy=(GetBufferSizeY()-MENUY)/2-3;
    FillDRect(cx,cy,MENUX,MENUY);
REMENU:
    SetXY(cx+3,cy+1); printf("%s",mode[displaymode]);
    SetXY(cx+3,cy+2); printf("%s",edit[md+up]);
    for(int i=0;i<MENUY-3;i++){
        SetXY(cx+3,cy+3+i); printf("%s",menu[i]);
    }
    SetXY(cx+1,cy+GetMenuOption()); printf(">");
    while(1){
        Sleep(1);
        MenuCycle(cx+1,cy,MENUY-1);
        if (Key(RETURN)){
            switch(GetMenuOption()){
                case 2:
                    if (!md) md=1;
                    else if (!up) up=1;
                    else {
                        up=0;
                        md=0;
                    }
                    ConsoleX(3);
                    goto REMENU;
                default:
                    return GetMenuOption();
            }
        }
        else if (Key(CTRLSX)||Key(CTRLDX)) return 0;
    }
}
void Help(){
    #define HELP 8
    const char *help[HELP]={" F1   Help"," F2   Undo"," F3   Go to Offset"," F4   Change Display Mode"," F5   Patch Mode"," ","TAB   Switch Input Mode","ESC   Close smallHex"};
    for(int i=0;i<HELP;i++){
        SetXY(3,1+i); printf("%s",help[i]);
    }
    DrawLineLinkY(7,0,GetBufferSizeY()-2);
}
