#include "Functions.h"
#define DEBUG

int32 p=0;

int main(){
    byte *buf=(byte*)malloc(4096);
    FILE *file;
    char *path;
    SetConsoleTitle("smallHex");
    #ifdef DEBUG
        path="..\\smallhex\\test.bin";
        file=fopen("test.bin","r+b");
    #else
        printf("File to open: ");
        scanf("%s",path);
    #endif
    file=fopen(path,"r+b");
WRITE:
    cls();
    fseek(file,p,SEEK_SET);
    fread(buf,1,4096,file);
    for(int i=0;i<720;i++) printf("%02X ",buf[i]);
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
        else if (Key(ESC))
            exit(0);
    }
}
