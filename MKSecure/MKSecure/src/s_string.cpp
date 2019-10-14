#include "s_header.h"

void __CC 
text::cStr::vSet(const charp c_pText) 
{
	this->vClean();
	while (c_pText[this->s_Length] != text::C_TXT_ENDL)
	{
		this->s_Length ++;
	}
	this->c_pStr = (charp)malloc(this->s_Length);
	for (ushort i_StrPos = 0; i_StrPos < this->vClean; i_StrPos++)
	{
		this->c_pStr[i_StrPos] = c_pText[i_StrPos];
	}
}
void __CC 
text::cStr::vClean() 
{
	this->s_Length = 0;
	free(this->c_pStr);
}
void __CC
text::cStr::vAppend(cStr * c_pAdd)
{
	if (c_pStr == nullptr)return;
	this->s_Length += c_pAdd->s_Length;
	this->c_pStr = (charp)realloc(this->c_pStr,this->s_Length);
	for (ushort i = 0; i < this->s_Length; i++)
	{

	}
}