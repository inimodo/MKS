#pragma once
#include <Windows.h>
#include <malloc.h>
#include <Lmcons.h>
#include <iostream>
#include <direct.h>
#include <conio.h>

#include "s_literals.h"
#include "s_constants.h"

#define LOG(X) std::cout<<X<<std::endl

#define __CC __stdcall
#define __ST __cdecl
#define __REG register


typedef unsigned short ushort;
typedef unsigned long long int ULLI;
typedef const LPSTR c_LPSTR;

typedef class mks MKS;
typedef class mks_func SFUNC;
typedef class mks_str CSTR;
typedef class mks_buffer BUFFER;
typedef struct mks_buffer_info BUFFER_INFO;
typedef class mks_branch BRANCH;

extern inline int __CC	vTermLength(c_LPSTR);
extern inline ULLI __CC vTenth(char);
extern inline int __CC vStringToInt(CSTR, DWORD);
extern inline int __CC vStringToInt(CSTR, DWORD,DWORD);
extern inline int __CC vIntToString(int, CSTR*);

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
	void __CC	vClear();

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
struct mks_buffer_info {
	COORD dw_Pos, dw_Size;
};



class mks_buffer {
public:

	CHAR_INFO*	c_pBuffer;
	COORD		dw_Size,dw_Cursor,dw_Pos;
	HANDLE		o_Output;
	SMALL_RECT	sm_Rect;

	BOOL __CC	vSetup(COORD, COORD, HANDLE);
	void __CC	vCleanup();

	BOOL __CC	vWriteOutput(c_LPSTR, DWORD, WORD);
	BOOL __CC	vWriteOutput( CHAR, WORD, BOOL);
	BOOL __CC	vReadInput(CSTR*, LPDWORD, WORD);
	BOOL __CC	vReadInput(CSTR*, LPDWORD, WORD,CHAR);
	BOOL __CC	vWriteBuffer();
	void __CC	vBreak();
	void __CC	vTab(SHORT);
	void __CC	vBufferClear();
	void __CC	vSetCursor(COORD);
	void __CC	vSetCursor(SHORT,SHORT);
};
#define _MKSR_ARGUMENT_TYPE void*
typedef _MKSR_ARGUMENT_TYPE ARGT;
//Maximum Arguments
#define _MKSR_ARGUMENTS 4
class mks_branch 
{
public:
	DWORD		dw_Key{0};
	BRANCH*		b_ArgumentBuffer[_MKSR_ARGUMENTS];

	ARGT		a_ArgumentBufferValue[_MKSR_ARGUMENTS];
	ARGT		a_ReturnBufferValue;
};

class mks_func
{
public:
	ARGT*		a_ArgumentBuffer;
	ARGT		a_ReturnBuffer;

	char		c_Arguments,c_Return;
	char*		c_Name;
	BOOL		(*f_Register)(SFUNC*, MKS*);
};
class mks 
{

public:
	HANDLE		o_HwndOutput{ 0 };
	HANDLE		o_HwndInput{ 0 };

	BOOL		b_Register[_MKSR_REGISTERS]={1,0,0,1,-1,FALSE,0,0};
	SFUNC		o_RegisterFunctions[_MKSR_REGFUNCTIONS];

	int			i_ScreenBufferCount{ 0 };
	BUFFER*		o_pScreenBuffer;

	BRANCH		b_pTree;


	CSTR		c_WinUsername,c_SoftwareDir;

	CSTR		c_InputRegister;
	CSTR		c_OutputRegister;

	DWORD		dw_KeyLength{ 0 };
	DWORD		dw_Key{ _MKSS_UNKNOW };
	DWORD		dw_Msg{ _MKSS_UNKNOW };

	
	void  __ST	vAssetWarmup();
	BOOL  __CC	vBuffeWarmup();
	int   __CC	vBufferReact(BUFFER_INFO, HANDLE);

	BOOL  __CC	vProcessInput();
	BOOL  __CC	vProcessFile();
	BOOL  __CC	vFetchBranch(BRANCH *);
	BOOL  __CC	vCreateBranch( DWORD,DWORD,BRANCH *);

	void  __CC	vConsoleInput();
	void  __CC	vConsoleOutput();
	void  __CC	vConsoleInputRequest(BOOL);
	
	BOOL  __CC	vGetFunctionId(DWORD);

	BOOL  __CC	vCleanup();
};


extern BOOL
vRegister_break(SFUNC*, MKS*);
extern BOOL	  
vRegister_login(SFUNC*, MKS*);
extern BOOL	   
vRegister_wkdir(SFUNC*, MKS*);
extern BOOL	  
vRegister_lttry(SFUNC*, MKS*);
extern BOOL
vRegister_clear(SFUNC*, MKS*);
extern BOOL
vRegister_input(SFUNC*, MKS*);
extern BOOL
vRegister_lstbf(SFUNC*, MKS*);
extern BOOL
vRegister_close(SFUNC*, MKS*);
extern BOOL
vRegister_regst(SFUNC*, MKS*);