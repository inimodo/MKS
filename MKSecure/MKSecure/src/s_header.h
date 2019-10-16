#pragma once
#include <Windows.h>
#include <malloc.h>
#include <Lmcons.h>
#include <iostream>
#include <direct.h>

#define LOG(X) std::cout << (X) << std::endl

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

#define _MKSS_KEYS 4
#define _MKSS_MSGSIZE 16
#define _MKSS_KEYSIZE 6

#define _MKSS_LOCK   0x0
extern char C_MKSS_LOCK[_MKSS_KEYSIZE];
extern char C_MKSS_LOCK_FAILED[_MKSS_MSGSIZE];
extern char C_MKSS_LOCK_GOOD[_MKSS_MSGSIZE];

#define _MKSS_LOGGIN 0x1
extern char C_MKSS_LOGIN[_MKSS_KEYSIZE];
extern char C_MKSS_LOGIN_FAILED[_MKSS_MSGSIZE];
extern char C_MKSS_LOGIN_GOOD[_MKSS_MSGSIZE];

#define _MKSS_LTTRY  0x2
extern char C_MKSS_LTTRY[_MKSS_KEYSIZE];
extern char C_MKSS_LTTRY_FAILED[_MKSS_MSGSIZE];
extern char C_MKSS_LTTRY_GOOD[_MKSS_MSGSIZE];

#define _MKSS_WATCH 0x3
extern char C_MKSS_WATCH[_MKSS_KEYSIZE];
extern char C_MKSS_WATCH_FAILED[_MKSS_MSGSIZE];
extern char C_MKSS_WATCH_GOOD[_MKSS_MSGSIZE];

#define _MKSS_GOOD	 0x10F
#define _MKSS_FAILED 0x10E
#define _MKSS_UNKNOW 0x1E0
#define _MKSS_NONE   0x100

extern void __ST vAssetWarmup();

typedef struct sKey SKEY;
struct sKey {
	void(*f_Event)();
	char* c_Key;
	char* c_Msg_Good;
	char* c_Msg_Failed;
};
extern SKEY k_Keylist[_MKSS_KEYS];

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


const static ushort S_KEY;

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
class cPassword
{
protected:
	const static char c_Cascades = 5;
	const static char c_Cascadesize = 4;
	const static ushort s_Code_Entry[c_Cascades];
	const static ushort s_Code_Public[c_Cascades];
public:
	void __CC vFileread();
	void __CC vRequestCheck(char&);
	void __CC vPushValue(char);
};
class cIOBuffer : public cConsole 
{
	public:
	void __ST vSetupBuffer();

	void __CC vRequestInput(cStr*);
	void __CC vProcessOutput(DWORD);

};
class cIOSystem : public cPassword
{
public:
	void __ST vSetupBuffer();

	cStr c_RawKey;
	DWORD dw_Key{ _MKSS_LOCK };
	void __CC vProcessRawKey();

	DWORD dw_Msg{ _MKSS_NONE };
	void __CC vProcessKey();
};
extern void __CC vSetup();
extern char __CC vLoop();
extern int __CC vCleanup();
extern char __CC vCatchloop();

