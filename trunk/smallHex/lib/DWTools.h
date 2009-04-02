#define byte  unsigned char
#define int16 short int
#define int32 long int
#define int64 long long

#define PrintMenu(x,y,z)   _PrintMenu(x,y,sizeof(z)/4,z)

byte   GetLibVerMax();
byte   GetLibVerMin();
byte   GetLibVerRel();
char  *GetLibVerDate();
char  *GetLibWebsite();
void   GetLibAbout();

// General Functions
void   cls();
int    GetTextLong(char *);
void   printCenter(char *);
void   printRight(char *,byte);

// System
bool   GetAdminMode();
char  *GetOSTechnology();
char  *GetCurrentUsername();
char  *GetTempDir();
char  *GetOSVersion();
char  *GetOSBuild();
char  *GetOSBuildLab();
char  *GetOSName();
char  *GetOSSP();
char  *GetOSSPBuild();
char  *GetOSSystemRoot();
char  *GetOSRegOwner();
char  *GetOSRegOrganization();

// Registry
long   RegCreateKeys(HKEY,char*);
long   RegSetString(HKEY,char*,char*,char*);
long   RegSetByte(HKEY,char*,char*,int);
byte  *RegGetString(HKEY,char*,char*);
long   RegGetByte(HKEY,char*,char*);
byte  *RegGetBin(HKEY,char*,char*);

// Console
COORD  GetBufferSize();
byte   GetBufferSizeX();
byte   GetBufferSizeY();
void   SetBufferSize(COORD);
void   SetBufferSizeX(byte);
void   SetBufferSizeY(byte);

// Input / OutputCOORD GetMouseXY();
COORD  GetMouseXY();
byte   GetMouseX();
byte   GetMouseY();
bool   GetMouseKey(byte);
byte   GetKeyPress();
byte   GetSyncKeyPress();
bool   GetKeyPress(byte);
bool   GetSyncKeyPress(byte);
void   EmuKey(byte);
void   EmuKey(byte,byte);
void   EmuKey(byte,byte,byte);
void   SetMouseCoord(COORD);
void   SetMouseCoord(byte,byte);
void   EmuMousePress(byte);
byte   Pause();
byte   PauseEx();
void   Pause(byte);


// Cursor Options
byte   GetCursorSize();
bool   GetCursorVisible();
void   SetCursor(byte,bool);
void   SetCursorSize(byte);
void   SetCursorVisible(bool);
byte   GetX();
byte   GetY();
COORD  GetXY();
void   SetX(byte);
void   SetY(byte);
void   SetXY(byte,byte);
void   SetXY(COORD);

// Colors
byte   GetColors();
byte   GetTextColor();
byte   GetBackColor();
void   SetColors(byte);
void   SetTextColor(byte);
void   SetBackColor(byte);

// Menus
void   SetMenuOption(byte);               // Set the inital menu option
byte   GetMenuOption();
void  _PrintMenu(byte,byte,byte,char**);  // SetX,SetY,Size,Texts
byte   MenuCycle(byte,byte,byte);
byte   MenuCycleEx(byte,byte,byte);

// Design
void   DesingLineX(byte,byte,byte);
void   DesingLineY(byte,byte,byte);
void   DesingDLineX(byte,byte,byte);
void   DesingDLineY(byte,byte,byte);
void   DesignLineLinkX(byte,byte,byte);
void   DesignLineDLinkX(byte,byte,byte);
void   DesignDLineLinkX(byte,byte,byte);
void   DesignDLineDLinkX(byte,byte,byte);
void   DesignLineLinkY(byte,byte,byte);
void   DesignLineDLinkY(byte,byte,byte);
void   DesignDLineLinkY(byte,byte,byte);
void   DesignDLineDLinkY(byte,byte,byte);
void   DesignSquare(byte,byte,byte);
void   DesignDSquare(byte,byte,byte);
void   DesignRect(byte,byte,byte,byte);
void   DesignDRect(byte,byte,byte,byte);
void   DesignEmptyLineX(byte,byte,byte);
void   DesignEmptyLineY(byte,byte,byte);
void   DesignEmptySquare(byte,byte,byte line);
void   DesignEmptyRect(byte,byte,byte,byte);

// Date and Time
int16  GetDateYear();
byte   GetDateMonth();
byte   GetDateDayOfWeek();
byte   GetDateDay();
byte   GetTimeHours();
byte   GetTimeMinutes();
byte   GetTimeSeconds();
int16  GetTimeMilliseconds();
void   SetTimeYear(int16);
void   SetTimeMonth(byte);
void   SetTimeDay(byte);
void   SetTimeHours(byte);
void   SetTimeMinutes(byte);
void   SetTimeSeconds(byte);
void   SetTimeMilliseconds(int16);
int    TimeScan(); // For Milliseconds,Seconds,Minutes, Hours and Days
int    TimeScanSimple(); // For Milliseconds,Seconds,Minutes and Hours
int64  TimeScanAdvance(); // For Milliseconds,Seconds,Minutes, Hours, Days and Months
int    TimeResult(int);
int    TimeResult(int,int);
int    TimeResultSeconds(int);
int    TimeResultSeconds(int,int);
int    TimeResultMinutes(int);
int    TimeResultMinutes(int,int);
int    TimeResultHours(int);
int    TimeResultHours(int,int);

// Checksums
int    NCA1(char*);
int    NCA2(char*);
int    NCA1File(char*);
int    NCA2File(char*);

// Classes
class Binary{
    public:
        void set(byte);
        bool get(byte);
};
