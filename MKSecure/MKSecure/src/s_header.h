#pragma once
#include <Windows.h>
#include <malloc.h>
#include <Lmcons.h>
#include <iostream>
#include <direct.h>
#include <conio.h>

#define LOG(X) std::cout << X << std::endl

#define __CC __stdcall
#define __ST __cdecl
#define __REG register

typedef unsigned short ushort;
typedef unsigned long long int ULLI;
typedef const LPSTR c_LPSTR;

#define _MKS_REGKEY (ULLI)25

#define _MKSR_REGFUNCTIONS 4
#define _MKSR_REGISTERS 2

#define _MKSR_REGISTER_UNLOCKED 0
#define _MKSR_REGISTER_WATCHING 1

#define _MKSS_REGFUNCTIONSIZE 6
#define _MKSS_KEYS 2
#define _MKSS_MSGSIZE 20

extern char C_TXT_PREFIX[_MKSS_KEYS];
extern char C_TXT_BREAK[_MKSS_KEYS];

extern char C_TXT_ENDL;
extern char C_TXT_NEWL;

extern char C_FILE[];
extern char C_TXT_IN[_MKSS_KEYS];

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

extern void __CC vSetup();
extern char __CC vLoop();
extern int __CC vCleanup();
extern char __CC vCatchloop();
extern void __ST vAssetWarmup();

typedef struct sKey SKEY;
struct sKey {
	char* c_Key;
	char* c_Msg_Good;
	char* c_Msg_Failed;
};

#define _MKSS_BUFFERSIZE 64

#define _MKSC_COLOR_FAILED ( FOREGROUND_RED )
#define _MKSC_COLOR_UNKNOW ( FOREGROUND_RED | FOREGROUND_GREEN)
#define _MKSC_COLOR_GOOD ( FOREGROUND_GREEN )
#define _MKSC_COLOR_CMD (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY )
#define _MKSC_COLOR_NAME (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define _MKSC_COLOR_INPUT (FOREGROUND_BLUE | FOREGROUND_GREEN)

extern inline int __CC vTermLength(c_LPSTR);

typedef class CSTR CSTR;
class CSTR
{
public:
	ushort s_Length{0};
	LPSTR c_pStr{0};

	CSTR(c_LPSTR);
	CSTR();
	CSTR(ushort);

	void __CC vSet(c_LPSTR);
	void __CC vSet(CSTR);
	void __CC vSet(ushort);

	void __CC vClean();

	void __CC vAppend(CSTR *);
	void __CC vAppend(CSTR );
	void __CC vAppend(c_LPSTR);

	operator ushort() {
		return s_Length;
	}
	operator LPSTR() {
		return c_pStr;
	}
};

class cConsole
{
public:
	HANDLE o_HwndOutput{0};
	HANDLE o_HwndInput{0};

	BOOL __ST vLoadHandle();
	BOOL __ST vGetWinUser();
	BOOL __ST vGetWinDir();

	BOOL __CC vReadInput(CSTR*, LPDWORD );
	BOOL __CC vWriteOutput(c_LPSTR,DWORD, LPDWORD );
	BOOL __CC vGetConsoleInfo();
	BOOL __CC vSetTextColor(WORD );
	BOOL __CC vBreak();


	CSTR c_LUser;
	CSTR c_LDir;

};
typedef class cIOSystem IOSYS;
class cIOSystem : public cConsole 
{
	public:
	void __ST vSetupBuffer();

	DWORD dw_KeyLength{0};
	CSTR c_RawKey;
	DWORD dw_Key{ _MKSS_NONE };
	void __CC vProcessRawKey();

	DWORD dw_Msg{ _MKSS_NONE };
	void __CC vProcessKey();
	void __CC vProcessMsg();
};

typedef class cFunction SFUNC;
class cFunction
{

	static void __CC vFileread();
	static void __CC vRequestCheck();


public:
	static BOOL b_pStateBuffer[_MKSR_REGISTERS];
	
	SKEY k_Key;

	BOOL (*f_Register)(SFUNC*, IOSYS*);
};
extern SFUNC k_Funclist[_MKSR_REGFUNCTIONS];

extern BOOL
vRegister_break(SFUNC*, IOSYS*);
extern BOOL	  
vRegister_login(SFUNC*, IOSYS*);
extern BOOL	   
vRegister_watch(SFUNC*, IOSYS*);
extern BOOL	  
vRegister_lttry(SFUNC*, IOSYS*);

