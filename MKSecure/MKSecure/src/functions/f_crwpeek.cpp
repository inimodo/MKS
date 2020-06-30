#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"


TMSG __CC
mks::functions::crwpeek(BRANCH * b_pBranch)
{
	WIN32_FIND_DATA o_FileData;
	HANDLE o_Filehandle;
	CSTR c_Folder = CSTR();
	c_Folder.CopyAll(&c_SoftwareDir);
	c_Folder.c_pStr[c_Folder.s_Length]= M_WLCD;
	c_Folder.c_pStr[c_Folder.s_Length+1]= M_ENDL;

	o_Filehandle = FindFirstFileA(c_Folder.c_pStr, &o_FileData);
	if (o_Filehandle == INVALID_HANDLE_VALUE)return M_MESSAGES_FUNCTION_ERROR;

	FSTACK o_Stack;
	do {
		o_Stack.Push(c_Folder.c_pStr, o_FileData.cFileName);
		o_Stack.fp_pStack[o_Stack.i_Files - 1].o_Data = o_FileData;

	} while (FindNextFileA(o_Filehandle, &o_FileData) != 0);
	PlotTree(&o_Stack);
	FindClose(o_Filehandle);
	return M_MESSAGES_FUNCTION_OKAY;
}