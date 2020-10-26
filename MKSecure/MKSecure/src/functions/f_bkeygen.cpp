#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"
#include "sf_sharedfunctions.h"

TMSG __CC
mks::functions::bkeygen(BRANCH * b_pBranch)
{
	srand(time(0));
	int i_Layers =b_pBranch->a_Args[0].ToInt();
	b_pBranch->a_ArgBufReturn.Set(i_Layers+1);

	PlotHeader(b_pBranch);
	PlotMessage((char*)"B62: ", 5);

	for (INT16 i_Index = 0; i_Index < i_Layers; i_Index++)
	{
		b_pBranch->a_ArgBufReturn.c_pStr[i_Index] = (char)encryption::TranslateInt(1 + rand() % 62);
		PlotMessage(b_pBranch->a_ArgBufReturn.c_pStr+i_Index,1);
	}
	PlotBreak();

	b_pBranch->a_ArgBufReturn.c_pStr[i_Layers ] = M_ENDL;
	return M_MESSAGES_FUNCTION_OKAY;
}

