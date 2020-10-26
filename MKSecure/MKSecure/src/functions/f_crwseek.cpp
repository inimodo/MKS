#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"
TMSG __CC
mks::functions::crwseek(BRANCH * b_pBranch)
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

	do {
		if (o_FileData.nFileSizeLow != 0)
		{
			INT16 i_DotIndex = 0,i_BreakIndex,i_Matches = 0;
 			for (INT16 i_Index = 0; i_Index < MAX_PATH; i_Index++)
			{
				if (o_FileData.cFileName[i_Index] == '.')i_DotIndex = i_Index;
				if (o_FileData.cFileName[i_Index] == M_ENDL) 
				{
					i_BreakIndex = i_Index;
					break;
				}
			}
			for (INT16 i_Index = 0; i_Index < b_pBranch->a_Args[0].s_Length; i_Index++)
			{
				if (o_FileData.cFileName[i_Index+ i_DotIndex+1] == b_pBranch->a_Args[0].c_pStr[i_Index])i_Matches++;
				else break;
			}
			if (i_Matches == b_pBranch->a_Args[0].s_Length && i_Matches == i_BreakIndex-i_DotIndex-1) 
			{

				PlotHeader(b_pBranch);
				PlotMessage((char *)"Found file ", 11);
				PlotMessage(
					o_FileData.cFileName,
					i_BreakIndex
				);
				PlotBreak();

				mst_Openfiles.GetFilestack()->fs_Filestack.Push(c_Folder.c_pStr, o_FileData.cFileName);
				mst_Openfiles.GetFilestack()->fs_Filestack.fp_pStack[mst_Openfiles.GetFilestack()->fs_Filestack.i_Files - 1].o_Data = o_FileData;
			}
		}
	} while (FindNextFileA(o_Filehandle, &o_FileData) != 0);
	DisplayFileStackContent(mst_Openfiles.i_Sellected);

	return M_MESSAGES_FUNCTION_OKAY;
}