#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"
#include"sf_sharedfunctions.h"


TMSG __CC
mks::functions::packout(BRANCH * b_pBranch)
{
	TMSG i_Status;
	if (b_pBranch->a_Args[1].c_pStr[0] == M_KW_WILDCARD)
	{
		i_Status = encryption::RequestMSTOpen(&(b_pBranch->a_Args[0]));
	}
	else
	{
		 i_Status = encryption::RequestMSTOpen(&(b_pBranch->a_Args[1]));
	}
	if (i_Status != M_MESSAGES_FILE_OKAY)
	{
		return i_Status;
	}

	CSTR * c_Filepath = mst_Openfiles.GetFilestack()->fp_Filepath.BuildWithFile(&(b_pBranch->a_Args[0]));
	c_Filepath->Append(M_FILE_PAFILEEX);

	INT16 i_SourceFile = _sopen(c_Filepath->c_pStr, _O_BINARY | _O_RDWR | _O_CREAT, _SH_DENYRW, _S_IREAD | _S_IWRITE);
	if (i_SourceFile == -1)return M_MESSAGES_FILE_FACCESS;

	INT16 i_Files;
	if (_read(i_SourceFile, &i_Files, sizeof(INT16)) == 0)
	{
		return M_MESSAGES_FILE_FACCESS;
	}
	
	PlotHeader(b_pBranch);
	PlotMessage((char *)"Packing out ", 12);
	PlotMessage(i_Files,3);
	PlotMessage((char *)" file(s).", 12);
	PlotBreak();

	for (INT16 i_Fileindex = 0; i_Fileindex < i_Files; i_Fileindex++)
	{

		PlotHeader(b_pBranch);

		WIN32_FIND_DATA o_Data ;
		if (_read(i_SourceFile, &o_Data, sizeof(WIN32_FIND_DATA)) == 0)
		{
			return M_MESSAGES_FILE_FACCESS;
		}
		PlotMessage((char *)"Got a ", 6);
		PlotMessage(o_Data.nFileSizeLow);
		PlotMessage((char *)" file ", 6);

		CSTR c_Filename = CSTR();
		INT16 i_FilenameSize = 0;
		if (_read(i_SourceFile, &i_FilenameSize, sizeof(INT16)) == 0)
		{
			return M_MESSAGES_FILE_FACCESS;
		}
		c_Filename.Set(i_FilenameSize);
		if (_read(i_SourceFile, c_Filename.c_pStr, i_FilenameSize) == 0)
		{
			return M_MESSAGES_FILE_FACCESS;
		}

		PlotMessage(
			c_Filename.c_pStr,
			c_Filename.s_Length
		);

		CSTR * c_AbsoluteFilepath = p_WorkDirectory.BuildWithFile(&c_Filename);
		INT16 i_DestinyFile = _sopen(c_AbsoluteFilepath->c_pStr, _O_BINARY | _O_RDWR | _O_CREAT, _SH_DENYRW, _S_IREAD | _S_IWRITE);
		if (i_DestinyFile == -1)
		{
			return M_MESSAGES_FILE_FACCESS;
		}
		c_Filename.Clean();

		DWORD i_CheckBytes = 0;
		char * c_Buffer = (char*)malloc(M_FILEBUFFERSIZE);
		if (c_Buffer == NULL)
		{
			return M_MESSAGES_FUNCTION_ERROR;
		}

		for (DWORD i_Index = 0; i_Index < (INT16)(o_Data.nFileSizeLow/ M_FILEBUFFERSIZE); i_Index++)
		{
			i_CheckBytes = _read(i_SourceFile, c_Buffer, M_FILEBUFFERSIZE);
			if (i_CheckBytes == -1)
			{
				return M_MESSAGES_FILE_READF;
			}
			if (_write(i_DestinyFile, c_Buffer, i_CheckBytes) == -1)
			{
				return M_MESSAGES_FILE_WRITEF;
			}
		}
		i_CheckBytes = _read(i_SourceFile, c_Buffer, o_Data.nFileSizeLow%M_FILEBUFFERSIZE);
		if (i_CheckBytes == -1)
		{
			return M_MESSAGES_FILE_READF;
		}
		if (_write(i_DestinyFile, c_Buffer, i_CheckBytes) == -1)
		{
			return M_MESSAGES_FILE_WRITEF;
		}

		encryption::AddFileToMST(c_AbsoluteFilepath, &o_Data);
		mst_Openfiles.GetFilestack()->Save();
		DisplayFileStackContent(mst_Openfiles.i_Sellected);


		_close(i_DestinyFile);
		PlotMessage((char *)" Saved!", 7);
		PlotBreak();
	}
	_close(i_SourceFile);
	return M_MESSAGES_FUNCTION_OKAY;
}