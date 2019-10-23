#include "s_header.h"


BOOL __ST
cConsole::vSetupHandle()
{
	o_HwndOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	o_HwndInput = GetStdHandle(STD_INPUT_HANDLE);
	if (o_HwndOutput == NULL || o_HwndInput == NULL) {
		return FALSE;
	}
	if (GetUserNameA(this->c_LUser, (LPDWORD)& this->c_LUser.s_Length ) == NULL)
	{
		return FALSE;
	}
	if (_getcwd(this->c_LDir, this->c_LDir.s_Length) == NULL) 
	{
		return FALSE;
	}
	this->c_pOutputBuffer = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * _MKSW_HEIGHT * _MKSW_WIDTH);
	this->c_pRegisterBuffer = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * _MKSW_HEIGHT * _MKSW_WIDTH);
	if (this->c_pOutputBuffer == NULL || this->c_pRegisterBuffer == NULL) {
		free(this->c_pOutputBuffer);
		free(this->c_pRegisterBuffer);
		return FALSE;
	}
	this->vBufferClear();
	return TRUE;
}

BOOL __CC 
cConsole::vReadInput(CSTR* c_Buffer, LPDWORD dw_pLength)
{
	for ((*dw_pLength) = 0; (*dw_pLength) < c_Buffer->s_Length; (*dw_pLength)++)
	{
		c_Buffer->c_pStr[(*dw_pLength)] = _getch();
		if (c_Buffer->c_pStr[(*dw_pLength)] == 13)
		{
			return FALSE;
		}
		if (c_Buffer->c_pStr[(*dw_pLength)] == 8)
		{
			if ((*dw_pLength) > 0)
			{
				c_Buffer->c_pStr[(*dw_pLength)] = 0;
				this->dw_Cursor.X -= 1;
				this->vWriteOutput(c_Buffer->c_pStr[(*dw_pLength)], _MKSC_COLOR_INPUT, FALSE);
				(*dw_pLength) -= 1;
				continue;

			}
		}
		this->vWriteOutput(c_Buffer->c_pStr[(*dw_pLength)], _MKSC_COLOR_INPUT, TRUE);
	}
	return TRUE;
}
BOOL __CC
cConsole::vWriteOutput(c_LPSTR c_pMsg, DWORD dw_Length, WORD w_Color)
{
	for (DWORD dw_Index= 0,dw_Pos = _MKSW_INDEX(this->dw_Cursor); dw_Index < dw_Length; dw_Index++)
	{
		this->c_pOutputBuffer[dw_Pos + dw_Index].Char.AsciiChar = c_pMsg[dw_Index];
		this->c_pOutputBuffer[dw_Pos + dw_Index].Attributes = w_Color| _MKSC_BACKGROUND;
	}
	this->dw_Cursor.X += dw_Length;
	this->vLoadBuffer();
	return TRUE;
}
BOOL __CC
cConsole::vWriteOutput(CHAR c_Msg, WORD w_Color,BOOL b_Add)
{
	this->c_pOutputBuffer[_MKSW_INDEX(this->dw_Cursor)].Char.AsciiChar = c_Msg;
	this->c_pOutputBuffer[_MKSW_INDEX(this->dw_Cursor)].Attributes = w_Color | _MKSC_BACKGROUND;
	this->dw_Cursor.X += b_Add;
	this->vLoadBuffer();
	return TRUE;
}
BOOL __CC
cConsole::vBreak()
{
	this->dw_Cursor.Y ++;
	this->dw_Cursor.X = _MKSW_DEF_POSX;
	return TRUE;
}
void __CC
cConsole::vBufferClear() 
{
	for (int i_Index = 0; i_Index < _MKSW_WIDTH * _MKSW_HEIGHT; i_Index++)
	{
		this->c_pOutputBuffer[i_Index].Attributes = _MKSC_BACKGROUND;
		this->c_pOutputBuffer[i_Index].Char.AsciiChar = 0;
		this->c_pRegisterBuffer[i_Index].Attributes = BACKGROUND_RED;
		this->c_pRegisterBuffer[i_Index].Char.AsciiChar = 0;
	}
}
BOOL __CC 
cConsole::vLoadBuffer()
{
	SMALL_RECT sm_Rect;
	sm_Rect.Top = 0;
	sm_Rect.Left = 0;
	sm_Rect.Right = _MKSW_WIDTH-1;
	sm_Rect.Bottom = _MKSW_HEIGHT-1;
	WriteConsoleOutputA(this->o_HwndOutput, this->c_pOutputBuffer, this->dw_Size, {0,0}, &sm_Rect);
	sm_Rect.Top = 0;
	sm_Rect.Left = _MKSW_WIDTH - 1;
	sm_Rect.Right = _MKSW_WIDTH*2;
	sm_Rect.Bottom = _MKSW_HEIGHT - 1;
	WriteConsoleOutputA(this->o_HwndOutput,this->c_pRegisterBuffer, this->dw_Size, { 0,0 }, &sm_Rect);

	return 0;
}
