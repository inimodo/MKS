#include "s_header.h"

mks_str::mks_str(c_LPSTR c_pInput)
	: s_Length(0)
{this->vSet(c_pInput);}

mks_str::mks_str()
	: s_Length(0), c_pStr(0)
{}
mks_str::mks_str(ushort s_Length)
	: s_Length(s_Length), c_pStr(0)
{
	this->vSet(s_Length);
}
void __CC
mks_str::vSet(ushort s_Length)
{
	this->vClean();
	this->c_pStr = (LPSTR)malloc(s_Length+1);
	this->s_Length = s_Length;
}
void __CC
mks_str::vSet(c_LPSTR c_pText)
{
	this->vClean();
	this->s_Length = vTermLength(c_pText);
	this->c_pStr = (LPSTR)malloc(s_Length+1);
	if (this->c_pStr != NULL) {
		for (ushort i_StrPos = 0; i_StrPos < s_Length; i_StrPos++)
		{
			this->c_pStr[i_StrPos] = c_pText[i_StrPos];
		}
		this->c_pStr[s_Length] = C_TXT_ENDL;
	}
}
void __CC
mks_str::vAppend(CSTR c_pAdd)
{
	if (c_pAdd.s_Length == 0)return;
	void* v_Codex = realloc(this->c_pStr, this->s_Length + c_pAdd.s_Length);
	if (v_Codex != NULL) {
		this->c_pStr = (LPSTR)v_Codex;
		for (ushort i_StrPos = this->s_Length - 1; i_StrPos < this->s_Length + c_pAdd.s_Length; i_StrPos++)
		{
			this->c_pStr[i_StrPos] = c_pAdd.c_pStr[i_StrPos - (s_Length - 1)];
		}
		this->c_pStr[s_Length + c_pAdd.s_Length] = C_TXT_ENDL;
		this->s_Length += c_pAdd.s_Length;
	}
	else
	{
		free(this->c_pStr);
	}
}
void __CC
mks_str::vAppend(CSTR * c_pAdd)
{
	if (c_pAdd->s_Length == 0)return;
	void* v_Codex = realloc(this->c_pStr, this->s_Length + c_pAdd->s_Length + 1);
	if (v_Codex != NULL) {
		this->c_pStr = (LPSTR)v_Codex;
		for (ushort i_StrPos = this->s_Length - 1; i_StrPos < this->s_Length + c_pAdd->s_Length; i_StrPos++)
		{
			this->c_pStr[i_StrPos] = c_pAdd->c_pStr[i_StrPos - (s_Length - 1)];
		}
		this->c_pStr[s_Length + c_pAdd->s_Length] = C_TXT_ENDL;
		this->s_Length += c_pAdd->s_Length;
	}
	else 
	{
		free(c_pStr);
	}
}
void __CC
mks_str::vAppend(c_LPSTR c_pAdd)
{
	if (c_pStr == nullptr)return;
	ushort s_AddLen = vTermLength(c_pAdd);
	void * v_Codex = realloc(this->c_pStr, this->s_Length + s_AddLen + 1);
	if (v_Codex != NULL) 
	{
		this->c_pStr = (LPSTR)v_Codex;
		for (ushort i_StrPos = this->s_Length - 1; i_StrPos < this->s_Length + s_AddLen; i_StrPos++)
		{
			this->c_pStr[i_StrPos] = c_pAdd[i_StrPos - (this->s_Length - 1)];
		}
		this->c_pStr[this->s_Length + s_AddLen] = C_TXT_ENDL;
		this->s_Length += s_AddLen;
	}
	else
	{
		free(c_pStr);
	}
}
void __CC 
mks_str::vClean()
{
	if (this->s_Length != 0) {
		free(this->c_pStr);
	}
	this->s_Length = 0;
}
void __CC
mks_str::vClear()
{
	if (this->s_Length != 0) {
		for (int i_Index = 0; i_Index < this->s_Length; i_Index++)
		{
			this->c_pStr[i_Index] = 0;
		}
	}
}