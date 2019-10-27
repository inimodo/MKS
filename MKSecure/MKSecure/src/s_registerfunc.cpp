#include"s_header.h"

BOOL SFUNC::b_pStateBuffer[_MKSR_REGISTERS];

CSTR SFUNC::c_ArgumentBuffer[_MKSR_ARGUMENTS];
DWORD SFUNC::dw_PasswordBuffer[_MKSR_ARGUMENTS];

BOOL __CC 
SFUNC::vValidate(int i_Count, BUFFER* b_Buffer,int i_Buffer)
{
	for (int i_Index = 0; i_Index < i_Count; i_Index++)
	{
		SFUNC::c_ArgumentBuffer[i_Index].vSet(_MKSS_BUFFERSIZE);
		SFUNC::c_ArgumentBuffer[i_Index].vClear();
		b_Buffer[i_Buffer].vWriteOutput(63, _MKSC_COLOR_CMD, TRUE);
		if (SFUNC::dw_PasswordBuffer[i_Index] == TRUE)
		{
			b_Buffer[i_Buffer].vReadInput(&SFUNC::c_ArgumentBuffer[i_Index], &SFUNC::dw_PasswordBuffer[i_Index], _MKSC_COLOR_INPUT, 42);
		}
		else
		{
			b_Buffer[i_Buffer].vReadInput(&SFUNC::c_ArgumentBuffer[i_Index], &SFUNC::dw_PasswordBuffer[i_Index], _MKSC_COLOR_INPUT);
		}
		b_Buffer[i_Buffer].vBreak();
	}
	return TRUE;
}
BOOL 
vRegister_break(void* k_Register, MKS* mks_Pref)
{
	if (SFUNC::b_pStateBuffer[_MKSR_REGISTER_UNLOCKED] == TRUE) 
	{
		SFUNC::b_pStateBuffer[_MKSR_REGISTER_UNLOCKED] = FALSE;
		return TRUE;
	}
	return FALSE;
}
BOOL 
vRegister_login(void* k_Register, MKS* mks_Pref)
{
	SFUNC::dw_PasswordBuffer[0] = TRUE;
	SFUNC::dw_PasswordBuffer[1] = TRUE;
	SFUNC::vValidate(2, mks_Pref->b_pBuffers, mks_Pref->i_RegisterBuffer);

	ULLI ull_CN[2];
	ull_CN[0] = vStringToUlli(SFUNC::c_ArgumentBuffer[0], SFUNC::dw_PasswordBuffer[0]);
	ull_CN[1] = vStringToUlli(SFUNC::c_ArgumentBuffer[1], SFUNC::dw_PasswordBuffer[1]);

	if (ull_CN[0] * ull_CN[1] == _MKS_REGKEY) 
	{
		SFUNC::b_pStateBuffer[_MKSR_REGISTER_UNLOCKED] = TRUE;
		return TRUE;
	}
	SFUNC::b_pStateBuffer[_MKSR_REGISTER_UNLOCKED] = FALSE;
	return FALSE;
}
BOOL 
vRegister_watch(void* k_Register, MKS* mks_Pref)
{
	if (SFUNC::b_pStateBuffer[_MKSR_REGISTER_UNLOCKED] == TRUE) 
	{
		SFUNC::b_pStateBuffer[_MKSR_REGISTER_WATCHING] = TRUE;
		return TRUE;
	}
	return FALSE;
}
BOOL 
vRegister_lttry(void* k_Register, MKS* mks_Pref)
{
	return FALSE;

}
BOOL
vRegister_clear(void* k_Register, MKS* mks_Pref)
{
	SFUNC::dw_PasswordBuffer[0] = FALSE;
	SFUNC::vValidate(1, mks_Pref->b_pBuffers, mks_Pref->i_RegisterBuffer);
	ULLI ulli_Buffer = vStringToUlli(SFUNC::c_ArgumentBuffer[0], SFUNC::dw_PasswordBuffer[0]);
	if (ulli_Buffer >= 0 && ulli_Buffer < _MKSW_BUFFERS) 
	{
		mks_Pref->b_pBuffers[ulli_Buffer].vBufferClear();
		return TRUE;
	}
	return FALSE;
}
BOOL
vRegister_input(void* k_Register, MKS* mks_Pref)
{
	SFUNC::dw_PasswordBuffer[0] = FALSE;
	SFUNC::vValidate(1, mks_Pref->b_pBuffers, mks_Pref->i_RegisterBuffer);
	ULLI ulli_Buffer = vStringToUlli(SFUNC::c_ArgumentBuffer[0], SFUNC::dw_PasswordBuffer[0]);
	if (ulli_Buffer >= 0 && ulli_Buffer < _MKSW_BUFFERS)
	{
		mks_Pref->i_RegisterBuffer = ulli_Buffer;
		return TRUE;
	}
	return FALSE;
}