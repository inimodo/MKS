#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"

TMSG __CC
mks::functions::mstopen(BRANCH * b_pBranch)
{
	if (b_pBranch->a_Args[0].c_pStr[0] == M_KW_SELLECT)
	{
		INT16 i_Selected = StringToInt(b_pBranch->a_Args[0].c_pStr+1, b_pBranch->a_Args[0].s_Length-1);
		if (i_Selected >= 0 && i_Selected < mst_Openfiles.i_Files)
		{
			if( mst_Openfiles.mst_pStack[i_Selected].Load() == -1)
			{
				return M_MESSAGES_FUNCTION_LOAD_ERROR;
			}
			mst_Openfiles.i_Sellected = i_Selected;
			DisplayFileStackContent(i_Selected);		
		}else return M_MESSAGES_FUNCTION_PARAMETER;
	}
	else 
	{
		CSTR * c_AbsoluteFilepath = p_WorkDirectory.BuildWithFile(&b_pBranch->a_Args[0]);
		c_AbsoluteFilepath->Append(M_FILE_STFILEEX);
		PlotMessage(c_AbsoluteFilepath->c_pStr, 0, TRUE);
		mst_Openfiles.Open(c_AbsoluteFilepath);
		if (mst_Openfiles.GetFilestack()->Load() == -1) 
		{
			return M_MESSAGES_FUNCTION_LOAD_ERROR;
		}
		DisplayFileStackContent(mst_Openfiles.i_Sellected);
		free(c_AbsoluteFilepath);
	}
	return M_MESSAGES_FUNCTION_LOAD_OKAY;
}