#include "s_header.h"

int __CC 
vTermLength(c_LPSTR c_Text) 
{
	__REG ushort s_rLen = 0;
	while (c_Text[s_rLen] != C_TXT_ENDL)
	{
		++s_rLen;
	}
	return s_rLen;
}
cStr::cStr(c_LPSTR c_pInput)
	: s_Length(0)
{this->vSet(c_pInput);}

cStr::cStr()
	: s_Length(0), c_pStr(0)
{}
void __CC
cStr::vSet(ushort s_Length)
{
	this->vClean();
	this->c_pStr = (LPSTR)malloc(s_Length+1);
	this->s_Length = s_Length;
}
void __CC
cStr::vSet(c_LPSTR c_pText) 
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
cStr::vAppend(cStr c_pAdd)
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
cStr::vAppend(cStr * c_pAdd)
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
cStr::vAppend(c_LPSTR c_pAdd)
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
cStr::vClean()
{
	if (this->s_Length != 0) {
		free(this->c_pStr);
	}
	this->s_Length = 0;
}