#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"

TMSG __CC
mks::functions::foclose(BRANCH * b_pBranch)
{
	i_Status = M_STATUS_QUIT;
	return M_MESSAGES_FUNCTION_OKAY;
}
