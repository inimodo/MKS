#include "..\header\s_structs.h"

HANDLE buffer::o_Output;

BOOL __CC
buffer::WriteBuffer()
{
	SMALL_RECT sm_Base = this->sm_Rect;
	return WriteConsoleOutputA(this->o_Output, this->c_pBuffer, this->i_Size, this->i_Pos, &sm_Base);
}
void __CC 
buffer::Cleanup()
{
	free(this->c_pBuffer);
}
BOOL __CC	
buffer::Setup(COORD i_Loc, COORD i_Dim, WORD i_Backcolor)
{
	this->i_Cursor = { 0,0 };
	this->i_Pos = {0,0};
	this->i_Size = i_Dim;
	this->sm_Rect.Top = i_Loc.Y;
	this->sm_Rect.Left = i_Loc.X;
	this->sm_Rect.Right = i_Dim.X+ i_Loc.X-1;
	this->sm_Rect.Bottom = i_Dim.Y+ i_Loc.Y-1;
	this->i_Backcolor = i_Backcolor;
	this->c_pBuffer = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)* i_Dim.X* i_Dim.Y);
	if (this->c_pBuffer == NULL)return FALSE;
	return TRUE;
}
BOOL __CC
buffer::ReadInput(CSTR* c_Buffer, INT32 * i_pLength,WORD w_Color)
{
	for ((*i_pLength) = 0; (*i_pLength) < c_Buffer->s_Length; (*i_pLength)++)
	{
		c_Buffer->c_pStr[(*i_pLength)] = _getch();
		if (c_Buffer->c_pStr[(*i_pLength)] == 13)
		{
			c_Buffer->c_pStr[(*i_pLength)] = M_ENDL;
			return TRUE;
		}
		if (c_Buffer->c_pStr[(*i_pLength)] == 8)
		{
			if ((*i_pLength) > 0)
			{
				this->SetCursor(-1, 0);
				c_Buffer->c_pStr[(*i_pLength)] = 0;

				this->WriteChar( c_Buffer->c_pStr[(*i_pLength)], w_Color, FALSE);
				this->WriteBuffer();
				(*i_pLength) -= 2;
				continue;
			}
			continue;
		}
		this->WriteChar(c_Buffer->c_pStr[(*i_pLength)], w_Color, TRUE);
		this->WriteBuffer();
	}
	return FALSE;
}
BOOL __CC
buffer::ReadInput(CSTR* c_Buffer, INT32* i_pLength, WORD w_Color,CHAR c_Passchar)
{
	for ((*i_pLength) = 0; (*i_pLength) < c_Buffer->s_Length; (*i_pLength)++)
	{
		c_Buffer->c_pStr[(*i_pLength)] = _getch();
		if (c_Buffer->c_pStr[(*i_pLength)] == 13)
		{
			return FALSE;
		}
		if (c_Buffer->c_pStr[(*i_pLength)] == 8)
		{
			if ((*i_pLength) > 0)
			{

				this->SetCursor(-1, 0);
				c_Buffer->c_pStr[(*i_pLength)] = 0;

				this->WriteChar(c_Buffer->c_pStr[(*i_pLength)], w_Color, FALSE);
				this->WriteBuffer();
				(*i_pLength) -= 2;
				continue;

			}
			continue;
		}
		this->WriteChar(c_Passchar, w_Color, TRUE);
		this->WriteBuffer();

	}
	return TRUE;
}
BOOL __CC
buffer::WriteOutput(DWORD i_Value,INT16 i_Digits, WORD w_Color)
{
	DWORD i_Tenth = 10, i_Divisor = i_Value, i_Temp;
	INT16 i_Startloc = M_INDEX(this->i_Cursor, this->i_Size);
	for (INT32 i_Index = 0; i_Index <i_Digits; i_Index++)
	{
		i_Temp = i_Divisor % i_Tenth;
		i_Divisor -= i_Temp;
		c_pBuffer[i_Startloc +(i_Digits - 1 - i_Index)].Char.AsciiChar = (i_Temp / (i_Tenth / 10)) + 48;
		c_pBuffer[i_Startloc + (i_Digits - 1 - i_Index)].Attributes = w_Color | this->i_Backcolor;
		i_Tenth *= 10;
		this->SetCursor(1, 0);
	}
	return FALSE;
}
BOOL __CC
buffer::WriteOutput(LPSTR c_pMsg, WORD w_Color)
{
	for (DWORD i_Index = 0; c_pMsg[i_Index] != M_ENDL; i_Index++)
	{
		c_pBuffer[M_INDEX(this->i_Cursor, this->i_Size)].Char.AsciiChar = c_pMsg[i_Index];
		c_pBuffer[M_INDEX(this->i_Cursor, this->i_Size)].Attributes = w_Color | this->i_Backcolor;
		this->SetCursor(1, 0);
	}
	return FALSE;
}
BOOL __CC
buffer::WriteOutput(LPSTR c_pMsg, WORD w_Color, INT16 i_Length)
{
	for (DWORD i_Index = 0; i_Index < i_Length; i_Index++)
	{

		c_pBuffer[M_INDEX(this->i_Cursor, this->i_Size)].Char.AsciiChar = c_pMsg[i_Index];
		c_pBuffer[M_INDEX(this->i_Cursor, this->i_Size)].Attributes = w_Color | this->i_Backcolor;
		this->SetCursor(1, 0);
	}
	return FALSE;
}
BOOL __CC
buffer::WriteChar( CHAR c_Msg, WORD w_Color, BOOL b_Add)
{
	c_pBuffer[M_INDEX(this->i_Cursor,this->i_Size)].Char.AsciiChar = c_Msg;
	c_pBuffer[M_INDEX(this->i_Cursor,this->i_Size)].Attributes = w_Color | this->i_Backcolor;
	this->SetCursor(b_Add,0);
	return FALSE;
}
void __CC
buffer::BufferClear()
{
	this->SetCursor({ 0,0 });
	for (INT16 i_Index = 0; i_Index < this->i_Size.X *this->i_Size.Y; i_Index++)
	{
		this->c_pBuffer[i_Index].Char.AsciiChar = 0;
		this->c_pBuffer[i_Index].Attributes = this->i_Backcolor;
	}
}
void __CC 
buffer::SetCursor(COORD i_NewPos)
{
	this->i_Cursor = i_NewPos;
}
void __CC 
buffer::SetCursor(INT32 s_X, INT32 s_Y)
{
	this->i_Cursor.X += s_X;
	this->i_Cursor.Y += s_Y;
	if (this->i_Cursor.X >= this->i_Size.X-1 ) 
	{
		this->i_Cursor.Y++;
		this->i_Cursor.X = 0;
	}
	if (this->i_Cursor.Y >= this->i_Size.Y )
	{
		this->i_Cursor.Y-=1;
		for (INT16 i_Index = 0; i_Index < this->i_Size.Y - 1; i_Index++)
		{
			for (INT16 i_Subindex = 0; i_Subindex < this->i_Size.X; i_Subindex++)
			{
				this->c_pBuffer[i_Index*this->i_Size.X + i_Subindex] = this->c_pBuffer[(i_Index + 1)*(this->i_Size.X) + i_Subindex];
			}
		}
		for (INT16 i_Index = (this->i_Size.Y - 1); i_Index < this->i_Size.Y ; i_Index++)
		{
			for (INT16 i_Subindex = 0; i_Subindex < this->i_Size.X; i_Subindex++)
			{
				this->c_pBuffer[i_Index*this->i_Size.X + i_Subindex].Attributes = this->i_Backcolor;
				this->c_pBuffer[i_Index*this->i_Size.X + i_Subindex].Char.UnicodeChar = 0;
			}
		}
	}
}
void __CC
buffer::Break()
{
	this->SetCursor(0, 1);
	this->i_Cursor.X = 0;
}
void __CC
buffer::Tab(INT32 s_Tab)
{
	this->SetCursor(s_Tab, 0);

}