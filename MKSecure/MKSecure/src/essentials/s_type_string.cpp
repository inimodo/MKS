#include "..\header\s_structs.h"


str::str(CLPSTR c_pInput)
	: s_Length(0), s_MemLen(0)
{this->Set(c_pInput);}

str::str()
	: s_Length(0), c_pStr(NULL), s_MemLen(0)
{}

str::~str()
{
	free(this->c_pStr);
}
str::str(INT16 s_Length)
	: s_Length(0), c_pStr(NULL), s_MemLen(0)
{
	this->Set(s_Length);
}

void __CC
str::Clean()
{
	LOG("BIG");
	free(this->c_pStr);
	this->c_pStr = NULL;
	this->s_Length = 0;
}

void __CC
str::Set(INT16 s_Length)
{
	this->Clean();
	this->c_pStr = (LPSTR)malloc(s_Length+1);
	this->s_Length = s_Length;
	this->s_MemLen = s_Length+1;
}
void __CC
str::Set(CLPSTR c_pText)
{
	this->Clean();
	this->s_Length =TermLength(c_pText);
	this->s_MemLen = this->s_Length+1;

	this->c_pStr = (LPSTR)malloc(s_Length+1);
	if (this->c_pStr != NULL) {
		for (INT16 i_StrPos = 0; i_StrPos < s_Length; i_StrPos++)
		{
			this->c_pStr[i_StrPos] = c_pText[i_StrPos];
		}
		this->c_pStr[s_Length] = M_ENDL;
	}
}
void __CC
str::Set(LPSTR c_pText, INT16 s_Len)
{
	this->Clean();
	this->s_Length = s_Len;
	this->s_MemLen = s_Len + 1;

	this->c_pStr = (LPSTR)malloc(s_Len + 1);
	if (this->c_pStr != NULL) {
		for (INT16 i_StrPos = 0; i_StrPos < s_Len; i_StrPos++)
		{
			this->c_pStr[i_StrPos] = c_pText[i_StrPos];
		}
		this->c_pStr[s_Len] = M_ENDL;
	}
}
void __CC
str::Set(LPSTR c_pText, INT16 s_Len,INT16 s_ReLen)
{
	this->Clean();
	this->s_Length = s_ReLen;
	this->s_MemLen = s_ReLen + 1;

	this->c_pStr = (LPSTR)malloc(s_ReLen + 1);
	if (this->c_pStr != NULL) {
		for (INT16 i_StrPos = 0; i_StrPos < s_Len; i_StrPos++)
		{
			this->c_pStr[i_StrPos] = c_pText[i_StrPos];
		}
		this->c_pStr[s_ReLen] = M_ENDL;
	}
}

void __CC	
str::Copy(str * c_pRef)
{
	this->Set(c_pRef->c_pStr,c_pRef->s_Length);
}
void __CC
str::CopyAll(str * c_pRef)
{
	this->Set(c_pRef->s_MemLen);
	memcpy(this->c_pStr, c_pRef->c_pStr, c_pRef->s_MemLen);
	this->s_Length = this->MeasureLength();
}

void __CC
str::Append(CSTR c_pAdd)
{
	if (c_pAdd.s_Length == 0)return;
	void* v_Codex = realloc(this->c_pStr, this->s_Length + c_pAdd.s_Length);
	if (v_Codex != NULL) {
		this->c_pStr = (LPSTR)v_Codex;
		for (INT16 i_StrPos = this->s_Length - 1; i_StrPos < this->s_Length + c_pAdd.s_Length; i_StrPos++)
		{
			this->c_pStr[i_StrPos] = c_pAdd.c_pStr[i_StrPos - (s_Length - 1)];
		}
		this->c_pStr[s_Length + c_pAdd.s_Length] = M_ENDL;
		this->s_Length += c_pAdd.s_Length;
	}
	else
	{
		free(this->c_pStr);
	}
}
void __CC
str::Append(CSTR * c_pAdd)
{
	if (c_pAdd->s_Length == 0)return;
	void* v_Codex = realloc(this->c_pStr, this->s_Length + c_pAdd->s_Length + 1);
	if (v_Codex != NULL) {
		this->c_pStr = (LPSTR)v_Codex;
		for (INT16 i_StrPos = this->s_Length - 1; i_StrPos < this->s_Length + c_pAdd->s_Length; i_StrPos++)
		{
			this->c_pStr[i_StrPos] = c_pAdd->c_pStr[i_StrPos - (s_Length - 1)];
		}
		this->c_pStr[s_Length + c_pAdd->s_Length] = M_ENDL;
		this->s_Length += c_pAdd->s_Length;
	}
}
void __CC
str::Append(CLPSTR c_pAdd)
{
	if (this->c_pStr == NULL)return;
	INT16 s_AddLen = TermLength(c_pAdd);

	char * c_pCodex = (char*)malloc( this->s_Length + s_AddLen + 1);
	if (c_pCodex != NULL)
	{
		for (INT16 i_StrPos = 0; i_StrPos < this->s_Length; i_StrPos++)
		{
			c_pCodex[i_StrPos] = this->c_pStr[i_StrPos];
		}
		free(this->c_pStr);
		for (INT16 i_StrPos = this->s_Length; i_StrPos < this->s_Length + s_AddLen; i_StrPos++)
		{
			c_pCodex[i_StrPos] = c_pAdd[i_StrPos - (this->s_Length )];
		}
		c_pCodex[this->s_Length + s_AddLen] = M_ENDL;
		this->c_pStr = c_pCodex;
		this->s_Length += s_AddLen;
	}
}

void __CC
str::ToString(DWORD i_Value,INT16 i_Digits)
{
	this->Set(i_Digits+1);
	DWORD i_Tenth = 10, i_Divisor =  i_Value ,i_Temp;
	for (INT32 i_Index = 0; i_Index <i_Digits; i_Index++)
	{
		i_Temp = i_Divisor % i_Tenth;
		i_Divisor -= i_Temp;
		this->c_pStr[i_Digits -1-i_Index] = (i_Temp / (i_Tenth / 10))+48;
		i_Tenth *= 10;
	}
	this->c_pStr[i_Digits] = M_ENDL;
}

void __CC
str::Clear()
{
	if (this->s_Length != 0) {
		for (INT32 i_Index = 0; i_Index < this->s_Length; i_Index++)
		{
			this->c_pStr[i_Index] = 0;
		}
	}
}
INT16 __CC
str::MeasureLength() 
{
	for (INT16 i_Pos = 0; i_Pos < this->s_MemLen; i_Pos++)
	{
		if (this->c_pStr[i_Pos] == M_ENDL)return i_Pos;
	}
	return -1;
}
INT16 __CC
str::ToInt(INT16 i_Offset)
{
	INT16 i_Output = 0;
	for (INT32 i_Index = 0; i_Index < this->s_Length- i_Offset; i_Index++)
	{
		i_Output += (INT32)(this->c_pStr[i_Index+ i_Offset] - (char)48)* Tenth(this->s_Length- i_Offset - i_Index - 1);
	}
	return  i_Output;
}

inline INT32 __CC
TermLength(CLPSTR c_Text)
{
	INT16 s_rLen = 0;
	while (c_Text[s_rLen] != M_ENDL)
	{
		++s_rLen;
	}
	return s_rLen;
}
inline INT32 __CC
Tenth(char c_Expo)
{
	INT32 ull_return = 1;
	for (char c_Index = 0; c_Index < c_Expo; c_Index++)
	{
		ull_return *= 10;
	}
	return ull_return;
}

inline INT32 __CC
StringToInt(CSTR c_Input,INT32 i_Size)
{
	INT32 ull_Output = 0;
	for (INT32 i_Index = 0; i_Index < i_Size; i_Index++)
	{
		ull_Output += (INT32)(c_Input.c_pStr[i_Index] - (char)48)* Tenth(i_Size - i_Index - 1);
	}
	return  ull_Output;
}
inline INT32 __CC
StringToInt(CSTR c_Input,INT32 i_Size,INT32 i_Offset)
{
	INT32 ull_Output = 0;
	for (INT32 i_Index = 0; i_Index < i_Size; i_Index++)
	{
		ull_Output += (INT32)(c_Input.c_pStr[i_Index + i_Offset] - (char)48)* Tenth(i_Size - i_Index - 1);
	}
	return  ull_Output;
}
void __CC
IntToString(INT32 i_Input,CSTR * c_pStr)
{
	INT32 i_Tenth{ 10 },i_Divisor{ i_Input },i_Result[10];

	if (i_Input == 0) 
	{
		c_pStr->Set(1);
		c_pStr->c_pStr[0] = 48;
		return;
	}

	for (INT32 i_Index = 0; i_Index <9; i_Index++)
	{
		if (i_Divisor == 0) {
			i_Tenth = i_Index;
			break;
		}
		i_Result[i_Index] = i_Divisor % i_Tenth;
		i_Divisor -= i_Result[i_Index];
		i_Result[i_Index] = (i_Result[i_Index] / (i_Tenth / 10));
		i_Tenth *= 10;
		if (i_Index == 8) {
			i_Tenth = 9;
		}
	}
	c_pStr->Set(i_Tenth);
	for (INT32 i_Index = 0; i_Index < i_Tenth; i_Index++)
	{
		c_pStr->c_pStr[i_Tenth - i_Index - 1] = i_Result[i_Index] + 48;
	}
	c_pStr->c_pStr[c_pStr->s_Length] = M_ENDL;
}
