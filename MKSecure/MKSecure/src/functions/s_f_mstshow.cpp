#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"

TMSG __CC
mks::functions::mstlist(BRANCH * b_pBranch)
{
	DisplayMstStackContent();
	return M_MESSAGES_FUNCTION_OKAY;
}