#pragma once
#include <Windows.h>
#include <malloc.h>
#include <Lmcons.h>
#include <iostream>

#define LOG(X) std::cout << X << std::endl

#define _USEREGISTER
#define __CC __stdcall

#ifdef _USEREGISTER 
#define __REG register
#else
#define __REG 
#endif

#define W_COLOR_ERROR ( FOREGROUND_RED | FOREGROUND_INTENSITY)
#define W_COLOR_CMD (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define W_COLOR_PATH (FOREGROUND_BLUE  |FOREGROUND_GREEN| FOREGROUND_INTENSITY)
#define W_COLOR_OPER (FOREGROUND_BLUE  | FOREGROUND_INTENSITY)
#define W_COLOR_FEEDB (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define W_COLOR_CMDMSG (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)

typedef unsigned short ushort;
typedef const LPSTR c_LPSTR;
namespace text 
{
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
}

#define _MKSS_LOCKED 0x2FF
#define _MKSS_LOGGIN 0x2FE
#define _MKSS_UNLOCK 0x2EE

#define _MKSS_FAILED 0x10E
#define _MKSS_UNKNOW 0x1E0
#define _MKSS_NONE   0x100

namespace mks {

	const static ushort S_KEY = 123456;

	class cConsole
	{
	public:
		HANDLE o_HwndOutput;
		HANDLE o_HwndInput;

		void __CC vLoadHandle();
		void __CC vGetWinUser();
		text::cStr c_LUser;
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
		text::cStr c_RequestEntry;
		void __CC vRequestInput(DWORD);
		void __CC vProcessMsg(DWORD);
	};
	class cIOSystem : public cPassword
	{
	public:
		DWORD dw_State{ _MKSS_LOCKED };
		DWORD dw_Msg{ _MKSS_NONE };
		void __CC vProcessRequest(text::cStr *);
	};
	extern void __CC vSetup();
	extern char __CC vLoop();
	extern int __CC vCleanup();
	extern char __CC vCatchloop();
}
