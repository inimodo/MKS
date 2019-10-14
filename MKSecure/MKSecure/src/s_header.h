#pragma once
#include <Windows.h>
#include <malloc.h>

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
typedef char* charp;
namespace text 
{
	class cStr
	{
	private:
		charp c_pStr;
		ushort s_Length;
	public:
		void __CC vSet(const charp);
		void __CC vClean();
		void __CC vAppend(cStr *);
		charp __CC vGet();
	};

	static cStr c_LUser;
	const static char C_TXT_PREFIX = '@';
	const static char C_TXT_WRONGPWD[] = "INVALID KEY\n";
	const static char C_TXT_WRONGPWD[] = "KEY REQUEST\n";
	const static char C_TXT_HIDDEN = '*';
	const static char C_TXT_KNOWN = '_';
	const static char C_TXT_SPACER = '-';
	const static char C_TXT_ENDL = '\n';
	extern void __CC vReaduser();
}

namespace mks {

	const static unsigned short S_KEY = 123456;
	const static char S_FILE[] = "cfile.key";
	static char s_Startup[];

	static class cConsole
	{
	private:
		static HANDLE o_HwndOutput;
		static HANDLE o_HwndInput;
	public:
		void __CC vLoadHandle();
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
	class cIBuffer : public cConsole 
	{
		
	};

	static cIBuffer o_Buffer;

	extern void __CC vSetup();
	extern char __CC vLoop();
	extern int __CC vCleanup();
	extern char __CC vCatchloop();
}