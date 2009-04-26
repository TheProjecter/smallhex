#define byte  unsigned char
#define int16 short int
#define int32 unsigned int
#define int64 DWORD64

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
char  *GetFileName(char *);
void   printCenter(char *);
void   printRight(char *,byte);
bool  *GetBin(byte);

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
bool   GetConsoleFocus();
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

// Draw
void   DrawLineX(byte,byte,byte);
void   DrawLineY(byte,byte,byte);
void   DrawDLineX(byte,byte,byte);
void   DrawDLineY(byte,byte,byte);
void   DrawLineLinkX(byte,byte,byte);
void   DrawLineDLinkX(byte,byte,byte);
void   DrawDLineLinkX(byte,byte,byte);
void   DrawDLineDLinkX(byte,byte,byte);
void   DrawLineLinkY(byte,byte,byte);
void   DrawLineDLinkY(byte,byte,byte);
void   DrawDLineLinkY(byte,byte,byte);
void   DrawDLineDLinkY(byte,byte,byte);
void   DrawSquare(byte,byte,byte);
void   DrawDSquare(byte,byte,byte);
void   DrawRect(byte,byte,byte,byte);
void   DrawDRect(byte,byte,byte,byte);
void   DrawEmptyLineX(byte,byte,byte);
void   DrawEmptyLineY(byte,byte,byte);
void   DrawEmptySquare(byte,byte,byte line);
void   DrawEmptyRect(byte,byte,byte,byte);

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

// Processes
HANDLE AttachProcess(const char);
bool   ReleaseProcess(HANDLE);
int   *RamRead(HANDLE,int,int);
bool   RamWrite(HANDLE,int,int*,int);
