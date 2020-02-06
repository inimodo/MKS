#include"s_header.h"(SFUNC* k_Register, MKS* mks_Pref)

BOOL 
vRegister_break(SFUNC* k_Register, MKS* mks_Pref)
{
	if (mks_Pref->b_Register[_MKSR_R_UNLOCKED] == TRUE)
	{
		mks_Pref->b_Register[_MKSR_R_UNLOCKED] = FALSE;
		return TRUE;
	}
	return FALSE;
}
BOOL 
vRegister_login(SFUNC* k_Register, MKS* mks_Pref)
{

	if ((int)k_Register->a_ArgumentBuffer[0] * (int)k_Register->a_ArgumentBuffer[1] == _MKS_REGKEY)
	{
		mks_Pref->b_Register[_MKSR_R_UNLOCKED] = TRUE;
		return TRUE;
	}
	mks_Pref->b_Register[_MKSR_R_UNLOCKED] = FALSE;
	return FALSE;
}
BOOL 
vRegister_wkdir(SFUNC* k_Register, MKS* mks_Pref)
{
	if ((int)k_Register->a_ArgumentBuffer[0] >= 0 && (int)k_Register->a_ArgumentBuffer[0] < _MKSW_BUFFERS)
	{
		mks_Pref->b_Register[_MKSR_R_WATCHINGON] = (int)k_Register->a_ArgumentBuffer[0];
		return TRUE;
	}
	return FALSE;
}
BOOL 
vRegister_lttry(SFUNC* k_Register, MKS* mks_Pref)
{
	return FALSE;

}
BOOL
vRegister_clear(SFUNC* k_Register, MKS* mks_Pref)
{
	if ((int)k_Register->a_ArgumentBuffer[0] >= 0 && (int)k_Register->a_ArgumentBuffer[0] < _MKSW_BUFFERS)
	{
		mks_Pref->o_pScreenBuffer[(int)k_Register->a_ArgumentBuffer[0]].vBufferClear();
		return TRUE;
	}
	return FALSE;
}
BOOL
vRegister_input(SFUNC* k_Register, MKS* mks_Pref)
{
	if ((int)k_Register->a_ArgumentBuffer[0] >= 0 && (int)k_Register->a_ArgumentBuffer[0] < _MKSW_BUFFERS)
	{
		mks_Pref->b_Register[_MKSR_R_REGISTERBUFFER] = (int)k_Register->a_ArgumentBuffer[0];
		return TRUE;
	}
	return FALSE;
}
BOOL
vRegister_lstbf(SFUNC* k_Register, MKS* mks_Pref)
{
	k_Register->a_ReturnBuffer = (ARGT)173;//(ARGT)mks_Pref->b_Register[_MKSR_R_REGISTERBUFFER]+1;
	return mks_Pref->o_pScreenBuffer[mks_Pref->b_Register[_MKSR_R_OUTPUTBUFFER]].vWriteOutput(mks_Pref->b_Register[_MKSR_R_REGISTERBUFFER]+48, _MKSC_COLOR_OUTPUT,TRUE);
}
BOOL
vRegister_close(SFUNC* k_Register, MKS* mks_Pref)
{
	return mks_Pref->b_Register[_MKSR_R_KEEPALIVE] = 0;
}
BOOL
vRegister_regst(SFUNC* k_Register, MKS* mks_Pref)
{
	if ((int)k_Register->a_ArgumentBuffer[0] >= 0 && (int)k_Register->a_ArgumentBuffer[0] < _MKSR_REGISTERS)
	{
		mks_Pref->b_Register[(int)k_Register->a_ArgumentBuffer[0]] = (int)k_Register->a_ArgumentBuffer[1];
		return TRUE;
	}
	return FALSE;
}