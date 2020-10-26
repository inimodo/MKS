#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"
#include"sf_sharedfunctions.h"

TMSG __CC
mks::functions::mstopen(BRANCH * b_pBranch)
{
	encryption::RequestMSTOpen(&(b_pBranch->a_Args[0]));
	DisplayFileStackContent(mst_Openfiles.i_Sellected);
	return M_MESSAGES_FUNCTION_LOAD_OKAY;
}