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
	this->b_Register[_MKSR_R_REGISTERBUFFER] = this->vBufferReact(_MKSD_REGISTERBUFFER, o_HwndOutput);
	this->b_Register[_MKSR_R_OUTPUTBUFFER] = this->vBufferReact(_MKSD_OUTPUTBUFFER, o_HwndOutput);
	
	return TRUE;
}
int   __CC	
mks::vBufferReact(BUFFER_INFO bi_Buffer,HANDLE o_Hwnd)
{
	++this->i_ScreenBufferCount;
	if (this->i_ScreenBufferCount == 0) 
	{
		this->o_pScreenBuffer = (BUFFER*)malloc( sizeof(BUFFER) * this->i_ScreenBufferCount);
	}
	else
	{
		 void*  v_Safe = realloc(this->o_pScreenBuffer, sizeof(BUFFER) * this->i_ScreenBufferCount);
		if (v_Safe != NULL)
		{
			this->o_pScreenBuffer = (BUFFER*)v_Safe;
		}
	}
	this->o_pScreenBuffer[this->i_ScreenBufferCount - 1].vSetup(bi_Buffer.dw_Pos, bi_Buffer.dw_Size, o_Hwnd, bi_Buffer.b_HasBorder);
	
	int i_Height, i_Width,i_Highest_X = 0, i_Highest_Y = 0;
	for (int i_Index = 0; i_Index < this->i_ScreenBufferCount; i_Index++)
	{
		i_Width = this->o_pScreenBuffer[i_Index].sm_Rect.Right + 1;
		i_Height = this->o_pScreenBuffer[i_Index].sm_Rect.Bottom + 1;
		if (i_Width > i_Highest_X) {
			i_Highest_X = i_Width;
		}
		if (i_Height > i_Highest_Y) {
			i_Highest_Y = i_Height;

		}

	}
	COORD dw_Size = { i_Highest_X,i_Highest_Y };
	SMALL_RECT sm_Rect = {0,0, i_Highest_X-1,i_Highest_Y-1};

	SetConsoleScreenBufferSize(this->o_HwndOutput, dw_Size);
	SetConsoleWindowInfo(this->o_HwndOutput, 1, &sm_Rect);

	return (this->i_ScreenBufferCount - 1);
}

void __CC
mks::vInputRoutine()
{
	if (this->i_Brachnes == 0)
	{
		this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vWriteOutput(C_TXT_INPUT_SUFIX, _MKSC_COLOR_CMD, TRUE);
		this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vWriteOutput((c_LPSTR)this->c_WinUsername, this->c_WinUsername.s_Length - 1, _MKSC_COLOR_NAME);
		this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vWriteOutput(C_TXT_INPUT_PREFIX, _MKSC_COLOR_CMD, TRUE);
		this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vReadInput(&this->c_InputRegister, &dw_KeyLength, _MKSC_COLOR_INPUT);
		this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vBreak();
	}
}

BOOL __CC
mks::vFetchInput()
{
	if (this->i_Brachnes == 0) 
	{
	
	}
	if (this->c_InputRegister.c_pStr[0] == C_TXT_FETCH_REQUEST) {

		if (this->vFetchFile() == FALSE) 
		{
			this->dw_Key = _MKSS_UNKNOW;
			this->dw_Msg = _MKSS_UNKNOWF;
		}
		else 
		{
			this->dw_Key = _MKSS_UNKNOW;
			this->dw_Msg = _MKSS_GOOD;;
		}
		return TRUE;
	}
	return TRUE;
}
BOOL __CC 
mks::vCreateBranch(BRANCH** b_ppBranch)
{
	return TRUE;
}
BOOL __CC 
mks::vFetchBranch(BRANCH * b_pBranch) 
{
	for (int i_ArgIndex = 0; i_ArgIndex < _MKSR_ARGUMENTS; i_ArgIndex++)
	{
		BOOL b_Done = TRUE;
		for (int i_Fetches = 0; i_Fetches < o_RegisterFunctions[this->dw_Key].c_Arguments; i_Fetches++)
		{
			if (b_pBranch->b_ArgumentBuffer[i_Fetches] != NULL) 
			{
				b_Done = FALSE;
			}
		}
		if (b_Done == FALSE) {
			for (int i_Fetches = 0; i_Fetches < o_RegisterFunctions[this->dw_Key].c_Arguments; i_Fetches++)
			{
				if (b_pBranch->b_ArgumentBuffer[i_Fetches] != NULL) {

					if (o_RegisterFunctions[b_pBranch->dw_Key].)
						this->vFetchBranch(b_pBranch->b_ArgumentBuffer[i_Fetches]);
				}


			}
		}

		if (o_RegisterFunctions[this->dw_Key].f_Register(&o_RegisterFunctions[this->dw_Key], this, b_pBranch->b_ArgumentBuffer[i_Fetches]) == TRUE) {
			this->dw_Msg = _MKSS_GOOD;
		}
		else {
			this->dw_Msg = _MKSS_FAILED;
		}
		
	}
	return TRUE;
}
BOOL __CC
mks::vFetchOutput()
{
	this->vFetchBranch(this->b_pTree);
	return TRUE;
}
BOOL __CC
mks::vFetchFile()
{
	CSTR s_Filepath(dw_KeyLength);
	for (ushort s_Cursor = 0, s_Stepdown = 0; s_Cursor < dw_KeyLength+1; s_Cursor++)
	{
		s_Filepath.c_pStr[s_Cursor] = this->c_InputRegister.c_pStr[s_Cursor+1];
	}
	s_Filepath.c_pStr[dw_KeyLength - 1] = C_TXT_ENDL;
	fopen_s(&this->f_pOpenFile,s_Filepath, "r");
	if (this->f_pOpenFile == NULL) return FALSE;
	s_Filepath.vClean();
	return TRUE;
}
void __CC
mks::vOutputRoutine()
{
	if (this->dw_Msg == _MKSS_GOOD)
	{
		this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vWriteOutput((c_LPSTR)C_MKSS_E_GOOD, _MKSS_MSGSIZE - 1, _MKSC_COLOR_GOOD);
	}
	if (this->dw_Msg == _MKSS_FAILED)
	{
		this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vWriteOutput((c_LPSTR)C_MKSS_E_ERROR, _MKSS_MSGSIZE - 1, _MKSC_COLOR_FAILED);
	}		
	if (this->dw_Msg == _MKSS_UNKNOWF)
	{
		this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vWriteOutput((c_LPSTR)C_MKSS_E_UNKNOWF, _MKSS_MSGSIZE - 1, _MKSC_COLOR_UNKNOW);
	}
	else if (this->dw_Msg == _MKSS_UNKNOW)
	{
		this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vWriteOutput((c_LPSTR)C_MKSS_E_UNKNOW, _MKSS_MSGSIZE - 1, _MKSC_COLOR_UNKNOW);
	}
	
	this->o_pScreenBuffer[this->b_Register[_MKSR_R_REGISTERBUFFER]].vBreak();
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
void __ST
mks::vAssetWarmup()
{
	this->o_RegisterFunctions[_MKSS_K_LOCK].f_Register = vRegister_break;
	this->o_RegisterFunctions[_MKSS_K_LOCK].c_Name = C_MKSS_K_BREAK;
	this->o_RegisterFunctions[_MKSS_K_LOCK].c_Arguments = 0;
	this->o_RegisterFunctions[_MKSS_K_LOCK].c_Return = FALSE;

	this->o_RegisterFunctions[_MKSS_K_LOGGIN].f_Register = vRegister_login;
	this->o_RegisterFunctions[_MKSS_K_LOGGIN].c_Name = C_MKSS_K_LOGIN;
	this->o_RegisterFunctions[_MKSS_K_LOGGIN].c_Arguments = 2;
	this->o_RegisterFunctions[_MKSS_K_LOGGIN].c_Return = FALSE;

	this->o_RegisterFunctions[_MKSS_K_LTTRY].f_Register = vRegister_lttry;
	this->o_RegisterFunctions[_MKSS_K_LTTRY].c_Name = C_MKSS_K_LTTRY;
	this->o_RegisterFunctions[_MKSS_K_LTTRY].c_Arguments = 0;
	this->o_RegisterFunctions[_MKSS_K_LTTRY].c_Return = FALSE;

	this->o_RegisterFunctions[_MKSS_K_WKDIR].f_Register = vRegister_wkdir;
	this->o_RegisterFunctions[_MKSS_K_WKDIR].c_Name = C_MKSS_K_WKDIR;
	this->o_RegisterFunctions[_MKSS_K_WKDIR].c_Arguments = 0;
	this->o_RegisterFunctions[_MKSS_K_WKDIR].c_Return = TRUE;

	this->o_RegisterFunctions[_MKSS_K_CLEAR].f_Register = vRegister_clear;
	this->o_RegisterFunctions[_MKSS_K_CLEAR].c_Name = C_MKSS_K_CLEAR;
	this->o_RegisterFunctions[_MKSS_K_CLEAR].c_Arguments = 1;
	this->o_RegisterFunctions[_MKSS_K_CLEAR].c_Return = FALSE;

	this->o_RegisterFunctions[_MKSS_K_INPUT].f_Register = vRegister_input;
	this->o_RegisterFunctions[_MKSS_K_INPUT].c_Name = C_MKSS_K_INPUT;
	this->o_RegisterFunctions[_MKSS_K_INPUT].c_Arguments = 1;
	this->o_RegisterFunctions[_MKSS_K_INPUT].c_Return = FALSE;

	this->o_RegisterFunctions[_MKSS_K_LSTBF].f_Register = vRegister_lstbf;
	this->o_RegisterFunctions[_MKSS_K_LSTBF].c_Name = C_MKSS_K_LSTBF;
	this->o_RegisterFunctions[_MKSS_K_LSTBF].c_Arguments = 0;
	this->o_RegisterFunctions[_MKSS_K_LSTBF].c_Return = TRUE;

	this->o_RegisterFunctions[_MKSS_K_CLOSE].f_Register = vRegister_close;
	this->o_RegisterFunctions[_MKSS_K_CLOSE].c_Name = C_MKSS_K_CLOSE;
	this->o_RegisterFunctions[_MKSS_K_CLOSE].c_Arguments = 1;
	this->o_RegisterFunctions[_MKSS_K_CLOSE].c_Return = FALSE;

	this->o_RegisterFunctions[_MKSS_K_REGST].f_Register = vRegister_regst;
	this->o_RegisterFunctions[_MKSS_K_REGST].c_Name = C_MKSS_K_REGST;
	this->o_RegisterFunctions[_MKSS_K_REGST].c_Arguments = 0;
	this->o_RegisterFunctions[_MKSS_K_REGST].c_Return = FALSE;
}