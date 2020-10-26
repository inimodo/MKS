#define _MKS_REQ_SYSTEM_ACCESS
#define _MKS_REQ_DATA_ACCESS
#include "header\s_functions.h"

//Sytem


void   __CC
mks::system::AddScreenBuffer(BUFFER_INFO bi_Buffer, INT16 i_Index)
{
	a_Assets_Buffer[i_Index].Setup(bi_Buffer.i_Pos, bi_Buffer.i_Size, bi_Buffer.i_Color);
	a_Assets_Buffer[i_Index].BufferClear();
	a_Assets_Buffer[i_Index].WriteBuffer();
}
BOOL __CC
mks::system::Initialize()
{
	i_Status = M_STATUS_KEEPALIVE;
	buffer::o_Output = GetStdHandle(STD_OUTPUT_HANDLE);
	if (buffer::o_Output == NULL) return FALSE;

	c_WinUsername.Set(UNLEN);
	c_SoftwareDir.Set(MAX_PATH);
	c_WinUsername.s_Length = UNLEN;
	if (GetUserNameA(c_WinUsername.c_pStr, (LPDWORD)& c_WinUsername.s_Length) == NULL) return FALSE;
	c_WinUsername.s_Length--;

	if (_getcwd(c_SoftwareDir.c_pStr, MAX_PATH) == NULL) return FALSE;
	INT32 i_TempLength = TermLength(c_SoftwareDir.c_pStr);
	if (c_SoftwareDir.c_pStr[i_TempLength - 1] != M_BASL)
	{
		c_SoftwareDir.c_pStr[i_TempLength] = M_BASL;
		c_SoftwareDir.c_pStr[++i_TempLength] = M_ENDL;
	}

	p_WorkDirectory.DisolvePath(c_SoftwareDir.c_pStr);
	AddScreenBuffer(M_FEEDBACK_BUFFER, M_BUFFER_FEEDBACK);
	AddScreenBuffer(M_MSTFILE_BUFFER, M_BUFFER_MSTFILE);
	AddScreenBuffer(M_REQUEST_BUFFER, M_BUFFER_REQUEST);
	AddScreenBuffer(M_STATUS_BUFFER, M_BUFFER_STATUS);

	INT32 i_Height, i_Width, i_Highest_X = 0, i_Highest_Y = 0;
	for (INT32 i_Index = 0; i_Index < M_BUFFERS; i_Index++)
	{
		i_Width = a_Assets_Buffer[i_Index].sm_Rect.Right + 1;
		i_Height = a_Assets_Buffer[i_Index].sm_Rect.Bottom + 1;
		if (i_Width > i_Highest_X) {
			i_Highest_X = i_Width;
		}
		if (i_Height > i_Highest_Y) {
			i_Highest_Y = i_Height;
		}
	}

	COORD i_Size = { (INT16)i_Highest_X,(INT16)i_Highest_Y };
	SMALL_RECT sm_Rect = { 0,0, (INT16)i_Highest_X - 1,(INT16)i_Highest_Y - 1 };

	SetConsoleWindowInfo(buffer::o_Output, 1, &sm_Rect);
	SetConsoleScreenBufferSize(buffer::o_Output, i_Size);

	return TRUE;
}