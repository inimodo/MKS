#include"s_header.h"

BOOL __CC
mks::vSetup()
{
	this->vAssetWarmup();

	this->c_LUser.vSet(UNLEN);
	this->c_LDir.vSet(MAX_PATH);
	this->c_RawKey.vSet(_MKSS_BUFFERSIZE);

	o_HwndOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	o_HwndInput = GetStdHandle(STD_INPUT_HANDLE);
	if (o_HwndOutput == NULL || o_HwndInput == NULL) {
		return FALSE;
	}
	if (GetUserNameA(this->c_LUser, (LPDWORD)& this->c_LUser.s_Length) == NULL)
	{
		return FALSE;
	}
	if (_getcwd(this->c_LDir, this->c_LDir.s_Length) == NULL)
	{
		return FALSE;
	}

	this->b_Buffers[_MKSW_BUFFERS_INPUT].vSetup({0,0}, { _MKSW_WIDTH ,_MKSW_HEIGHT }, o_HwndOutput,TRUE);
	this->b_Buffers[_MKSW_BUFFERS_OUTPUT].vSetup({ _MKSW_WIDTH,0}, { _MKSW_WIDTH ,_MKSW_HEIGHT }, o_HwndOutput,TRUE);

	return TRUE;
}
BOOL __CC
mks::vCatchloop()
{
	return TRUE;
}
BOOL __CC
mks::vLoop()
{
	vProcessKey();
	vProcessMsg();
	vProcessRawKey();
	return 1;
}
BOOL __CC
mks::vCleanup()
{
	c_LDir.vClean();
	c_LUser.vClean();
	c_RawKey.vClean();
	return 1;
}
void __CC 
mks::vProcessRawKey()
{
	this->dw_Key = _MKSS_UNKNOW;
	this->b_Buffers[_MKSW_BUFFERS_INPUT].vReadInput(&this->c_RawKey, & dw_KeyLength, _MKSC_COLOR_INPUT);
	this->b_Buffers[_MKSW_BUFFERS_INPUT].vBreak();

	this->b_Buffers[_MKSW_BUFFERS_OUTPUT].vWriteOutput((c_LPSTR)this->c_RawKey, dw_KeyLength, _MKSC_COLOR_NAME);

	if (this->dw_KeyLength != _MKSS_REGFUNCTIONSIZE-1) 
	{	
		return;
	}
	for (ushort s_KeyIndex = 0; s_KeyIndex < _MKSR_REGFUNCTIONS; s_KeyIndex++)
	{
		this->dw_KeyLength = 0;
		for (ushort s_Index = 0; s_Index < _MKSS_REGFUNCTIONSIZE; s_Index++)
		{
			if (c_RawKey.c_pStr[s_Index] == C_TXT_ENDL) {
				break;
			}
			if (c_RawKey.c_pStr[s_Index] == k_Funclist[s_KeyIndex].k_Key.c_Key[s_Index]) {				
				++this->dw_KeyLength;
			}		
		}
		if (this->dw_KeyLength == _MKSS_REGFUNCTIONSIZE-1) 
		{
			this->dw_Key = s_KeyIndex;
			return;
		}
	}
}
void __CC
mks::vProcessKey()
{
	this->dw_Msg = _MKSS_FAILED;
	if (this->dw_Key != _MKSS_UNKNOW && this->dw_Key != _MKSS_NONE)
	{
		if (k_Funclist[this->dw_Key].f_Register(&k_Funclist[this->dw_Key], this->b_Buffers) == TRUE)
		{
			this->dw_Msg = _MKSS_GOOD;
		}
		else
		{
			this->dw_Msg = _MKSS_FAILED;
		}
	}
}
void __CC
mks::vProcessMsg()
{
	if (this->dw_Key == _MKSS_UNKNOW)
	{
		this->b_Buffers[_MKSW_BUFFERS_INPUT].vWriteOutput((c_LPSTR)C_MKSS_K_UNKNOW, _MKSS_MSGSIZE - 1, _MKSC_COLOR_UNKNOW);
		this->b_Buffers[_MKSW_BUFFERS_INPUT].vBreak();

	}
	else if (this->dw_Key != _MKSS_NONE)
	{
		if (this->dw_Msg == _MKSS_FAILED)
		{
			this->b_Buffers[_MKSW_BUFFERS_INPUT].vWriteOutput( (c_LPSTR)k_Funclist[this->dw_Key].k_Key.c_Msg_Failed, _MKSS_MSGSIZE - 1, _MKSC_COLOR_FAILED);
		}
		else
			if (this->dw_Msg == _MKSS_GOOD)
			{
				this->b_Buffers[_MKSW_BUFFERS_INPUT].vWriteOutput( (c_LPSTR)k_Funclist[this->dw_Key].k_Key.c_Msg_Good, _MKSS_MSGSIZE - 1, _MKSC_COLOR_GOOD);
			}
		this->b_Buffers[_MKSW_BUFFERS_INPUT].vBreak();
	}

	this->b_Buffers[_MKSW_BUFFERS_INPUT].vWriteOutput(C_TXT_IN, _MKSC_COLOR_CMD,TRUE);
	this->b_Buffers[_MKSW_BUFFERS_INPUT].vWriteOutput((c_LPSTR)this->c_LUser, this->c_LUser.s_Length-1, _MKSC_COLOR_NAME);
	this->b_Buffers[_MKSW_BUFFERS_INPUT].vWriteOutput(C_TXT_PREFIX,  _MKSC_COLOR_CMD,TRUE);
}
void __ST
mks::vAssetWarmup()
{
	this->k_Funclist[_MKSS_K_LOCK].f_Register = vRegister_break;
	this->k_Funclist[_MKSS_K_LOCK].k_Key.c_Key = C_MKSS_K_LOCK;
	this->k_Funclist[_MKSS_K_LOCK].k_Key.c_Msg_Good = C_MKSS_K_LOCK_GOOD;
	this->k_Funclist[_MKSS_K_LOCK].k_Key.c_Msg_Failed = C_MKSS_K_LOCK_FAILED;

	this->k_Funclist[_MKSS_K_LOGGIN].f_Register = vRegister_login;
	this->k_Funclist[_MKSS_K_LOGGIN].k_Key.c_Key = C_MKSS_K_LOGIN;
	this->k_Funclist[_MKSS_K_LOGGIN].k_Key.c_Msg_Good = C_MKSS_K_LOGIN_GOOD;
	this->k_Funclist[_MKSS_K_LOGGIN].k_Key.c_Msg_Failed = C_MKSS_K_LOGIN_FAILED;

	this->k_Funclist[_MKSS_K_LTTRY].f_Register = vRegister_lttry;
	this->k_Funclist[_MKSS_K_LTTRY].k_Key.c_Key = C_MKSS_K_LTTRY;
	this->k_Funclist[_MKSS_K_LTTRY].k_Key.c_Msg_Good = C_MKSS_K_LTTRY_GOOD;
	this->k_Funclist[_MKSS_K_LTTRY].k_Key.c_Msg_Failed = C_MKSS_K_LTTRY_FAILED;

	this->k_Funclist[_MKSS_K_WATCH].f_Register = vRegister_watch;
	this->k_Funclist[_MKSS_K_WATCH].k_Key.c_Key = C_MKSS_K_WATCH;
	this->k_Funclist[_MKSS_K_WATCH].k_Key.c_Msg_Good = C_MKSS_K_WATCH_GOOD;
	this->k_Funclist[_MKSS_K_WATCH].k_Key.c_Msg_Failed = C_MKSS_K_WATCH_FAILED;
}