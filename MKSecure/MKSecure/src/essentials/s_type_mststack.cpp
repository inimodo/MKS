#include"..\header\s_structs.h"

void __CC
mststack::Open(CSTR* c_pFilename)
{

	INT16 i_MatchIndex = this->FindFileId(c_pFilename);
	if (i_MatchIndex != -1) 
	{
		this->i_Sellected = i_MatchIndex;
		return;
	}
	if (this->i_MemSize == this->i_Files)
	{
		MSTFILE * v_pPointer = (MSTFILE*)malloc(sizeof(MSTFILE)*(this->i_MemSize + 1));
		if (v_pPointer != NULL)
		{
			for (INT16 i_Index = 0; i_Index < this->i_MemSize; i_Index++)
			{
				v_pPointer[i_Index] = this->mst_pStack[i_Index];
			}
			v_pPointer[this->i_MemSize] = MSTFILE();
			v_pPointer[this->i_MemSize].Open(c_pFilename);
			this->i_Files++;
			this->i_MemSize++;
			this->i_Sellected = this->i_Files - 1;
			free(this->mst_pStack);
			this->mst_pStack = v_pPointer;
		}
	}
	else if (this->i_MemSize > this->i_Files)
	{
		this->i_Files++;
		this->i_Sellected = this->i_Files - 1;
		this->mst_pStack[this->i_Files - 1] = MSTFILE();
		this->mst_pStack[this->i_Files - 1].Open(c_pFilename);
	}
}

MSTFILE* __CC
mststack::GetFilestack(INT16 i_Index) 
{
	if (i_Index <= -1)return &this->mst_pStack[this->i_Sellected];
	else return &this->mst_pStack[i_Index];

}
void __CC
mststack::Close(INT16 i_Pos)
{

	if (i_Pos == this->i_Sellected && this->i_Files != 0) 
	{
		this->i_Sellected--;
	}

	this->mst_pStack[i_Pos].Close();

	for (INT16 i_Index = i_Pos; i_Index < this->i_Files - 1; i_Index++)
	{
		this->mst_pStack[i_Index] = this->mst_pStack[i_Index + 1];
	}
	this->i_Files--;
}

void __CC
mststack::Closeall()
{
	for (INT16 i_Index = 0; i_Index < this->i_Files; i_Index++)
	{
		this->mst_pStack[i_Index].Close();
	}
	this->i_Files = 0;
}
mststack::~mststack()
{
	for (INT16 i_Index = 0; i_Index < this->i_Files; i_Index++)
	{
		this->mst_pStack[i_Index].Close();
	}
	this->i_Files = 0;
}
INT16 __CC 
mststack::FindFileId(CSTR* c_pFilename)
{
	for (INT16 i_FileIndex = 0; i_FileIndex < this->i_Files; i_FileIndex++)
	{
		CSTR * c_Filepath = this->mst_pStack[i_FileIndex].fp_Filepath.BuildWithFile(&this->mst_pStack[i_FileIndex].fp_Filepath.c_Filename);
		if (c_Filepath->s_Length != c_pFilename->s_Length)continue;
		for (INT16 i_CharIndex = 0,i_MatchCount = 0; i_CharIndex < c_pFilename->s_Length; i_CharIndex++)
		{
			if (c_Filepath->c_pStr[i_CharIndex] == c_pFilename->c_pStr[i_CharIndex])i_MatchCount++;
			else break;
			if (i_MatchCount == c_pFilename->s_Length-1)return i_FileIndex;
		}
		c_Filepath->Clean();
		free(c_Filepath);
	}
	return -1;
}