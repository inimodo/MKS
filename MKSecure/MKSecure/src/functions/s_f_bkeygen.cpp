#define _MKS_REQ_FUNCTION_ACCESS
#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"

char EncodeInt(int i_Value) 
{
	if (i_Value <= 10) 
	{
		return '0' + i_Value-1;
	}
	if (i_Value <= 26+10)
	{
		return 'a' + i_Value-11;
	}
	if (i_Value <= 26+26+10)
	{
		return 'A' + i_Value - 26 - 11;
	}
	return 0;
}

int EncodeChar(char c_Char)
{
	if (c_Char <= '9' && c_Char >= '0')
		return c_Char - '0' + 1;
	if (c_Char <= 'z' && c_Char >= 'a')
		return c_Char - 'a' + 11;
	if (c_Char <= 'Z' && c_Char >= 'A')
		return c_Char - 'A' + ('z' - 'a' + 12);
	return 0;
}

TMSG __CC
mks::functions::bkeygen(BRANCH * b_pBranch)
{
	srand(time(0));
	int i_Layers =b_pBranch->a_Args[0].ToInt();
	b_pBranch->a_ArgBufReturn = CSTR(i_Layers*2);
	PlotMessage((char*)"B62: ", 5, FALSE);
	for (INT16 i_Index = 0; i_Index < i_Layers*2; i_Index++)
	{
		b_pBranch->a_ArgBufReturn.c_pStr[i_Index] = (char)EncodeInt(1 + rand() % 62);
		PlotMessage(b_pBranch->a_ArgBufReturn.c_pStr+ i_Index,1, FALSE);
	}
	PlotMessage((char*)NULL, 0, TRUE);

	b_pBranch->a_ArgBufReturn.c_pStr[i_Layers * 2] = M_ENDL;
	return M_MESSAGES_FUNCTION_OKAY;
}

