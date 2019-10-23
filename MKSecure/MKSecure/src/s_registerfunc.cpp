#include"s_header.h"

BOOL SFUNC::b_pStateBuffer[_MKSR_REGISTERS];

BOOL 
vRegister_break(SFUNC * k_Register,IOSYS * io_Sys)
{
	if (SFUNC::b_pStateBuffer[_MKSR_REGISTER_UNLOCKED] == TRUE) 
	{
		SFUNC::b_pStateBuffer[_MKSR_REGISTER_UNLOCKED] = FALSE;
		return TRUE;
	}
	return FALSE;
}
BOOL 
vRegister_login(SFUNC* k_Register, IOSYS* io_Sys)
{
	DWORD dw_TempSize = 0;
	ULLI ull_CN[2] = {0,0};
	char c_CN;
	for (char c_CNP = 0; c_CNP < 2; c_CNP++)
	{
		io_Sys->vWriteOutput(C_MKSS_K_LOGIN_CN, 7, _MKSC_COLOR_INPUT);
		for (char c_Index = 0; c_Index < _MKSS_BUFFERSIZE; c_Index++)
		{
			c_CN = _getch();
			if (c_CN == 13) 
			{
				if (c_Index <= 1) {
					ull_CN[c_CNP] = 0;
				}
				io_Sys->vBreak();
				break;
			}
			if (c_CN <= 57 && c_CN >= 48) 
			{			
				ull_CN[c_CNP] += (c_CN - 48) * vTenth(c_Index);
			}
			else 
			{
				if (c_Index <= 1) {
					ull_CN[c_CNP] = 0;
				}
				io_Sys->vBreak();
				break;
			}

			io_Sys->vWriteOutput(C_MKSS_K_LOGIN_HIDER, _MKSC_COLOR_INPUT,TRUE);

		}	
	}

	if (ull_CN[0] * ull_CN[1] == _MKS_REGKEY) 
	{
		SFUNC::b_pStateBuffer[_MKSR_REGISTER_UNLOCKED] = TRUE;
		return TRUE;
	}
	SFUNC::b_pStateBuffer[_MKSR_REGISTER_UNLOCKED] = FALSE;
	return FALSE;
}
BOOL 
vRegister_watch(SFUNC* k_Register, IOSYS* io_Sys)
{
	if (SFUNC::b_pStateBuffer[_MKSR_REGISTER_UNLOCKED] == TRUE) 
	{
		SFUNC::b_pStateBuffer[_MKSR_REGISTER_WATCHING] = TRUE;
		return TRUE;
	}
	return FALSE;
}
BOOL 
vRegister_lttry(SFUNC* k_Register, IOSYS* io_Sys)
{
	return FALSE;

}