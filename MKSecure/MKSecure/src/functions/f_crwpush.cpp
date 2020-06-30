#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"
TMSG __CC
mks::functions::crwpush(BRANCH * b_pBranch)
{
	WIN32_FIND_DATA o_FileData;
	HANDLE o_Filehandle;
	CSTR c_Folder = CSTR();

	c_Folder.CopyAll(&c_SoftwareDir);
	c_Folder.c_pStr[c_Folder.s_Length] = M_WLCD;
	c_Folder.c_pStr[c_Folder.s_Length + 1] = M_ENDL;

	if (mst_Openfiles.i_Files == 0)return M_MESSAGES_FUNCTION_LOAD_NOPNFILE;
	o_Filehandle = FindFirstFileA(c_Folder.c_pStr, &o_FileData);
	if (o_Filehandle == INVALID_HANDLE_VALUE) 
	{
		return M_MESSAGES_FUNCTION_ERROR;
	}
	if (b_pBranch->a_Args[0].c_pStr[0] == M_KW_WILDCARD)
	{
		do {
			if (o_FileData.nFileSizeLow != 0)
			{
				mst_Openfiles.GetFilestack()->fs_Filestack.Push(c_Folder.c_pStr, o_FileData.cFileName);
				mst_Openfiles.GetFilestack()->fs_Filestack.fp_pStack[mst_Openfiles.GetFilestack()->fs_Filestack.i_Files - 1].o_Data = o_FileData;
			}
		} while (FindNextFileA(o_Filehandle, &o_FileData) != 0);
	}
	else if (b_pBranch->a_Args[0].c_pStr[0] == M_KW_SELLECT)
	{
		INT16 i_Search = b_pBranch->a_Args[0].ToInt(1),i_Index  = 0;
		do
		{
			if (i_Index == i_Search)
			{
				mst_Openfiles.GetFilestack()->fs_Filestack.Push(c_Folder.c_pStr, o_FileData.cFileName);
				mst_Openfiles.GetFilestack()->fs_Filestack.fp_pStack[mst_Openfiles.GetFilestack()->fs_Filestack.i_Files - 1].o_Data = o_FileData;
			}
			i_Index++;
		} while (FindNextFileA(o_Filehandle, &o_FileData) != 0);
	}

	else return M_MESSAGES_FUNCTION_LOAD_NOPNFILE;
	DisplayFileStackContent(mst_Openfiles.i_Sellected);
	FindClose(o_Filehandle);
	return M_MESSAGES_FUNCTION_OKAY;
}