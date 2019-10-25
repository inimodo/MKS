#include"s_header.h"
#include "s_header.h"

BOOL __CC	
mks_buffer::vSetup(COORD dw_Loc, COORD dw_Dim, HANDLE o_Hwnd)
{
	this->dw_Cursor = { 1,1 };
	this->dw_Pos = {0,0};
	this->dw_Size = dw_Dim;
	this->o_Output = o_Hwnd;
	this->c_pBuffer = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)* dw_Dim.X* dw_Dim.Y);
	if (this->c_pBuffer == NULL)return FALSE;
	this->sm_Rect.Top = dw_Loc.Y;
	this->sm_Rect.Left = dw_Loc.X;
	this->sm_Rect.Right = dw_Dim.X+ dw_Loc.X;
	this->sm_Rect.Bottom = dw_Dim.Y+ dw_Loc.Y;
	this->vBufferClear();
	return TRUE;
}
void __CC 
mks_buffer::vCleanup()
{
	free(this->c_pBuffer);
}
BOOL __CC
mks_buffer::vReadInput(CSTR* c_Buffer, LPDWORD dw_pLength,WORD w_Color)
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
				this->vWriteOutput( c_Buffer->c_pStr[(*dw_pLength)], w_Color, FALSE);
				(*dw_pLength) -= 1;
				continue;

			}
			continue;
		}
		this->vWriteOutput(c_Buffer->c_pStr[(*dw_pLength)], w_Color, TRUE);
	}
	return TRUE;
}
BOOL __CC
mks_buffer::vWriteOutput(c_LPSTR c_pMsg, DWORD dw_Length, WORD w_Color)
{
	for (DWORD dw_Index = 0, dw_Pos = _MKSW_INDEX(this->dw_Cursor, this->dw_Size); dw_Index < dw_Length; dw_Index++)
	{
		c_pBuffer[dw_Pos + dw_Index].Char.AsciiChar = c_pMsg[dw_Index];
		c_pBuffer[dw_Pos + dw_Index].Attributes = w_Color | _MKSC_BACKGROUND;
	}
	this->dw_Cursor.X += dw_Length;
	this->vWriteBuffer();
	return TRUE;
}
BOOL __CC
mks_buffer::vWriteOutput( CHAR c_Msg, WORD w_Color, BOOL b_Add)
{
	c_pBuffer[_MKSW_INDEX(this->dw_Cursor,this->dw_Size)].Char.AsciiChar = c_Msg;
	c_pBuffer[_MKSW_INDEX(this->dw_Cursor,this->dw_Size)].Attributes = w_Color | _MKSC_BACKGROUND;
	this->dw_Cursor.X += (short)b_Add;
	this->vWriteBuffer();
	return TRUE;
}
BOOL __CC
mks_buffer::vBreak()
{
	if (this->dw_Cursor.Y >= this->dw_Size.Y-1 || this->dw_Cursor.X >= this->dw_Size.X -1 ) {
		this->dw_Cursor.Y = 1;
		this->dw_Cursor.X = 1;
		this->vBufferClear();
		return FALSE;
	}
	this->dw_Cursor.Y++;
	this->dw_Cursor.X = 1;
	return TRUE;
}
void __CC
mks_buffer::vBufferClear()
{
	for (int i_Index = 0; i_Index < _MKSW_WIDTH * _MKSW_HEIGHT; i_Index++)
	{
		this->c_pBuffer[i_Index].Attributes = _MKSC_BACKGROUND;
		this->c_pBuffer[i_Index].Char.AsciiChar = 0;
	}
}
BOOL __CC
mks_buffer::vWriteBuffer()
{
	return WriteConsoleOutputA(this->o_Output, this->c_pBuffer, this->dw_Size, this->dw_Pos, &(this->sm_Rect));
}
