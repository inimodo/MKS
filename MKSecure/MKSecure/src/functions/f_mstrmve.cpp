#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include"..\header\s_functions.h"

TMSG __CC
mks::functions::mstrmve(BRANCH * b_pBranch)
{
	if (mst_Openfiles.i_Files != 0)
	{
		if (b_pBranch->a_Args[0].c_pStr[0] == M_KW_WILDCARD)
		{
			PlotHeader(b_pBranch);
			PlotMessage((char*) "Removed ",8);
			PlotMessage(mst_Openfiles.GetFilestack()->fs_Filestack.i_Files,3);

			PlotMessage((char*) " files from ",12);
			PlotMessage(mst_Openfiles.GetFilestack()->fp_Filepath.c_Filename.c_pStr, mst_Openfiles.GetFilestack()->fp_Filepath.c_Filename.s_Length);
			PlotBreak();

			mst_Openfiles.GetFilestack()->fs_Filestack.Popall();
			DisplayFileStackContent(mst_Openfiles.i_Sellected);
		}
		else if (b_pBranch->a_Args[0].c_pStr[0] == M_KW_SELLECT)
		{

			INT16 i_Search = b_pBranch->a_Args[0].ToInt(1);
			if (mst_Openfiles.GetFilestack()->fs_Filestack.i_Files > i_Search)
			{
				mst_Openfiles.GetFilestack()->fs_Filestack.Pop(i_Search);
			}else return M_MESSAGES_FUNCTION_PARAMETER;
		}
		DisplayFileStackContent(mst_Openfiles.i_Sellected);

	}
	else return M_MESSAGES_FUNCTION_LOAD_NOPNFILE;
	return M_MESSAGES_FUNCTION_OKAY;
}