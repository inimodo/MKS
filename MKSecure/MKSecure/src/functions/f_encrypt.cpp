#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"
#include"sf_sharedfunctions.h"

TMSG __CC
mks::functions::encrypt(BRANCH * b_pBranch)
{
	INT i_Keylength = b_pBranch->a_Args[1].s_Length;
	INT16 * i_pKey = encryption::TranslateKey(&b_pBranch->a_Args[1]);
	
	if (b_pBranch->a_Args[0].c_pStr[0] == M_KW_SELLECT)
	{
		INT16 i_Selected = StringToInt(b_pBranch->a_Args[0].c_pStr + 1, b_pBranch->a_Args[0].s_Length - 1);
		if (i_Selected >= 0 && i_Selected < mst_Openfiles.i_Files)
		{
			if (mst_Openfiles.mst_pStack[i_Selected].Load() == -1)
			{
				return M_MESSAGES_FUNCTION_LOAD_ERROR;
			}
			mst_Openfiles.i_Sellected = i_Selected;
		}
		else return M_MESSAGES_FUNCTION_PARAMETER;
	}
	else
	{
		CSTR * c_AbsoluteFilepath = p_WorkDirectory.BuildWithFile(&b_pBranch->a_Args[0]);
		c_AbsoluteFilepath->Append(M_FILE_STFILEEX);
		mst_Openfiles.Open(c_AbsoluteFilepath);
		if (mst_Openfiles.GetFilestack()->Load() == -1)
		{
			return M_MESSAGES_FUNCTION_LOAD_ERROR;
		}
		c_AbsoluteFilepath->Clean();
		free(c_AbsoluteFilepath);
	}

	PlotMessage((char *)"Fetching ", 9, FALSE);
	PlotMessage(
		mst_Openfiles.mst_pStack[mst_Openfiles.i_Sellected].fp_Filepath.c_Filename.c_pStr, 
		mst_Openfiles.mst_pStack[mst_Openfiles.i_Sellected].fp_Filepath.c_Filename.s_Length, 
		TRUE
	);

	PlotMessage((char *)"Loaded ", 7, FALSE);
	PlotMessage(
		mst_Openfiles.mst_pStack[mst_Openfiles.i_Sellected].fs_Filestack.i_Files,
		3,
		FALSE
	);
	PlotMessage((char *)" Files.", 7, TRUE);

	QWORD i_Offset = 0;
	for (INT16 i_Fileindex = 0; i_Fileindex < mst_Openfiles.mst_pStack[mst_Openfiles.i_Sellected].fs_Filestack.i_Files; i_Fileindex++)
	{
		PlotMessage((char *)"Process File", 8, FALSE);
		PlotMessage(
			mst_Openfiles.mst_pStack[mst_Openfiles.i_Sellected].fs_Filestack.fp_pStack[i_Fileindex].c_Filename.c_pStr,
			mst_Openfiles.mst_pStack[mst_Openfiles.i_Sellected].fs_Filestack.fp_pStack[i_Fileindex].c_Filename.s_Length,
			TRUE
		);
		LOG("INDEX: "<< mst_Openfiles.i_Sellected);
		STOP;
		INT16 i_Status = encryption::EncryptStream(&(mst_Openfiles.mst_pStack[mst_Openfiles.i_Sellected].fs_Filestack.fp_pStack[i_Fileindex]),100, i_pKey, i_Keylength,&i_Offset);
		if (i_Status != M_MESSAGES_FILE_OKAY)return i_Status;
	}

	return M_MESSAGES_FUNCTION_OKAY;
}