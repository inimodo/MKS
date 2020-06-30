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
			PlotMessage((char*) "Removing ",10,FALSE);
			PlotMessage(mst_Openfiles.GetFilestack()->fs_Filestack.i_Files,3,FALSE);
			PlotMessage((char*) " Files from ",13,FALSE);
			PlotMessage(mst_Openfiles.GetFilestack()->fp_Filepath.c_Filename.c_pStr, mst_Openfiles.GetFilestack()->fp_Filepath.c_Filename.s_Length, FALSE);

			for (INT16 i_Index = 0; i_Index < mst_Openfiles.GetFilestack()->fs_Filestack.i_Files; i_Index++)
			{
				PlotMessage(
					mst_Openfiles.GetFilestack()->fs_Filestack.fp_pStack[i_Index].c_Filename.c_pStr, 
					mst_Openfiles.GetFilestack()->fs_Filestack.fp_pStack[i_Index].c_Filename.s_Length, 
					TRUE
				);
			}
			mst_Openfiles.GetFilestack()->fs_Filestack.Popall();
			DisplayFileStackContent(mst_Openfiles.i_Sellected);
		}
		else if (b_pBranch->a_Args[0].c_pStr[0] == M_KW_SELLECT)
		{

			INT16 i_Search = b_pBranch->a_Args[0].ToInt(1), i_Index = 0;
			
		}
	}
	else return M_MESSAGES_FUNCTION_LOAD_NOPNFILE;
	return M_MESSAGES_FUNCTION_OKAY;
}