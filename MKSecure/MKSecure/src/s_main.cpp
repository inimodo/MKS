#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "header\s_functions.h"


INT32		mks::data::i_Status;
CSTR		mks::data::c_WinUsername, mks::data::c_SoftwareDir;
PATH		mks::data::p_WorkDirectory;
MSTSTACK	mks::data::mst_Openfiles;

INT32 main(INT32 i_Args,char ** c_ppArguments)
{
	if (Initialize())
	{	
		CSTR c_InputRegister(MAX_PATH);
		while (i_Status == M_STATUS_KEEPALIVE)
		{
			INT32 i_Msg,i_Length;
			UpdateStatus();
			WaitConsoleInput(&c_InputRegister,&i_Length);

			LOG(c_InputRegister.c_pStr);
			LOG(i_Length);
			LOG(c_InputRegister.s_Length);
			LOG(c_InputRegister.s_MemLen);
			STOP;
			if (c_InputRegister.c_pStr[0] == M_KW_MOVEPATH)
			{
				PathFeedback(FetchPath(&c_InputRegister));
				continue;
			}
			else
			{
				BRANCH  b_pTree;
				if (CreateBranch(&c_InputRegister,0, i_Length, &b_pTree) == FALSE)
				{
					ResolveError();
					continue;
				}
				FetchBranch(&b_pTree);
			}
		} 
	}
	return 0;
}