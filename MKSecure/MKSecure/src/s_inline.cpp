#include "s_header.h"

int __CC
vTermLength(c_LPSTR c_Text)
{
	ushort s_rLen = 0;
	while (c_Text[s_rLen] != C_TXT_ENDL)
	{
		++s_rLen;
	}
	return s_rLen;
}
ULLI __CC
vTenth(char c_Expo)
{
	ULLI ull_return = 1;
	for (char c_Index = 0; c_Index < c_Expo; c_Index++)
	{
		ull_return *= 10;
	}
	return ull_return;
}
