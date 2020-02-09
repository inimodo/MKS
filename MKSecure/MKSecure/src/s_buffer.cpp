#include"s_header.h"
#include "s_header.h"

BOOL __CC
mks_buffer::vWriteBuffer()
{
	return WriteConsoleOutputA(this->o_Output, this->c_pBuffer, this->dw_Size, this->dw_Pos, &(this->sm_Rect));
}
void __CC 
mks_buffer::vCleanup()
{
	free(this->c_pBuffer);
}
BOOL __CC	
mks_buffer::vSetup(COORD dw_Loc, COORD dw_Dim, HANDLE o_Hwnd)
{
	this->dw_Cursor = { 0,0 };
	this->dw_Pos = {0,0};
	this->dw_Size = dw_Dim;
	this->o_Output = o_Hwnd;
	this->sm_Rect.Top = dw_Loc.Y;
	this->sm_Rect.Left = dw_Loc.X;
	this->sm_Rect.Right = dw_Dim.X+ dw_Loc.X-1;
	this->sm_Rect.Bottom = dw_Dim.Y+ dw_Loc.Y-1;
	this->c_pBuffer = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)* dw_Dim.X* dw_Dim.Y);
	if (this->c_pBuffer == NULL)return FALSE;
	this->vBufferClear();
	return TRUE;
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
				this->vSetCursor(-1, 0);
				c_Buffer->c_pStr[(*dw_pLength)] = 0;

				this->vWriteOutput( c_Buffer->c_pStr[(*dw_pLength)], w_Color, FALSE);
				(*dw_pLength) -= 2;
				continue;
			}
			continue;
		}
		this->vWriteOutput(c_Buffer->c_pStr[(*dw_pLength)], w_Color, TRUE);
	}
	return TRUE;
}
BOOL __CC
mks_buffer::vReadInput(CSTR* c_Buffer, LPDWORD dw_pLength, WORD w_Color,CHAR c_Passchar)
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

				this->vSetCursor(-1, 0);
				c_Buffer->c_pStr[(*dw_pLength)] = 0;

				this->vWriteOutput(c_Buffer->c_pStr[(*dw_pLength)], w_Color, FALSE);
				(*dw_pLength) -= 2;
				continue;

			}
			continue;
		}
		this->vWriteOutput(c_Passchar, w_Color, TRUE);
	}
	return TRUE;
}
BOOL __CC
mks_buffer::vWriteOutput(c_LPSTR c_pMsg, DWORD dw_Length, WORD w_Color)
{
	for (DWORD dw_Index = 0; dw_Index < dw_Length; dw_Index++)
	{
		c_pBuffer[_MKSW_INDEX(this->dw_Cursor, this->dw_Size)].Char.AsciiChar = c_pMsg[dw_Index];
		c_pBuffer[_MKSW_INDEX(this->dw_Cursor, this->dw_Size)].Attributes = w_Color | _MKSC_BACKGROUND;
		this->vSetCursor(1, 0);
	}
	return this->vWriteBuffer();
}
BOOL __CC
mks_buffer::vWriteOutput( CHAR c_Msg, WORD w_Color, BOOL b_Add)
{
	c_pBuffer[_MKSW_INDEX(this->dw_Cursor,this->dw_Size)].Char.AsciiChar = c_Msg;
	c_pBuffer[_MKSW_INDEX(this->dw_Cursor,this->dw_Size)].Attributes = w_Color | _MKSC_BACKGROUND;
	this->vSetCursor(b_Add,0);
	return this->vWriteBuffer();
}

void __CC
mks_buffer::vBufferClear()
{
	this->vSetCursor({ 0,0 });
	for (int i_Index = 0; i_Index < this->dw_Size.X * this->dw_Size.Y; i_Index++)
	{
		this->c_pBuffer[i_Index].Attributes = _MKSC_BACKGROUND | _MKSC_COLOR_BORDER;
		this->c_pBuffer[i_Index].Char.AsciiChar = 0;

	}
	this->vWriteBuffer();
}
void __CC 
mks_buffer::vSetCursor(COORD dw_NewPos)
{
	this->dw_Cursor = dw_NewPos;
}
void __CC 
mks_buffer::vSetCursor(SHORT s_X, SHORT s_Y)
{
	this->dw_Cursor.X += s_X;
	this->dw_Cursor.Y += s_Y;
	if (this->dw_Cursor.X >= this->dw_Size.X - 1) 
	{
		this->dw_Cursor.Y++;
		this->dw_Cursor.X = 0;
	}
	if (this->dw_Cursor.Y >= this->dw_Size.Y - 1)
	{
		this->dw_Cursor.Y = 0;
		this->vBufferClear();
	}
}
void __CC
mks_buffer::vBreak()
{
	this->vSetCursor(0, 1);
	this->dw_Cursor.X = 0;
}
void __CC
mks_buffer::vTab(SHORT s_Tab)
{
	this->vSetCursor(s_Tab, 0);

}