#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"
#include"sf_sharedfunctions.h"


TMSG __CC
mks::functions::decrypt(BRANCH * b_pBranch)
{
	INT i_Keylength = b_pBranch->a_Args[1].s_Length;
	INT16 * i_pKey = encryption::TranslateKey(&b_pBranch->a_Args[1]);

	TMSG i_Status = encryption::RequestMSTOpen(&(b_pBranch->a_Args[0]));
	if (i_Status != M_MESSAGES_FILE_OKAY)
	{
		return i_Status;
	}

	PlotHeader(b_pBranch);
	PlotMessage((char *)"Decrypting ", 11);
	PlotMessage(
		mst_Openfiles.GetFilestack()->fs_Filestack.i_Files,
		3
	);
	PlotMessage((char *)" file(s) in ", 12);
	PlotMessage(
		mst_Openfiles.GetFilestack()->fp_Filepath.c_Filename.c_pStr,
		mst_Openfiles.GetFilestack()->fp_Filepath.c_Filename.s_Length
	);
	PlotBreak();

	QWORD i_Offset = 0;
	for (INT16 i_Fileindex = 0; i_Fileindex < mst_Openfiles.GetFilestack()->fs_Filestack.i_Files; i_Fileindex++)
	{
		PlotHeader(b_pBranch);
		PlotMessage(
			mst_Openfiles.GetFilestack()->fs_Filestack.fp_pStack[i_Fileindex].c_Filename.c_pStr,
			mst_Openfiles.GetFilestack()->fs_Filestack.fp_pStack[i_Fileindex].c_Filename.s_Length
		);
		PlotMessage((char *)" ... ", 5);

		i_Status = encryption::DecryptStream(&(mst_Openfiles.GetFilestack()->fs_Filestack.fp_pStack[i_Fileindex]), i_pKey, i_Keylength, &i_Offset);
		if (i_Status != M_MESSAGES_FILE_OKAY)return i_Status;

		PlotMessage((char *)" Finished!", 10);
		PlotBreak();
	}
	free(i_pKey);

	return M_MESSAGES_FUNCTION_OKAY;
}