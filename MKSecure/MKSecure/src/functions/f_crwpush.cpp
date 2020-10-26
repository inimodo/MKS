#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"
#include"sf_sharedfunctions.h"
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
		PlotHeader(b_pBranch);
		PlotMessage((char *)"Files in Folder are added!", 27);
		PlotBreak();
		do {
			if (o_FileData.nFileSizeLow != 0)
			{
				encryption::AddFileToMST(&c_Folder, &o_FileData);
			}
		} while (FindNextFileA(o_Filehandle, &o_FileData) != 0);
	}
	else if (b_pBranch->a_Args[0].c_pStr[0] == M_KW_SELLECT)
	{
		INT16 i_Search = b_pBranch->a_Args[0].ToInt(1);
		for (INT16 i_FileIndex = 0; i_FileIndex != i_Search; i_FileIndex++)
		{
			if (FindNextFileA(o_Filehandle, &o_FileData) == 0) 
			{
				FindClose(o_Filehandle);
				return M_MESSAGES_FILE_UNKNOWN;
			}
		} 
	}
	else 
	{
		for (INT16 i_FileIndex = 0; ; i_FileIndex++)
		{	
			INT16 i_Matches = 0;
			for (INT16 i_Index = 0; i_Index < b_pBranch->a_Args[0].s_Length; i_Index++)
			{
				if (b_pBranch->a_Args[0].c_pStr[i_Index] != o_FileData.cFileName[i_Index])
				{
					i_Matches = 0;
					break;
				}
				else
				{
					i_Matches++;
				}
			}
			if (i_Matches == b_pBranch->a_Args[0].s_Length) 
			{
				break;
			}	
			if (FindNextFileA(o_Filehandle, &o_FileData) == 0)
			{
				FindClose(o_Filehandle);
				return M_MESSAGES_FILE_UNKNOWN;
			}
		} 
	}

	PlotHeader(b_pBranch);
	PlotMessage((char *)"Pushed ", 7);
	PlotMessage(
		o_FileData.cFileName,
		0
	);
	PlotBreak();

	encryption::AddFileToMST(&c_Folder,&o_FileData);


	DisplayFileStackContent(mst_Openfiles.i_Sellected);
	FindClose(o_Filehandle);
	return M_MESSAGES_FUNCTION_OKAY;
}