#include "s_header.h"


/*
BOOL __CC
mks::vCreateBranch(CSTR s_Text,BRANCH * b_pBranch)
{
	b_pBranch->dw_Key = vGetFunctionId(&s_Text);
	if (b_pBranch->dw_Key == _MKSS_UNKNOW)return FALSE;
	b_pBranch->a_ReturnBufferValue = NULL;
	for (int i_Index = 0; i_Index < _MKSR_ARGUMENTS; i_Index++)
	{
		b_pBranch->a_ArgumentBufferValue[i_Index] = NULL;
		b_pBranch->b_ArgumentBuffer[i_Index] = NULL;
	}
	if (o_RegisterFunctions[b_pBranch->dw_Key].c_Arguments == 0)return TRUE;
	for (int i_Start = _MKSS_REGFUNCTIONSIZE-1, i_Stop = 0,i_Arg = 0; i_Start < s_Text.s_Length || i_Arg < o_RegisterFunctions[b_pBranch->dw_Key].c_Arguments; i_Start++)
	{
		i_Stop = 0;
		if (s_Text.c_pStr[i_Start] == C_TXT_DO_REQUEST_START)
		{
			for (i_Stop = 1; i_Stop < s_Text.s_Length - i_Start; i_Stop++)
			{
				if (s_Text.c_pStr[i_Start + i_Stop] == C_TXT_DO_REQUEST_STOP)
				{
					break;
				}
			}
			CSTR s_Arg(i_Stop-1);
			for (int i_Index = 0; i_Index < s_Arg.s_Length; i_Index++)
			{
				s_Arg.c_pStr[i_Index] = s_Text.c_pStr[i_Start + i_Index + 1];
			}
			b_pBranch->b_ArgumentBuffer[i_Arg] = (BRANCH*)malloc(sizeof(BRANCH));
			if (b_pBranch->b_ArgumentBuffer[i_Arg] == NULL)
			{
				return FALSE;
			}
			vCreateBranch(s_Arg, b_pBranch->b_ArgumentBuffer[i_Arg]);
			s_Arg.vClean();
			i_Start += i_Stop;
			i_Arg++;
		}
		if (s_Text.c_pStr[i_Start] == C_TXT_REAL_REQUEST && s_Text.c_pStr[i_Start+1] != C_TXT_DO_REQUEST_START)
		{
			for (i_Stop = 1; i_Stop < (s_Text.s_Length - i_Start); i_Stop++)
			{
				if (s_Text.c_pStr[i_Start + i_Stop] <= 33)
				{
					break;
				}
			}
			i_Stop--;
			CSTR s_Arg(i_Stop);
			for (int i_Index = 0; i_Index < s_Arg.s_Length; i_Index++)
			{
				s_Arg.c_pStr[i_Index] = s_Text.c_pStr[i_Start + i_Index + 1];
			}
			b_pBranch->a_ArgumentBufferValue[i_Arg] = (ARGT)vStringToInt(s_Arg, s_Arg.s_Length);
			s_Arg.vClean();
			i_Start += i_Stop;
			i_Arg++;
		}
	}
	return TRUE;
}
*/