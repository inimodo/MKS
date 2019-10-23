#include"s_header.h"

void __ST
cIOSystem::vSetupBuffer()
{
	this->c_LUser.vSet(UNLEN);
	this->c_LDir.vSet(MAX_PATH);
	this->c_RawKey.vSet(_MKSS_BUFFERSIZE);
}
void __CC 
cIOSystem::vProcessRawKey()
{
	this->dw_Key = _MKSS_UNKNOW;
	this->vReadInput(&this->c_RawKey, & dw_KeyLength);
	this->vBreak();
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
				break;;
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
cIOSystem::vProcessKey()
{
	this->dw_Msg = _MKSS_FAILED;
	if (this->dw_Key != _MKSS_UNKNOW && this->dw_Key != _MKSS_NONE)
	{
		if (k_Funclist[this->dw_Key].f_Register(&k_Funclist[this->dw_Key],this) == TRUE) 
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
cIOSystem::vProcessMsg()
{
	if (this->dw_Key == _MKSS_UNKNOW)
	{
		this->vWriteOutput((c_LPSTR)C_MKSS_K_UNKNOW, _MKSS_MSGSIZE - 1, _MKSC_COLOR_UNKNOW);
	}
	else if (this->dw_Key != _MKSS_NONE)
	{
		if (this->dw_Msg == _MKSS_FAILED)
		{
			this->vWriteOutput((c_LPSTR)k_Funclist[this->dw_Key].k_Key.c_Msg_Failed, _MKSS_MSGSIZE - 1, _MKSC_COLOR_FAILED);
		}
		else
			if (this->dw_Msg == _MKSS_GOOD)
			{
				this->vWriteOutput((c_LPSTR)k_Funclist[this->dw_Key].k_Key.c_Msg_Good, _MKSS_MSGSIZE - 1, _MKSC_COLOR_GOOD);
			}
	}

	this->vBreak();
	this->vWriteOutput((c_LPSTR)C_TXT_IN, _MKSS_KEYS-1, _MKSC_COLOR_CMD);
	this->vWriteOutput((c_LPSTR)this->c_LUser, this->c_LUser.s_Length, _MKSC_COLOR_NAME);
	this->vWriteOutput((c_LPSTR)C_TXT_PREFIX, _MKSS_KEYS, _MKSC_COLOR_CMD);
}
