#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"
#include"sf_sharedfunctions.h"

TMSG __CC
mks::functions::packint(BRANCH * b_pBranch)
{
	TMSG i_Status = encryption::RequestMSTOpen(&(b_pBranch->a_Args[0]));
	if (i_Status != M_MESSAGES_FILE_OKAY)
	{
		return i_Status;
	}

	CSTR * c_Filepath = mst_Openfiles.GetFilestack()->fp_Filepath.BuildWithFile(&(b_pBranch->a_Args[0]));
	c_Filepath->Append(M_FILE_PAFILEEX);

	INT16 i_DestinyFile = _sopen(c_Filepath->c_pStr, _O_BINARY | _O_RDWR | _O_CREAT, _SH_DENYRW, _S_IREAD | _S_IWRITE);
	if (i_DestinyFile == -1)return M_MESSAGES_FILE_FACCESS;

	if (_write(i_DestinyFile, &mst_Openfiles.GetFilestack()->fs_Filestack.i_Files, sizeof(INT16)) == 0)
	{
		return M_MESSAGES_FILE_FACCESS;
	}

	PlotHeader(b_pBranch);
	PlotMessage((char *)"Packing up ", 11);
	PlotMessage(
		mst_Openfiles.GetFilestack()->fs_Filestack.i_Files,
		3
	);
	PlotMessage((char *)" file(s).", 9);

	PlotBreak();

	for (INT16 i_Fileindex = 0; i_Fileindex < mst_Openfiles.GetFilestack()->fs_Filestack.i_Files; i_Fileindex++)
	{
		FPATH * fp_pFilepath = &(mst_Openfiles.GetFilestack()->fs_Filestack.fp_pStack[i_Fileindex]);
		CSTR * c_Filepath = fp_pFilepath->BuildWithFile(&fp_pFilepath->c_Filename);

		PlotHeader(b_pBranch);
		PlotMessage(
			fp_pFilepath->c_Filename.c_pStr,
			fp_pFilepath->c_Filename.s_Length
		);
		PlotMessage((char *)" (", 2);
		PlotMessage(fp_pFilepath->o_Data.nFileSizeLow);
		PlotMessage((char *)") ... ", 6);

		INT16 i_SourceFile = _sopen(c_Filepath->c_pStr, _O_BINARY | _O_RDWR | _O_CREAT, _SH_DENYRW, _S_IREAD | _S_IWRITE);
		if (i_SourceFile == -1)
		{
			return M_MESSAGES_FILE_FACCESS;
		}

		if (_write(i_DestinyFile, &fp_pFilepath->o_Data, sizeof(WIN32_FIND_DATA)) == 0)
		{
			return M_MESSAGES_FILE_FACCESS;
		}
		if (_write(i_DestinyFile, &fp_pFilepath->c_Filename.s_Length, sizeof(INT16)) == 0)
		{
			return M_MESSAGES_FILE_FACCESS;
		}
		if (_write(i_DestinyFile, fp_pFilepath->c_Filename.c_pStr, fp_pFilepath->c_Filename.s_Length) == 0)
		{
			return M_MESSAGES_FILE_FACCESS;
		}


		DWORD i_CheckBytes = 0;
		char * c_Buffer = (char*)malloc(M_FILEBUFFERSIZE);
		if (c_Buffer == NULL)
		{
			return M_MESSAGES_FUNCTION_ERROR;
		}


		while (!_eof(i_SourceFile))
		{
			i_CheckBytes = _read(i_SourceFile, c_Buffer, M_FILEBUFFERSIZE);
			if (i_CheckBytes == -1)
			{
				_close(i_SourceFile);
				_close(i_DestinyFile);
				free(c_Buffer);

				return M_MESSAGES_FILE_READF;
			}
			if (_write(i_DestinyFile, c_Buffer, i_CheckBytes) == -1)
			{
				_close(i_SourceFile);
				_close(i_DestinyFile);
				free(c_Buffer);

				return M_MESSAGES_FILE_WRITEF;
			}
		}
		_close(i_SourceFile);
		PlotMessage((char *)"Appended!", 9);
		PlotBreak();
	}

	_close(i_DestinyFile);
	return M_MESSAGES_FUNCTION_OKAY;
}