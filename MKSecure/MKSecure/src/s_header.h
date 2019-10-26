#pragma once
#include <Windows.h>
#include <malloc.h>
#include <Lmcons.h>
#include <iostream>
#include <direct.h>
#include <conio.h>

#define LOG(X) std::cout << X << std::endl

#define _MKSW_BUFFERS 2
#define _MKSW_BUFFERS_INPUT 0
#define _MKSW_BUFFERS_OUTPUT 1

#define _MKSW_WIDTH 45
#define _MKSW_HEIGHT 30
#define _MKSW_INHEIGHT (_MKSW_HEIGHT-2)


#define _MKSW_INDEX(CD,CS) (int)((((COORD)CD).Y*((COORD)CS).X)+((COORD)CD).X)
#define __CC __stdcall
#define __ST __cdecl
#define __REG register

typedef unsigned short ushort;
typedef unsigned long long int ULLI;
typedef const LPSTR c_LPSTR;

#define _MKS_REGKEY (ULLI)(137*173)

#define _MKSR_REGFUNCTIONS 4
#define _MKSR_REGISTERS 2


#define _MKSR_REGISTER_UNLOCKED 0
#define _MKSR_REGISTER_WATCHING 1

#define _MKSS_REGFUNCTIONSIZE 6
#define _MKSS_KEYS 2
#define _MKSS_MSGSIZE 20

extern char C_TXT_PREFIX;
extern char C_TXT_IN;

extern char C_TXT_BREAK[_MKSS_KEYS];
extern char C_TXT_ENDL;
extern char C_TXT_NEWL;

extern char C_FILE[];

extern char C_MKSS_K_UNKNOW[_MKSS_MSGSIZE];
extern char C_MKSS_K_PERM[_MKSS_MSGSIZE];

#define _MKSS_K_LOCK   0x00
extern char C_MKSS_K_LOCK[_MKSS_REGFUNCTIONSIZE];
extern char C_MKSS_K_LOCK_FAILED[_MKSS_MSGSIZE];
extern char C_MKSS_K_LOCK_GOOD[_MKSS_MSGSIZE];

#define _MKSS_K_LOGGIN 0x01
extern char C_MKSS_K_LOGIN[_MKSS_REGFUNCTIONSIZE];
extern char C_MKSS_K_LOGIN_FAILED[_MKSS_MSGSIZE];
extern char C_MKSS_K_LOGIN_GOOD[_MKSS_MSGSIZE];

extern char C_MKSS_K_LOGIN_CN[_MKSS_MSGSIZE];
extern char C_MKSS_K_LOGIN_HIDER;

#define _MKSS_K_LTTRY  0x02
extern char C_MKSS_K_LTTRY[_MKSS_REGFUNCTIONSIZE];
extern char C_MKSS_K_LTTRY_FAILED[_MKSS_MSGSIZE];
extern char C_MKSS_K_LTTRY_GOOD[_MKSS_MSGSIZE];

#define _MKSS_K_WATCH 0x03
extern char C_MKSS_K_WATCH[_MKSS_REGFUNCTIONSIZE];
extern char C_MKSS_K_WATCH_FAILED[_MKSS_MSGSIZE];
extern char C_MKSS_K_WATCH_GOOD[_MKSS_MSGSIZE];
#define _MKSS_UNKNOW 0xEE

#define _MKSS_NONE   0xAFA
#define _MKSS_GOOD	 0xAAA
#define _MKSS_FAILED 0xFFF



typedef struct sKey SKEY;
struct sKey {
	char*		c_Key;
	char*		c_Msg_Good;
	char*		c_Msg_Failed;
};

#define _MKSS_BUFFERSIZE 64

#define _MKSC_BACKGROUND (0)
#define _MKSC_COLOR_FAILED ( FOREGROUND_RED )
#define _MKSC_COLOR_UNKNOW ( FOREGROUND_RED | FOREGROUND_GREEN)
#define _MKSC_COLOR_GOOD ( FOREGROUND_GREEN )
#define _MKSC_COLOR_CMD (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY )
#define _MKSC_COLOR_NAME (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define _MKSC_COLOR_INPUT (FOREGROUND_BLUE | FOREGROUND_GREEN)
#define _MKSC_COLOR_BORDER (FOREGROUND_RED)

extern inline int __CC vTermLength(c_LPSTR);
extern inline ULLI __CC vTenth(char);

typedef class mks MKS;
typedef class mks_func SFUNC;
typedef class mks_str CSTR;
typedef class mks_buffer BUFFER;

class mks_str
{
public:
				mks_str(c_LPSTR);
				mks_str();
				mks_str(ushort);

	ushort		s_Length{ 0 };
	LPSTR		c_pStr{ 0 };

	void __CC	vSet(c_LPSTR);
	void __CC	vSet(CSTR);
	void __CC	vSet(ushort);

	void __CC	vClean();

	void __CC	vAppend(CSTR*);
	void __CC	vAppend(CSTR);
	void __CC	vAppend(c_LPSTR);

	operator ushort() {
		return s_Length;
	}
	operator LPSTR() {
		return c_pStr;
	}
};
class mks_buffer {
public:

	CHAR_INFO*	c_pBuffer;
	COORD		dw_Size,dw_Cursor,dw_Pos;
	HANDLE		o_Output;
	SMALL_RECT	sm_Rect;
	BOOL		b_Border;

	BOOL __CC	vSetup(COORD, COORD, HANDLE, BOOL);
	void __CC	vCleanup();

	BOOL __CC	vWriteOutput(c_LPSTR, DWORD, WORD);
	BOOL __CC	vWriteOutput( CHAR, WORD, BOOL);
	BOOL __CC	vReadInput(CSTR*, LPDWORD, WORD);
	BOOL __CC	vWriteBuffer();
	void __CC	vBreak();
	void __CC	vBufferClear();
	void __CC	vSetCursor(COORD);
	void __CC	vSetCursor(SHORT,SHORT);
};
class mks_func
{
	static void __CC vFileread();
	static void __CC vRequestCheck();
public:
	static BOOL b_pStateBuffer[_MKSR_REGISTERS];
	SKEY		k_Key;
	BOOL		(*f_Register)(void*, BUFFER*);
};
class mks 
{
private:
	SFUNC		k_Funclist[_MKSR_REGFUNCTIONS];
	HANDLE		o_HwndOutput{ 0 };
	HANDLE		o_HwndInput{ 0 };

	CSTR		c_LUser,c_LDir;

	DWORD		dw_KeyLength{ 0 };
	CSTR		c_RawKey;

	DWORD		dw_Key{ _MKSS_NONE };
	DWORD		dw_Msg{ _MKSS_NONE };

	BUFFER		b_Buffers[_MKSW_BUFFERS];
	
public:
	void __ST	vAssetWarmup();
	BOOL __ST	vSetupHandle();

	void __CC	vProcessRawKey();
	void __CC	vProcessKey();
	void __CC	vProcessMsg();

	BOOL __CC	vSetup();
	BOOL __CC	vLoop();
	BOOL __CC	vCatchloop();
	int __CC	vCleanup();
};




extern BOOL
vRegister_break(void*, BUFFER*);
extern BOOL	  
vRegister_login(void*, BUFFER*);
extern BOOL	   
vRegister_watch(void*, BUFFER*);
extern BOOL	  
vRegister_lttry(void*, BUFFER*);

