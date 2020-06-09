#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"

TMSG __CC
mks::functions::mstsave(BRANCH * b_pBranch)
{
	switch (b_pBranch->a_Args[0].c_pStr[0])
	{
	case M_MODES_ALL:

		for (INT16 i_Index = 0; i_Index < mst_Openfiles.i_Files; i_Index++)
		{
			mst_Openfiles.mst_pStack[i_Index].Save();
		}
		return M_MESSAGES_FUNCTION_OKAY;
		break;
	case M_MODES_LOCAL:
	case M_KW_WILDCARD:

		if (mst_Openfiles.i_Files == 0)return M_MESSAGES_FUNCTION_ERROR;
		mst_Openfiles.GetFilestack()->Save();
		return M_MESSAGES_FUNCTION_OKAY;
		break;
	}

	return M_MESSAGES_FUNCTION_PARAMETER;
}