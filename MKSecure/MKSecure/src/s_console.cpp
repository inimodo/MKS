#define _MKS_REQ_DATA_ACCESS
#include "header\s_functions.h"

//Console//_MKS_REQ_DATA_ACCESS

void __CC
mks::console::WaitConsoleInput(CSTR * c_InputRegister,INT32 * i_Length)
{
	a_Assets_Buffer[M_BUFFER_REQUEST].BufferClear();
	a_Assets_Buffer[M_BUFFER_REQUEST].WriteChar('~', M_COLOR_NAME);
	a_Assets_Buffer[M_BUFFER_REQUEST].WriteBuffer();
	a_Assets_Buffer[M_BUFFER_REQUEST].ReadInput(c_InputRegister, i_Length, M_COLOR_INPUT);
}
void __CC
mks::console::PathFeedback(TMSG i_Msg)
{
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteChar(63, M_COLOR_INDEXES);
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteOutput(a_Assets_Messages[i_Msg], a_Assets_MColors[i_Msg], M_MSGSIZE);
	a_Assets_Buffer[M_BUFFER_FEEDBACK].Break();
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteBuffer();
}
void __CC
mks::console::ResolveError()
{
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteChar('!', M_COLOR_INDEXES);
	a_Assets_Buffer[M_BUFFER_FEEDBACK].Tab(1);
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteOutput(a_Assets_Messages[M_MESSAGES_QUERRY_UNKNOW], a_Assets_MColors[M_MESSAGES_QUERRY_UNKNOW], M_MSGSIZE);
	a_Assets_Buffer[M_BUFFER_FEEDBACK].Break();
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteBuffer();
}

void __CC
mks::console::FuncHeader( BRANCH * b_pBranch)
{
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteChar('~', M_COLOR_INDEXES);
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteOutput(a_Assets_Functions[b_pBranch->i_Key].c_Name, M_COLOR_FUNCTION, M_FUNC_KWLENRAW);
	for (char i_Index = 0; i_Index < a_Assets_Functions[b_pBranch->i_Key].c_Arguments; i_Index++)
	{
		a_Assets_Buffer[M_BUFFER_FEEDBACK].Tab(1);
		a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteOutput(b_pBranch->a_Args[i_Index].c_pStr, M_COLOR_FUNCTION, b_pBranch->a_Args[i_Index].s_Length);
	}
	a_Assets_Buffer[M_BUFFER_FEEDBACK].Break();
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteBuffer();
}

void __CC
mks::console::FuncFeedback(TMSG i_Msg,BRANCH * b_pBranch)
{

	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteChar(63, M_COLOR_INDEXES);
	a_Assets_Buffer[M_BUFFER_FEEDBACK].Tab(1);
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteOutput(a_Assets_Messages[i_Msg], a_Assets_MColors[i_Msg], M_MSGSIZE);
	a_Assets_Buffer[M_BUFFER_FEEDBACK].Break();
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteBuffer();
}

void __CC
mks::console::PlotTree(FSTACK * o_List)
{
	for (INT16 i_Index = 0; i_Index < o_List->i_Files; i_Index++)
	{
		FileInfo(i_Index,o_List, M_BUFFER_FEEDBACK);
	}	
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteBuffer();
}

void __CC
mks::console::PlotMessage(INT16 i_Value, INT16 i_Digits, BOOL b_Newline)
{
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteOutput(i_Value, i_Digits, M_COLOR_SYMPOL);
	
	if (b_Newline)
	{
		a_Assets_Buffer[M_BUFFER_FEEDBACK].Break();
	}
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteBuffer();
}

void __CC
mks::console::PlotMessage(char * c_pMessage, INT16 i_Length, BOOL b_Newline)
{
	if (c_pMessage != NULL) 
	{
		if (i_Length == 0)i_Length = TermLength(c_pMessage);
		a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteOutput(c_pMessage, M_COLOR_SYMPOL, i_Length);
	}
	if (b_Newline)
	{
		a_Assets_Buffer[M_BUFFER_FEEDBACK].Break();
	}
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteBuffer();
}

void __CC
mks::console::FileSize(DWORD i_Size,WORD i_Color,INT16 i_Buffer)
{
	char c_Prefix[3] = {'k','m','g'};
	a_Assets_Buffer[i_Buffer].WriteChar('(', M_COLOR_SYMPOL);
	for (DWORD i_Pos = 0,i_Sizing = 1000; i_Pos < 3; i_Pos++, i_Sizing*=1000)
	{
		if ((i_Size / i_Sizing) < 1000) 
		{
			a_Assets_Buffer[i_Buffer].WriteOutput(i_Size / i_Sizing,3, i_Color);
			a_Assets_Buffer[i_Buffer].WriteChar(c_Prefix[i_Pos], i_Color);
			break;
		}
	}
	a_Assets_Buffer[i_Buffer].WriteChar('B', i_Color);
	a_Assets_Buffer[i_Buffer].WriteChar(')', M_COLOR_SYMPOL);
}
void __CC
mks::console::MstFileInfo(INT16 i_Index, MSTSTACK * f_Stack, INT16 i_Buffer)
{
	a_Assets_Buffer[i_Buffer].WriteChar(195, M_COLOR_SYMPOL);
	a_Assets_Buffer[i_Buffer].WriteChar('[', M_COLOR_SYMPOL);
	a_Assets_Buffer[i_Buffer].WriteOutput(i_Index,3, M_COLOR_SYMPOL_UPLIGHT);
	a_Assets_Buffer[i_Buffer].WriteChar(']', M_COLOR_SYMPOL);
	mks::console::FileSize(f_Stack->mst_pStack[i_Index].GetFs(), M_COLOR_SYMPOL_UPLIGHT, i_Buffer);
	a_Assets_Buffer[i_Buffer].WriteChar(':', M_COLOR_SYMPOL);
	a_Assets_Buffer[i_Buffer].WriteOutput(f_Stack->mst_pStack[i_Index].fp_Filepath.c_Filename ,M_COLOR_FUNCTION_OUTPUT, f_Stack->mst_pStack[i_Index].fp_Filepath.c_Filename.s_Length);
	a_Assets_Buffer[i_Buffer].WriteChar('/', M_COLOR_SYMPOL);
	a_Assets_Buffer[i_Buffer].WriteOutput(f_Stack->mst_pStack[i_Index].fs_Filestack.i_Files,3, M_COLOR_SYMPOL_UPLIGHT);
	a_Assets_Buffer[i_Buffer].Break();
}
void __CC
mks::console::FileInfo(INT16 i_Index, FSTACK * f_Stack, INT16 i_Buffer)
{

	a_Assets_Buffer[i_Buffer].WriteChar(195, M_COLOR_SYMPOL);
	a_Assets_Buffer[i_Buffer].WriteChar('[', M_COLOR_SYMPOL);
	a_Assets_Buffer[i_Buffer].WriteOutput(i_Index,3, M_COLOR_SYMPOL_UPLIGHT);
	a_Assets_Buffer[i_Buffer].WriteChar(']', M_COLOR_SYMPOL);
	mks::console::FileSize(f_Stack->fp_pStack[i_Index].o_Data.nFileSizeLow, M_COLOR_SYMPOL_UPLIGHT, i_Buffer);
	a_Assets_Buffer[i_Buffer].WriteChar(':', M_COLOR_SYMPOL);
	a_Assets_Buffer[i_Buffer].WriteOutput(f_Stack->fp_pStack[i_Index].c_Filename.c_pStr, M_COLOR_FUNCTION_OUTPUT, f_Stack->fp_pStack[i_Index].c_Filename.s_Length);	
	if(f_Stack->fp_pStack[i_Index].o_Data.nFileSizeLow == 0)
		a_Assets_Buffer[i_Buffer].WriteChar('\\', M_COLOR_SYMPOL);
	a_Assets_Buffer[i_Buffer].Break();
}
void __CC
mks::console::DisplayMstStackContent()
{
	for (INT16 i_Index = 0; i_Index < mst_Openfiles.i_Files; i_Index++)
	{
		mks::console::MstFileInfo(i_Index, &mst_Openfiles, M_BUFFER_FEEDBACK);
	}
	a_Assets_Buffer[M_BUFFER_FEEDBACK].WriteBuffer();
}
void __CC
mks::console::DisplayFileStackContent(INT16 i_File)
{
	a_Assets_Buffer[M_BUFFER_MSTFILE].BufferClear();
	a_Assets_Buffer[M_BUFFER_MSTFILE].WriteChar('@', M_COLOR_SYMPOL);
	mks::console::FileSize(mst_Openfiles.mst_pStack[i_File].GetFs(), M_COLOR_SYMPOL_UPLIGHT, M_BUFFER_MSTFILE);
	a_Assets_Buffer[M_BUFFER_MSTFILE].WriteChar(':', M_COLOR_SYMPOL);
	a_Assets_Buffer[M_BUFFER_MSTFILE].WriteOutput(mst_Openfiles.mst_pStack[i_File].fp_Filepath.c_Filename.c_pStr, M_COLOR_FUNCTION_OUTPUT, mst_Openfiles.mst_pStack[i_File].fp_Filepath.c_Filename.s_Length);
	a_Assets_Buffer[M_BUFFER_MSTFILE].Break();
	for (INT16 i_Index = 0; i_Index < mst_Openfiles.mst_pStack[i_File].fs_Filestack.i_Files; i_Index++)
	{
		FileInfo(i_Index, &mst_Openfiles.mst_pStack[i_File].fs_Filestack, M_BUFFER_MSTFILE);
	}
	a_Assets_Buffer[M_BUFFER_MSTFILE].WriteBuffer();
}

void __CC 
mks::console::UpdateStatus()
{
	a_Assets_Buffer[M_BUFFER_PATH].BufferClear();
	a_Assets_Buffer[M_BUFFER_PATH].WriteChar('[', M_COLOR_SYMPOL_UPLIGHT);
	a_Assets_Buffer[M_BUFFER_PATH].WriteOutput(c_WinUsername, M_COLOR_NAME, c_WinUsername.s_Length - 1);
	a_Assets_Buffer[M_BUFFER_PATH].WriteChar(']', M_COLOR_SYMPOL_UPLIGHT);
	p_WorkDirectory.Build(&c_SoftwareDir);
	a_Assets_Buffer[M_BUFFER_PATH].WriteOutput(c_SoftwareDir, M_COLOR_INPUT, c_SoftwareDir.s_Length);
	if (mst_Openfiles.i_Files != 0)
		a_Assets_Buffer[M_BUFFER_PATH].WriteOutput(mst_Openfiles.GetFilestack()->fp_Filepath.c_Filename, M_COLOR_NAME, mst_Openfiles.GetFilestack()->fp_Filepath.c_Filename.s_Length);
	a_Assets_Buffer[M_BUFFER_PATH].WriteBuffer();

	a_Assets_Buffer[M_BUFFER_STATUS].BufferClear();
	a_Assets_Buffer[M_BUFFER_STATUS].WriteOutput((LPSTR)"filestream: ", M_COLOR_SYMPOL_HIGHLIGHT, 12);
	a_Assets_Buffer[M_BUFFER_STATUS].WriteChar('(', M_COLOR_SYMPOL_UPLIGHT);
	a_Assets_Buffer[M_BUFFER_STATUS].WriteOutput(mst_Openfiles.i_Sellected,2, M_COLOR_NAME);
	a_Assets_Buffer[M_BUFFER_STATUS].WriteChar('/', M_COLOR_SYMPOL_UPLIGHT);
	a_Assets_Buffer[M_BUFFER_STATUS].WriteOutput(mst_Openfiles.i_Files,2, M_COLOR_NAME);
	a_Assets_Buffer[M_BUFFER_STATUS].WriteChar(')', M_COLOR_SYMPOL_UPLIGHT);

	if (mst_Openfiles.i_Files != 0) 
	{
		a_Assets_Buffer[M_BUFFER_STATUS].Tab(1);
		a_Assets_Buffer[M_BUFFER_STATUS].WriteChar('@', M_COLOR_SYMPOL);
		a_Assets_Buffer[M_BUFFER_STATUS].Tab(1);
		a_Assets_Buffer[M_BUFFER_STATUS].WriteOutput(mst_Openfiles.GetFilestack()->fp_Filepath.c_Filename, M_COLOR_NAME, mst_Openfiles.GetFilestack()->fp_Filepath.c_Filename.s_Length);		
		a_Assets_Buffer[M_BUFFER_STATUS].Tab(1);
		a_Assets_Buffer[M_BUFFER_STATUS].WriteChar('(', M_COLOR_SYMPOL);
		a_Assets_Buffer[M_BUFFER_STATUS].WriteOutput((LPSTR)"locates:", M_COLOR_SYMPOL_HIGHLIGHT, 8);
		a_Assets_Buffer[M_BUFFER_STATUS].Tab(1);
		a_Assets_Buffer[M_BUFFER_STATUS].WriteOutput(mst_Openfiles.GetFilestack()->fs_Filestack.i_Files,3, M_COLOR_NAME);
		a_Assets_Buffer[M_BUFFER_STATUS].Tab(1);
		a_Assets_Buffer[M_BUFFER_STATUS].WriteOutput((LPSTR)"items", M_COLOR_SYMPOL_HIGHLIGHT, 5);
		a_Assets_Buffer[M_BUFFER_STATUS].WriteChar(')', M_COLOR_SYMPOL);
	}
	a_Assets_Buffer[M_BUFFER_STATUS].WriteBuffer();
}