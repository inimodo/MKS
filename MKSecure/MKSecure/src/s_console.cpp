#include "s_header.h"


//BOOL __CC 
//mks::vReadInput(CSTR* c_Buffer, LPDWORD dw_pLength)
//{
//	for ((*dw_pLength) = 0; (*dw_pLength) < c_Buffer->s_Length; (*dw_pLength)++)
//	{
//		c_Buffer->c_pStr[(*dw_pLength)] = _getch();
//		if (c_Buffer->c_pStr[(*dw_pLength)] == 13)
//		{
//			return FALSE;
//		}
//		if (c_Buffer->c_pStr[(*dw_pLength)] == 8)
//		{
//			if ((*dw_pLength) > 0)
//			{
//				c_Buffer->c_pStr[(*dw_pLength)] = 0;
//				this->dw_Cursor.X -= 1;
//				this->vWriteOutput(this->c_pOutputBuffer,c_Buffer->c_pStr[(*dw_pLength)], _MKSC_COLOR_INPUT, FALSE);
//				(*dw_pLength) -= 1;
//				continue;
//
//			}
//			continue;
//		}
//		this->vWriteOutput(this->c_pOutputBuffer,c_Buffer->c_pStr[(*dw_pLength)], _MKSC_COLOR_INPUT, TRUE);
//	}
//	return TRUE;
//}
//BOOL __CC
//mks::vWriteOutput(CHAR_INFO* c_pBuffer,c_LPSTR c_pMsg, DWORD dw_Length, WORD w_Color)
//{
//	for (DWORD dw_Index= 0,dw_Pos = _MKSW_INDEX(this->dw_Cursor); dw_Index < dw_Length; dw_Index++)
//	{
//		c_pBuffer[dw_Pos + dw_Index].Char.AsciiChar = c_pMsg[dw_Index];
//		c_pBuffer[dw_Pos + dw_Index].Attributes = w_Color| _MKSC_BACKGROUND;
//	}
//	this->dw_Cursor.X += dw_Length;
//	this->vLoadBuffer();
//	return TRUE;
//}
//BOOL __CC
//mks::vWriteOutput(CHAR_INFO* c_pBuffer,CHAR c_Msg, WORD w_Color,BOOL b_Add)
//{
//	c_pBuffer[_MKSW_INDEX(this->dw_Cursor)].Char.AsciiChar = c_Msg;
//	c_pBuffer[_MKSW_INDEX(this->dw_Cursor)].Attributes = w_Color | _MKSC_BACKGROUND;
//	this->dw_Cursor.X += (short)b_Add;
//	this->vLoadBuffer();
//	return TRUE;
//}
//BOOL __CC
//mks::vBreak()
//{
//	if (this->dw_Cursor.Y >= _MKSW_INHEIGHT) {
//		this->dw_Cursor.Y = _MKSW_DEF_POSY;
//		this->dw_Cursor.X = _MKSW_DEF_POSX;
//		this->vBufferClear();
//		return FALSE;
//	}
//	this->dw_Cursor.Y ++;
//	this->dw_Cursor.X = _MKSW_DEF_POSX;
//	return TRUE;
//}
//void __CC
//mks::vBufferClear() 
//{
//	for (int i_Index = 0; i_Index < _MKSW_WIDTH * _MKSW_HEIGHT; i_Index++)
//	{
//		this->c_pOutputBuffer[i_Index].Attributes = _MKSC_BACKGROUND;
//		this->c_pOutputBuffer[i_Index].Char.AsciiChar = 0;
//		this->c_pRegisterBuffer[i_Index].Attributes = BACKGROUND_RED;
//		this->c_pRegisterBuffer[i_Index].Char.AsciiChar = 0;
//	}
//}
//BOOL __CC 
//mks::vLoadBuffer()
//{
//	SMALL_RECT sm_Rect;
//	sm_Rect.Top = 0;
//	sm_Rect.Left = 0;
//	sm_Rect.Right = _MKSW_WIDTH-1;
//	sm_Rect.Bottom = _MKSW_HEIGHT-1;
//	WriteConsoleOutputA(this->o_HwndOutput, this->c_pOutputBuffer, this->dw_Size, {0,0}, &sm_Rect);
//	sm_Rect.Top = 0;
//	sm_Rect.Left = _MKSW_WIDTH - 1;
//	sm_Rect.Right = _MKSW_WIDTH*2;
//	sm_Rect.Bottom = _MKSW_HEIGHT - 1;
//	WriteConsoleOutputA(this->o_HwndOutput,this->c_pRegisterBuffer, this->dw_Size, { 0,0 }, &sm_Rect);
//
//	return 0;
//}
