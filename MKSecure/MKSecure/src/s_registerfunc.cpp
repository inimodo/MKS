#include"s_header.h"

BOOL SFUNC::b_pStateBuffer[_MKSR_REGISTERS];

BOOL 
vRegister_break(void* k_Register, BUFFER* io_Sys)
{
	if (SFUNC::b_pStateBuffer[_MKSR_REGISTER_UNLOCKED] == TRUE) 
	{
		SFUNC::b_pStateBuffer[_MKSR_REGISTER_UNLOCKED] = FALSE;
		return TRUE;
	}
	return FALSE;
}
BOOL 
vRegister_login(void* k_Register, BUFFER* io_Sys)
{
	DWORD dw_TempSize = 0;
	ULLI ull_CN[2] = {0,0};
	char c_CN;

	if (ull_CN[0] * ull_CN[1] == _MKS_REGKEY) 
	{
		SFUNC::b_pStateBuffer[_MKSR_REGISTER_UNLOCKED] = TRUE;
		return TRUE;
	}
	SFUNC::b_pStateBuffer[_MKSR_REGISTER_UNLOCKED] = FALSE;
	return FALSE;
}
BOOL 
vRegister_watch(void* k_Register, BUFFER* io_Sys)
{
	if (SFUNC::b_pStateBuffer[_MKSR_REGISTER_UNLOCKED] == TRUE) 
	{
		SFUNC::b_pStateBuffer[_MKSR_REGISTER_WATCHING] = TRUE;
		return TRUE;
	}
	return FALSE;
}
BOOL 
vRegister_lttry(void* k_Register, BUFFER* io_Sys)
{
	return FALSE;

}