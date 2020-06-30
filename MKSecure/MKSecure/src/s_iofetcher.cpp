#define _MKS_REQ_DATA_ACCESS
#define _MKS_REQ_CONSOLE_ACCESS
#include "header\s_functions.h"

//Sytem



BOOL __CC
mks::system::GetFunctionId(CSTR* c_InputRegister,INT32 i_Offset)
{
	INT32 i_TempSu = 0;
	for (INT16 s_KeyIndex = 0; s_KeyIndex < M_FUNC_COUNT; s_KeyIndex++)
	{
		i_TempSu = 0;
		for (INT16 s_Index = 0; s_Index < M_FUNC_KWLENRAW; s_Index++)
		{
			if (c_InputRegister->c_pStr[s_Index + i_Offset] == a_Assets_Functions[s_KeyIndex].c_Name[s_Index])
			{
				i_TempSu += 1;
			}
			else
			{
				continue;
			}
		}
		if (i_TempSu == M_FUNC_KWLENRAW)
		{
			return s_KeyIndex;
		}
	}
	return -1;
}
BOOL __CC 
mks::system::CreateBranch(CSTR * c_InputRegister,INT32 i_StartIndex,INT32 i_EndIndex,BRANCH * b_pBranch)
{
	b_pBranch->i_Key = GetFunctionId(c_InputRegister,i_StartIndex);
	if (b_pBranch->i_Key == -1)return FALSE;
	if (a_Assets_Functions[b_pBranch->i_Key].c_Arguments == 0)return TRUE;

	for (INT16 i_Index = 0; i_Index < a_Assets_Functions[b_pBranch->i_Key].c_Arguments; i_Index++)
	{
		b_pBranch->a_Args[i_Index] = CSTR();
	}

	INT32 i_CursorIndex = M_FUNC_KWLENRAW + i_StartIndex, i_Deltacursor = 0, i_ArgIndex = 0;
	for ( ; i_CursorIndex < i_StartIndex+ i_EndIndex && i_ArgIndex < a_Assets_Functions[b_pBranch->i_Key].c_Arguments; i_CursorIndex++, i_Deltacursor = 0)
	{		
		if (c_InputRegister->c_pStr[i_CursorIndex] == M_KW_STARTFUNC)
		{
			i_CursorIndex++;
			for (i_Deltacursor = 1; i_Deltacursor < c_InputRegister->s_Length - i_CursorIndex; i_Deltacursor++)
			{
				if (c_InputRegister->c_pStr[i_CursorIndex + i_Deltacursor] == M_KW_STOPFUNC)
				{
					break;
				}
			}
			b_pBranch->b_ArgBuf[i_ArgIndex] = (BRANCH*)malloc(sizeof(BRANCH));
			if (b_pBranch->b_ArgBuf[i_ArgIndex] == NULL)
			{
				return FALSE;
			} 

			if (mks::system::CreateBranch(c_InputRegister, i_CursorIndex, i_Deltacursor, b_pBranch->b_ArgBuf[i_ArgIndex]) == FALSE) 
			{
				free(b_pBranch->b_ArgBuf[i_ArgIndex]);
				i_ArgIndex--;
			}
			i_ArgIndex++;
			continue;
		}else if (c_InputRegister->c_pStr[i_CursorIndex] == M_KW_WILDCARD)
		{
			i_CursorIndex++;

			if (c_InputRegister->c_pStr[i_CursorIndex] == M_KW_WILDCARD) 
			{
				b_pBranch->b_ArgBuf[i_ArgIndex] = NULL;
				b_pBranch->a_Args[i_ArgIndex].Set(c_InputRegister->c_pStr + i_CursorIndex, 1);

				i_CursorIndex++;
				i_ArgIndex++;
				continue;
			}

			for (i_Deltacursor = 1; i_Deltacursor < (c_InputRegister->s_Length - i_CursorIndex); i_Deltacursor++)
			{
				if (c_InputRegister->c_pStr[i_CursorIndex + i_Deltacursor] <= M_KW_SPACE ||
					c_InputRegister->c_pStr[i_CursorIndex + i_Deltacursor] == M_KW_WILDCARD ||
					c_InputRegister->c_pStr[i_CursorIndex + i_Deltacursor] == M_KW_STARTFUNC)
				{
					break;
				}
			}

			if (c_InputRegister->c_pStr[i_CursorIndex] == M_KW_SELLECT)
			{
				b_pBranch->b_ArgBuf[i_ArgIndex] = NULL;
				b_pBranch->a_Args[i_ArgIndex].Set(c_InputRegister->c_pStr + i_CursorIndex, i_Deltacursor);

				i_CursorIndex += i_Deltacursor - 1;

				i_ArgIndex++;
				continue;
			}

			b_pBranch->b_ArgBuf[i_ArgIndex] = NULL;
			b_pBranch->a_Args[i_ArgIndex].Set(c_InputRegister->c_pStr+ i_CursorIndex, i_Deltacursor);

			i_CursorIndex += i_Deltacursor-1;
			i_ArgIndex++;
			continue;			
		}		
	}
	if (i_ArgIndex != a_Assets_Functions[b_pBranch->i_Key].c_Arguments) 
	{
		return FALSE;
	}
	return TRUE;
}
void __CC 
mks::system::InvokeFunctioncall(BRANCH * b_pBranch)
{
	FuncHeader(b_pBranch);
	FuncFeedback(a_Assets_Functions[b_pBranch->i_Key].f_Function(b_pBranch),b_pBranch);
}
void __CC 
mks::system::FetchBranch(BRANCH * b_pBranch)
{
	for (INT32 i_Fetches = 0; i_Fetches < a_Assets_Functions[b_pBranch->i_Key].c_Arguments; i_Fetches++)
	{
		if (b_pBranch->b_ArgBuf[i_Fetches] != NULL)
		{	
			mks::system::FetchBranch(b_pBranch->b_ArgBuf[i_Fetches]);
			b_pBranch->a_Args[i_Fetches].Copy(&b_pBranch->b_ArgBuf[i_Fetches]->a_ArgBufReturn);
			b_pBranch->b_ArgBuf[i_Fetches]->a_ArgBufReturn.Clean();
			free(b_pBranch->b_ArgBuf[i_Fetches]);		
		}
	}
	mks::system::InvokeFunctioncall(b_pBranch);
	for (INT32 i_Index = 0; i_Index < a_Assets_Functions[b_pBranch->i_Key].c_Arguments; i_Index++)
	{
		b_pBranch->a_Args[i_Index].Clean();
	}
	b_pBranch->i_Key = -1;
}
BOOL __CC
mks::system::FetchPath(CSTR* c_InputRegister)
{
	if (TermLength(c_InputRegister->c_pStr) == 1)return M_MESSAGES_FOLDER_UNKOW;
	if (c_InputRegister->c_pStr[1] == M_KW_WILDCARD)
	{
		p_WorkDirectory.DisolvePath(c_InputRegister->c_pStr + 2);
		return M_MESSAGES_FOLDER_OKAY;
	}
	PATH p_Querryentry(c_InputRegister->c_pStr + 1, 0);
	INT16 i_Downs = 0, i_Total, i_Overshoot = 0;
	for (INT16 i_Folder = 0; i_Folder < p_Querryentry.i_Folders; i_Folder++)
	{
		if (p_Querryentry.c_pFolders[i_Folder].s_Length == 2 &&
			p_Querryentry.c_pFolders[i_Folder].c_pStr[0] == '.' &&
			p_Querryentry.c_pFolders[i_Folder].c_pStr[1] == '.')
		{
			i_Downs++;
		}
		else
		{
			break;
		}
	}
	i_Total = (p_Querryentry.i_Folders - i_Downs) - i_Downs;
	if (i_Total > 0)i_Overshoot = i_Total;

	p_WorkDirectory.Build(&c_SoftwareDir);
	p_WorkDirectory.DisolvePath(c_SoftwareDir.c_pStr, i_Overshoot);

	if (!(p_WorkDirectory.i_Folders <= i_Downs)) {
		for (INT16 i_Folder = 0; i_Folder < p_Querryentry.i_Folders - i_Downs; i_Folder++)
		{
			if ((i_Folder + p_WorkDirectory.i_Folders - i_Downs) > p_WorkDirectory.i_Folders - 1)
				p_WorkDirectory.c_pFolders[i_Folder + p_WorkDirectory.i_Folders - i_Downs] = CSTR();
			p_WorkDirectory.c_pFolders[i_Folder + p_WorkDirectory.i_Folders - i_Downs].Set(
				p_Querryentry.c_pFolders[i_Downs + i_Folder].c_pStr,
				p_Querryentry.c_pFolders[i_Downs + i_Folder].s_Length
			);
		}
		p_WorkDirectory.i_Folders += i_Total;
		return M_MESSAGES_FOLDER_OKAY;
	}
	return M_MESSAGES_FOLDER_ERROR;
}