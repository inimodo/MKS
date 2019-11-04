#include"s_header.h"


BOOL __CC
mks::vBuffeWarmup()
{
	this->c_WinUsername.vSet(UNLEN);
	this->c_SoftwareDir.vSet(MAX_PATH);
	this->c_InputRegister.vSet(_MKSS_BUFFERSIZE);

	o_HwndOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	o_HwndInput = GetStdHandle(STD_INPUT_HANDLE);
	if (o_HwndOutput == NULL || o_HwndInput == NULL) {
		return FALSE;
	}
	if (GetUserNameA(this->c_WinUsername, (LPDWORD)& this->c_WinUsername.s_Length) == NULL)
	{
		return FALSE;
	}
	if (_getcwd(this->c_SoftwareDir, this->c_SoftwareDir.s_Length) == NULL)
	{
		return FALSE;
	}
	this->o_pScreenBuffer = (BUFFER*)malloc(sizeof(BUFFER)*this->i_ScreenBufferCount);
	if (this->o_pScreenBuffer == NULL) 
	{
		return FALSE;
	}
	this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vSetup({0,0}, { _MKSW_WIDTH ,_MKSW_HEIGHT }, o_HwndOutput,TRUE);
	this->o_pScreenBuffer[this->b_Register[_MKSR_R_OUTPUTBUFFER]].vSetup({ _MKSW_WIDTH,0}, { _MKSW_WIDTH ,_MKSW_HEIGHT }, o_HwndOutput,TRUE);

	return TRUE;
}

void __ST
mks::vAssetWarmup()
{
	this->o_RegisterFunctions[_MKSS_K_LOCK].f_Register = vRegister_break;
	this->o_RegisterFunctions[_MKSS_K_LOCK].c_Name = C_MKSS_K_BREAK;

	this->o_RegisterFunctions[_MKSS_K_LOGGIN].f_Register = vRegister_login;
	this->o_RegisterFunctions[_MKSS_K_LOGGIN].c_Name = C_MKSS_K_LOGIN;

	this->o_RegisterFunctions[_MKSS_K_LTTRY].f_Register = vRegister_lttry;
	this->o_RegisterFunctions[_MKSS_K_LTTRY].c_Name = C_MKSS_K_LTTRY;

	this->o_RegisterFunctions[_MKSS_K_WATCH].f_Register = vRegister_watch;
	this->o_RegisterFunctions[_MKSS_K_WATCH].c_Name = C_MKSS_K_WATCH;

	this->o_RegisterFunctions[_MKSS_K_CLEAR].f_Register = vRegister_clear;
	this->o_RegisterFunctions[_MKSS_K_CLEAR].c_Name = C_MKSS_K_CLEAR;

	this->o_RegisterFunctions[_MKSS_K_INPUT].f_Register = vRegister_input;
	this->o_RegisterFunctions[_MKSS_K_INPUT].c_Name = C_MKSS_K_INPUT;

	this->o_RegisterFunctions[_MKSS_K_LSTBF].f_Register = vRegister_lstbf;
	this->o_RegisterFunctions[_MKSS_K_LSTBF].c_Name = C_MKSS_K_LSTBF;

	this->o_RegisterFunctions[_MKSS_K_CLOSE].f_Register = vRegister_close;
	this->o_RegisterFunctions[_MKSS_K_CLOSE].c_Name = C_MKSS_K_CLOSE;

	this->o_RegisterFunctions[_MKSS_K_REGST].f_Register = vRegister_regst;
	this->o_RegisterFunctions[_MKSS_K_REGST].c_Name = C_MKSS_K_REGST;
}
void __CC
mks::vInputRoutine()
{
	this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vWriteOutput(C_TXT_INPUT_SUFIX, _MKSC_COLOR_CMD, TRUE);
	this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vWriteOutput((c_LPSTR)this->c_WinUsername, this->c_WinUsername.s_Length - 1, _MKSC_COLOR_NAME);
	this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vWriteOutput(C_TXT_INPUT_PREFIX, _MKSC_COLOR_CMD, TRUE);
	this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vReadInput(&this->c_InputRegister, &dw_KeyLength, _MKSC_COLOR_INPUT);
	this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vBreak();
}

BOOL __CC
mks::vFetchInput()
{
	if (this->c_InputRegister.c_pStr[0] == C_TXT_FETCH_REQUEST) 
	{
		this->vFetchFile();
		return TRUE;
	}
	for (ushort s_Cursor = 0,s_Stepdown = 0; s_Cursor < dw_KeyLength; s_Cursor++)
	{

	}
	return TRUE;
}

BOOL __CC
mks::vFetchOutput()
{
	
	return TRUE;
}
BOOL __CC
mks::vFetchFile()
{

	return TRUE;
}
void __CC
mks::vOutputRoutine()
{
	this->dw_Msg = _MKSS_FAILED;
	if (this->dw_Key != _MKSS_UNKNOW)
	{
		if (o_RegisterFunctions[this->dw_Key].f_Register(&o_RegisterFunctions[this->dw_Key], this) == TRUE)
		{
			this->dw_Msg = _MKSS_GOOD;
			this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vWriteOutput((c_LPSTR)C_MKSS_E_GOOD, _MKSS_MSGSIZE - 1, _MKSC_COLOR_GOOD);
		}
		else
		{
			this->dw_Msg = _MKSS_FAILED;
			this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vWriteOutput((c_LPSTR)C_MKSS_E_ERROR, _MKSS_MSGSIZE - 1, _MKSC_COLOR_FAILED);

		}
		this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vBreak();

	}
	if (this->dw_Key == _MKSS_UNKNOW)
	{
		this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vWriteOutput((c_LPSTR)C_MKSS_E_UNKNOW, _MKSS_MSGSIZE - 1, _MKSC_COLOR_UNKNOW);
		this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vBreak();
	}
}

BOOL __CC
mks::vGetFunctionId(int i_Startindex)
{
	int i_TempSu = 0; 
	for (ushort s_KeyIndex = 0; s_KeyIndex < _MKSR_REGFUNCTIONS; s_KeyIndex++)
	{
		i_TempSu = 0;
		for (ushort s_Index = 0; s_Index < _MKSS_REGFUNCTIONSIZE; s_Index++)
		{
			if (c_InputRegister[i_Startindex+s_Index] == o_RegisterFunctions[s_KeyIndex].c_Name[s_Index]) {
				++i_TempSu;
			}		
		}
		if (i_TempSu == _MKSS_REGFUNCTIONSIZE-1)
		{
			return s_KeyIndex;
		}
	}
	return _MKSS_UNKNOW;
}

BOOL __CC
mks::vCleanup()
{
	this->c_SoftwareDir.vClean();
	this->c_WinUsername.vClean();
	this->c_InputRegister.vClean();
	free(this->o_pScreenBuffer);
	return 1;
}