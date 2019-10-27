#include "s_header.h"

inline int __CC
vTermLength(c_LPSTR c_Text)
{
	ushort s_rLen = 0;
	while (c_Text[s_rLen] != C_TXT_ENDL)
	{
		++s_rLen;
	}
	return s_rLen;
}
inline ULLI __CC
vTenth(char c_Expo)
{
	ULLI ull_return = 1;
	for (char c_Index = 0; c_Index < c_Expo; c_Index++)
	{
		ull_return *= 10;
	}
	return ull_return;
}

inline ULLI __CC 
vStringToUlli(CSTR c_Input,DWORD dw_Size)
{
	ULLI ull_Output = 0;
	for (int i_Index = 0; i_Index < dw_Size; i_Index++)
	{
		ull_Output+=(ULLI)(c_Input.c_pStr[i_Index] - (char)48)* vTenth(dw_Size- i_Index-1);
	}
	return  ull_Output;
}
inline void __CC
vIntToString(int i_Input, CSTR* c_Output)
{
	int i_Tenth{10};
	int i_Divisor{ i_Input };
	int i_Result[10];
	for (int i_Index = 0; i_Index <9; i_Index++)
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
	for (int i_Index = 0; i_Index < i_Tenth; i_Index++)
	{
		c_Output->c_pStr[i_Tenth - i_Index-1] = i_Result[i_Index] + 48;
	}
}
