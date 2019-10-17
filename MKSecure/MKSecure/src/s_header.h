#pragma once
#include <Windows.h>
#include <malloc.h>
#include <Lmcons.h>
#include <iostream>
#include <direct.h>

#define LOG(X) std::cout << X << std::endl

#define __CC __stdcall
#define __ST __cdecl
#define __REG register

extern char C_TXT_PREFIX;
extern char C_TXT_WRONGPWD[];
extern char C_TXT_REQUESTPWD[];
extern char C_TXT_HIDDEN;
extern char C_TXT_KNOWN;
extern char C_TXT_SPACER;
extern char C_TXT_ENDL;
extern char C_FILE[];
extern char C_TXT_IN;
extern char C_TXT_OUT;

#define _MKSS_REGFUNCTIONS 4
#define _MKSS_MSGSIZE 16
#define _MKSS_REGFUNCTIONSIZE 6

#define _MKSS_K_LOCK   0x00
extern char C_MKSS_K_LOCK[_MKSS_REGFUNCTIONSIZE];
extern char C_MKSS_K_LOCK_FAILED[_MKSS_MSGSIZE];
extern char C_MKSS_K_LOCK_GOOD[_MKSS_MSGSIZE];

#define _MKSS_K_LOGGIN 0x01
extern char C_MKSS_LOGIN[_MKSS_REGFUNCTIONSIZE];
extern char C_MKSS_LOGIN_FAILED[_MKSS_MSGSIZE];
extern char C_MKSS_LOGIN_GOOD[_MKSS_MSGSIZE];

#define _MKSS_K_LTTRY  0x02
extern char C_MKSS_K_LTTRY[_MKSS_REGFUNCTIONSIZE];
extern char C_MKSS_K_LTTRY_FAILED[_MKSS_MSGSIZE];
extern char C_MKSS_K_LTTRY_GOOD[_MKSS_MSGSIZE];

#define _MKSS_K_WATCH 0x03
extern char C_MKSS_K_WATCH[_MKSS_REGFUNCTIONSIZE];
extern char C_MKSS_K_WATCH_FAILED[_MKSS_MSGSIZE];
extern char C_MKSS_K_WATCH_GOOD[_MKSS_MSGSIZE];
#define _MKSS_UNKNOW 0xEE
#define _MKSS_NONE   0xFF

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
extern SKEY k_Keylist[_MKSS_REGFUNCTIONS];

typedef cFunction SFUNC;
class cFunction
{
private:
	const static char c_Cascades = 5;
	const static char c_Cascadesize = 4;
	const static ushort s_Code_Entry[c_Cascades];
	const static ushort s_Code_Public[c_Cascades];

	static void __CC vFileread();
	static void __CC vRequestCheck(char&);
	static void __CC vPushValue(char);
public:
	static BOOL b_State_Locked, b_State_Watcher;
	void(*f_Register)(void*);
};
extern SFUNC k_Funclist[_MKSS_REGFUNCTIONS];
#define _BUFFER_S 64

#define W_COLOR_ERROR ( FOREGROUND_RED | FOREGROUND_INTENSITY)
#define W_COLOR_CMD (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define W_COLOR_PATH (FOREGROUND_BLUE  |FOREGROUND_GREEN| FOREGROUND_INTENSITY)
#define W_COLOR_OPER (FOREGROUND_BLUE  | FOREGROUND_INTENSITY)
#define W_COLOR_FEEDB (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define W_COLOR_CMDMSG (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)

typedef unsigned short ushort;
typedef const LPSTR c_LPSTR;

extern inline int __CC vTermLength(c_LPSTR);

class cStr
{
public:
	ushort s_Length{0};
	LPSTR c_pStr{0};

	cStr(c_LPSTR);
	cStr();

	void __CC vSet(c_LPSTR);
	void __CC vSet(cStr);
	void __CC vSet(ushort);

	void __CC vClean();

	void __CC vAppend(cStr *);
	void __CC vAppend(cStr );
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

	int __CC vReadInput(cStr*, LPDWORD );
	cStr c_LUser;
	cStr c_LDir;
};
class cIOSystem : public cConsole 
{
	public:
	void __ST vSetupBuffer();

	DWORD dw_KeyLength{0};
	cStr c_RawKey;
	DWORD dw_Key{ _MKSS_K_LOCK };
	void __CC vProcessRawKey();

	DWORD dw_Msg{ _MKSS_NONE };
	void __CC vProcessKey();
	void __CC vProcessMsg();
};


