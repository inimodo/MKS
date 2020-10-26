#include "..\header\s_structs.h"
path::path():
	i_Folders(0), c_pFolders(NULL){}
path::path(char* c_pPath, INT16 i_Overshoot) :
	i_Folders(0), c_pFolders(NULL)
{	
	this->DisolvePath(c_pPath, i_Overshoot);
}
path::~path() 
{
	for (INT16 i_Index = 0; i_Index < this->i_Folders; i_Index++)
	{
		this->c_pFolders[i_Index].Clean();
	}
	free(this->c_pFolders);
}
fpath::fpath(char* c_pPath) : 
	c_Filename(CSTR())
{
	this->DisolveFilePath(c_pPath);
}
fpath::fpath() 
{
	c_Filename = CSTR();
}
fpath::~fpath()
{
	c_Filename.Clean();
}
void __CC 
fpath::Clean()
{
	for (INT16 i_Index = 0; i_Index < this->i_Folders; i_Index++)
	{
		this->c_pFolders[i_Index].Clean();
	}
	this->c_Filename.Clean();
	free(this->c_pFolders);	
}
void __CC
path::DisolvePath(char* c_pPath,INT16 i_Overshoot)
{
	INT32 i_InputLength = TermLength(c_pPath), i_FoldersCount = 0;
	if (c_pPath[i_InputLength - 1] != M_BASL)
	{
		c_pPath[i_InputLength] = M_BASL;
	}
	for (INT16 i_Cursor = 0; i_Cursor <i_InputLength + 1; i_Cursor++)
	{
		if (c_pPath[i_Cursor] == M_BASL)i_FoldersCount += 1;
	}
	if (this->c_pFolders != NULL) 
	{
		for (INT16 i_Index = 0; i_Index < this->i_Folders; i_Index++)
		{
			this->c_pFolders[i_Index].Clean();
		}
		free(this->c_pFolders);
		this->c_pFolders = NULL;
	}
	this->c_pFolders = (CSTR*)malloc(sizeof(CSTR)*(i_FoldersCount+ i_Overshoot));
	for (INT16 i_Cursor = 0, i_Start = 0, i_Folder = 0; i_Folder < i_FoldersCount; i_Cursor++)
	{
		if (c_pPath[i_Cursor] == M_BASL)
		{
			this->c_pFolders[i_Folder] = CSTR();
			this->c_pFolders[i_Folder].Set(c_pPath + i_Start, i_Cursor - i_Start);
			i_Start = i_Cursor + 1;
			i_Folder++;
		}
	}
	this->i_Folders = i_FoldersCount;
}
void __CC	
path::Build(CSTR * c_pPath)
{
	c_pPath->Clear();
	for (INT16 i_Folder = 0, i_Offset = 0; i_Folder < this->i_Folders; i_Folder++)
	{
		for (INT16 i_Index = 0; i_Index < this->c_pFolders[i_Folder].s_Length; i_Index++)
		{
			c_pPath->c_pStr[i_Offset + i_Index] = this->c_pFolders[i_Folder].c_pStr[i_Index];
		}
		i_Offset += this->c_pFolders[i_Folder].s_Length;
		c_pPath->c_pStr[i_Offset++] = M_BASL;
		if (i_Folder == this->i_Folders - 1)
		{
			c_pPath->c_pStr[i_Offset] = M_ENDL;
			c_pPath->s_Length = i_Offset;
		}
	}

}

CSTR* __CC
path::BuildWithFile(CSTR * c_pFilename)
{
	CSTR * c_Output = (CSTR*)malloc(sizeof(CSTR));
	if (c_Output == NULL)return NULL;
	*c_Output = CSTR();
	c_Output->Set(MAX_PATH);
	INT16 i_Offset = 0;
	for (INT16 i_Folder = 0; i_Folder < this->i_Folders; i_Folder++)
	{
		for (INT16 i_Index = 0; i_Index < this->c_pFolders[i_Folder].s_Length; i_Index++)
		{
			c_Output->c_pStr[i_Offset + i_Index] = this->c_pFolders[i_Folder].c_pStr[i_Index];
		}
		i_Offset += this->c_pFolders[i_Folder].s_Length;
		c_Output->c_pStr[i_Offset++] = M_BASL;
	}
	for (INT16 i_Index = 0; i_Index < c_pFilename->s_Length; i_Index++)
	{
		c_Output->c_pStr[i_Offset + i_Index] = c_pFilename->c_pStr[i_Index];
	}
	i_Offset += c_pFilename->s_Length;
	c_Output->c_pStr[i_Offset] = M_ENDL;
	c_Output->s_Length = i_Offset;
	return c_Output;
}

CSTR* __CC
path::Build()
{
	CSTR * c_Output = (CSTR*)malloc(sizeof(CSTR));
	if (c_Output == NULL)return NULL;
	*c_Output = CSTR(MAX_PATH);
	for (INT16 i_Folder = 0, i_Offset = 0; i_Folder < this->i_Folders; i_Folder++)
	{
		for (INT16 i_Index = 0; i_Index < this->c_pFolders[i_Folder].s_Length; i_Index++)
		{
			c_Output->c_pStr[i_Offset + i_Index] = this->c_pFolders[i_Folder].c_pStr[i_Index];
		}
		i_Offset += this->c_pFolders[i_Folder].s_Length;
		c_Output->c_pStr[i_Offset++] = M_BASL;
		if (i_Folder == this->i_Folders - 1)
		{
			c_Output->c_pStr[i_Offset] = M_ENDL;
			c_Output->s_Length = i_Offset;
		}
	}
	return c_Output;
}

void __CC 
fpath::BuildFilePath(CSTR * c_pPath)
{
	INT16 i_Offset = 0;
	c_pPath->Set(MAX_PATH);
	for (INT16 i_Folder = 0; i_Folder < this->i_Folders; i_Folder++)
	{
		for (INT16 i_Index = 0; i_Index < this->c_pFolders[i_Folder].s_Length; i_Index++)
		{
			c_pPath->c_pStr[i_Offset + i_Index] = this->c_pFolders[i_Folder].c_pStr[i_Index];
		}
		i_Offset += this->c_pFolders[i_Folder].s_Length;
		c_pPath->c_pStr[i_Offset++] = M_BASL;
	}
	for (INT16 i_Index = 0; i_Index < c_Filename.s_Length; i_Index++)
	{
		c_pPath->c_pStr[i_Offset + i_Index] = c_Filename.c_pStr[i_Index];
	}
	i_Offset += c_Filename.s_Length;
	c_pPath->c_pStr[i_Offset] = M_ENDL;
	LOG(c_pPath->c_pStr);
	STOP;
}

void __CC
fpath::DisolveFilePath(char* c_pPath)
{
	INT32 i_InputLength = TermLength(c_pPath), i_FoldersCount = 0;

	for (INT16 i_Cursor = 0; i_Cursor <i_InputLength + 1; i_Cursor++)
	{
		if (c_pPath[i_Cursor] == M_BASL)i_FoldersCount += 1;
	}
	if (this->c_pFolders != NULL)
	{
		for (INT16 i_Index = 0; i_Index < this->i_Folders; i_Index++)
		{
			this->c_pFolders[i_Index].Clean();
		}
		free(this->c_pFolders);
		this->c_pFolders = NULL;
	}
	this->c_pFolders = (CSTR*)malloc(sizeof(CSTR)*i_FoldersCount);
	INT16 i_Start = 0;
	for (INT16 i_Cursor = 0, i_Folder = 0; i_Folder < i_FoldersCount; i_Cursor++)
	{
		if (c_pPath[i_Cursor] == M_BASL)
		{
			this->c_pFolders[i_Folder] = CSTR();
			this->c_pFolders[i_Folder].Set(c_pPath + i_Start, i_Cursor - i_Start);
			i_Start = i_Cursor + 1;
			i_Folder++;
		}
	}
	c_Filename.Set(c_pPath + i_Start, i_InputLength-i_Start);
	this->i_Folders = i_FoldersCount;
}


void __CC
fpath::SetFile(char* c_pFile)
{
	c_Filename.Set(c_pFile);
}