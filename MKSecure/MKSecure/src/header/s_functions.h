#pragma once


#include "s_includes.h"
#include "s_structs.h"

namespace mks 
{

	namespace data 
	{
		extern SFUNC		a_Assets_Functions[M_FUNC_COUNT];
		extern WORD			a_Assets_MColors[M_MESSAGES];
		extern CHAR			a_Assets_Messages[M_MESSAGES][M_MSGSIZE];
		extern BUFFER		a_Assets_Buffer[M_BUFFERS];

		extern INT32		i_Status;
		extern CSTR			c_WinUsername, c_SoftwareDir;
		extern PATH			p_WorkDirectory;
		extern MSTSTACK		mst_Openfiles;
	}
	namespace system 
	{
		extern BOOL __CC	Initialize();
		extern void __CC	FetchBranch(BRANCH *);
		extern BOOL __CC	CreateBranch(CSTR * c_InputRegister, INT32, INT32, BRANCH *);
		extern BOOL __CC	FetchPath(CSTR* c_InputRegister);
		extern BOOL __CC	GetFunctionId(CSTR* c_InputRegister, INT32 i_Offset);
		extern void __CC	InvokeFunctioncall(BRANCH * b_pBranch);
		extern void __CC	AddScreenBuffer(BUFFER_INFO bi_Buffer, INT16 i_Index);

	}
	namespace console 
	{
		extern void __CC	WaitConsoleInput(CSTR * c_InputRegister, INT32 * i_Length);
		extern void __CC	PathFeedback(INT16);
		extern void __CC	FuncFeedback(TMSG i_Msg, BRANCH * b_pBranch);
		extern void __CC	FuncHeader(BRANCH * b_pBranch);
		extern void __CC	FileInfo(INT16 i_Index, FSTACK * f_Stack, INT16 i_Buffer);
		extern void __CC	ResolveError();

		extern void __CC	PlotBreak();
		extern void __CC	PlotHeader(BRANCH * b_pBranch);
		extern void __CC	PlotMessage(char * c_pMessage, INT16 i_Length);
		extern void __CC	PlotMessage(INT16 i_Value, INT16 i_Digits);
		extern void __CC	PlotMessage(DWORD i_Value);

		extern void __CC	UpdateStatus();
		extern void __CC	FuncStackHeader(BRANCH *);
		extern void __CC	DisplayFileStackContent(INT16 i_File);
		extern void __CC	PlotTree(FSTACK * o_List);
		extern void __CC	DisplayMstStackContent();
		extern void __CC	MstFileInfo(INT16 i_Index, MSTSTACK * f_Stack, INT16 i_Buffer);
		extern void __CC	FileSize(DWORD i_Size, WORD i_Color, INT16 i_Buffer);
	}
	namespace functions 
	{
		extern TMSG __CC	crwpush(BRANCH*);
		extern TMSG __CC	crwpeek(BRANCH*);
		extern TMSG __CC	crwseek(BRANCH*);
		extern TMSG __CC	foclose(BRANCH*);
		extern TMSG __CC	bkeygen(BRANCH*);
		extern TMSG __CC	mstlist(BRANCH*);
		extern TMSG __CC	mstopen(BRANCH*);
		extern TMSG __CC	mstexit(BRANCH*);
		extern TMSG __CC	mstsave(BRANCH*);
		extern TMSG __CC	mstrmve(BRANCH*);
		extern TMSG __CC	encrypt(BRANCH*);
		extern TMSG __CC	decrypt(BRANCH*);
		extern TMSG __CC	packint(BRANCH*);
		extern TMSG __CC	packout(BRANCH*);
	}
}

#ifdef _MKS_REQ_SYSTEM_ACCESS 
using namespace mks::system;
#endif

#ifdef _MKS_REQ_FUNCTION_ACCESS 
using namespace mks::functions;
#endif

#ifdef _MKS_REQ_CONSOLE_ACCESS 
using namespace mks::console;
#endif

#ifdef _MKS_REQ_DATA_ACCESS 
using namespace mks::data;
#endif

