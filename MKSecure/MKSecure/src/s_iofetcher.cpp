#include"s_header.h"

BOOL __CC
mks::vProcessInput()
{
	if (this->c_InputRegister.c_pStr[0] == C_TXT_FETCH_REQUEST) {

		if (this->vProcessFile() == FALSE)
		{
			this->dw_Key = _MKSS_UNKNOW;
			this->dw_Msg = _MKSS_UNKNOWF;
		}
		else
		{
			this->dw_Key = _MKSS_UNKNOW;
			this->dw_Msg = _MKSS_GOOD;
		}
	}
	else {
		if (this->vCreateBranch(0, this->dw_KeyLength, &this->b_pTree) == FALSE)
		{
			this->dw_Msg = _MKSS_UNKNOW;
			return FALSE;
		}

		if (this->vFetchBranch(&b_pTree) == FALSE)
		{
			this->dw_Msg = _MKSS_FAILED;
			return FALSE;
		}

		this->dw_Msg = _MKSS_GOOD;
	}
	return TRUE;
}
BOOL __CC 
mks::vCreateBranch(DWORD dw_Start,DWORD dw_Stop,BRANCH * b_pBranch)
{
	b_pBranch->dw_Key = vGetFunctionId(dw_Start);
	this->dw_Key = b_pBranch->dw_Key;
	if (b_pBranch->dw_Key == _MKSS_UNKNOW)return FALSE;
	b_pBranch->a_ReturnBufferValue = NULL;
	for (int i_Index = 0; i_Index < _MKSR_ARGUMENTS; i_Index++)
	{
		b_pBranch->a_ArgumentBufferValue[i_Index] = NULL;
		b_pBranch->b_ArgumentBuffer[i_Index] = NULL;
	}
	if (o_RegisterFunctions[b_pBranch->dw_Key].c_Arguments == 0)return TRUE;
	for (int i_Start = _MKSS_REGFUNCTIONSIZE + dw_Start-1, i_Stop = 0,i_Arg = 0; i_Start < dw_Start+dw_Stop || i_Arg < o_RegisterFunctions[b_pBranch->dw_Key].c_Arguments; i_Start++)
	{		
		i_Stop = 0;
		if (this->c_InputRegister.c_pStr[i_Start] == C_TXT_REAL_REQUEST) 
		{
			i_Start++;

			if (this->c_InputRegister.c_pStr[i_Start] == C_TXT_DO_REQUEST_START)
			{
				for (i_Stop = 1; i_Stop < this->c_InputRegister.s_Length - i_Start; i_Stop++)
				{
					if (this->c_InputRegister.c_pStr[i_Start + i_Stop] == C_TXT_DO_REQUEST_STOP)
					{
						break;
					}
				}
				b_pBranch->b_ArgumentBuffer[i_Arg] = (BRANCH*)malloc(sizeof(BRANCH));
				if (b_pBranch->b_ArgumentBuffer[i_Arg] == NULL)
				{
					return FALSE;
				}

				vCreateBranch(i_Start + 1, i_Stop, b_pBranch->b_ArgumentBuffer[i_Arg]);
				i_Start += i_Stop;
				i_Arg++;
				continue;
			}
			if (this->c_InputRegister.c_pStr[i_Start] != C_TXT_DO_REQUEST_START)
			{
				if (this->c_InputRegister.c_pStr[i_Start] == C_TXT_INFO_SUFIX)
				{
					this->vConsoleInputRequest(FALSE);
					b_pBranch->a_ArgumentBufferValue[i_Arg] = (ARGT)vStringToInt(this->c_OutputRegister, this->dw_KeyLength, 0);		
				}
				else 
				{
					for (i_Stop = 1; i_Stop < (this->c_InputRegister.s_Length - i_Start); i_Stop++)
					{
						if (this->c_InputRegister.c_pStr[i_Start + i_Stop] <= 33)
						{
							break;
						}
					}
					b_pBranch->a_ArgumentBufferValue[i_Arg] = (ARGT)vStringToInt(this->c_InputRegister, i_Stop, i_Start);
				}
				i_Start += i_Stop-1;

				i_Arg++;
				continue;

			}
		}
	}
	return TRUE;
}
BOOL __CC
mks::vGetFunctionId(DWORD dw_Offset)
{
	int i_TempSu = 0;
	for (ushort s_KeyIndex = 0; s_KeyIndex < _MKSR_REGFUNCTIONS; s_KeyIndex++)
	{
		i_TempSu = 0;
		for (ushort s_Index = 0; s_Index < _MKSS_REGFUNCTIONSIZE; s_Index++)
		{
			if (this->c_InputRegister.c_pStr[s_Index+ dw_Offset] == this->o_RegisterFunctions[s_KeyIndex].c_Name[s_Index]) {
				++i_TempSu;
			}
		}
		if (i_TempSu == _MKSS_REGFUNCTIONSIZE - 1)
		{
			return s_KeyIndex;
		}
	}
	return _MKSS_UNKNOW;
}

BOOL __CC 
mks::vFetchBranch(BRANCH * b_pBranch) 
{
	if ((int)b_pBranch->dw_Key == _MKSS_UNKNOW) 
	{
		return FALSE;
	
	}
	BOOL b_Done = TRUE;
	for (int i_Fetches = 0; i_Fetches < _MKSR_ARGUMENTS; i_Fetches++)
	{	
		if (b_pBranch->b_ArgumentBuffer[i_Fetches] != NULL) b_Done = FALSE;
	}
	if (b_Done == FALSE) 
	{
		for (int i_Fetches = 0; i_Fetches < _MKSR_ARGUMENTS; i_Fetches++)
		{
			if (b_pBranch->b_ArgumentBuffer[i_Fetches] != NULL) {

				if (this->vFetchBranch(b_pBranch->b_ArgumentBuffer[i_Fetches]) == FALSE)
				{
					return FALSE;
				}
				else
				{
					b_pBranch->a_ArgumentBufferValue[i_Fetches] = b_pBranch->b_ArgumentBuffer[i_Fetches]->a_ReturnBufferValue;
					free(b_pBranch->b_ArgumentBuffer[i_Fetches]);
					b_pBranch->b_ArgumentBuffer[i_Fetches] = NULL;
				}
			}
		}
	}


	this->o_RegisterFunctions[b_pBranch->dw_Key].a_ArgumentBuffer = b_pBranch->a_ArgumentBufferValue;

	if (o_RegisterFunctions[b_pBranch->dw_Key].f_Register(&o_RegisterFunctions[b_pBranch->dw_Key], this) == FALSE) 
	{
		this->dw_Msg = _MKSS_FAILED;
		this->dw_Key = b_pBranch->dw_Key;
		this->vConsoleOutput();
		return FALSE;
	}

	b_pBranch->a_ReturnBufferValue = this->o_RegisterFunctions[b_pBranch->dw_Key].a_ReturnBuffer;
	this->dw_Msg = _MKSS_GOOD;
	this->dw_Key = b_pBranch->dw_Key;
	this->vConsoleOutput();

	return TRUE;
}

BOOL __CC
mks::vProcessFile()
{
	FILE* f_pOpenFile;
	CSTR s_Filepath(dw_KeyLength);
	for (ushort s_Cursor = 0, s_Stepdown = 0; s_Cursor < dw_KeyLength+1; s_Cursor++)
	{
		s_Filepath.c_pStr[s_Cursor] = this->c_InputRegister.c_pStr[s_Cursor+1];
	}
	s_Filepath.c_pStr[dw_KeyLength - 1] = C_TXT_ENDL;

	fopen_s(&f_pOpenFile,s_Filepath, "r");
	if (f_pOpenFile == NULL)
	{
		return FALSE;
	}
	fseek(f_pOpenFile, 0L, SEEK_SET);

	while(fgets( this->c_InputRegister.c_pStr, this->c_InputRegister.s_Length, f_pOpenFile))
	{
		this->dw_KeyLength = vTermLength(this->c_InputRegister.c_pStr);		
		this->vProcessInput();
		LOG("L: "<< this->dw_KeyLength);
		system("pause");
	}
	fclose(f_pOpenFile);
	s_Filepath.vClean();
	return TRUE;
}


