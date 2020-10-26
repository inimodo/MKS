#include "..\header\s_structs.h"

void __CC
fstack::Push(char * c_pChar, char * c_pFile)
{
	if (this->i_MemSize == this->i_Files) 
	{
		FPATH * v_pPointer = (FPATH*)malloc(sizeof(FPATH)*(this->i_MemSize + 1));
		if (v_pPointer != NULL)
		{
			for (INT16 i_Index = 0; i_Index < this->i_MemSize; i_Index++)
			{
				v_pPointer[i_Index] = this->fp_pStack[i_Index];
			}
			v_pPointer[this->i_MemSize] = FPATH();
			v_pPointer[this->i_MemSize].DisolveFilePath(c_pChar);
			if (c_pFile != NULL)v_pPointer[this->i_MemSize].SetFile(c_pFile);
			this->i_Files++;
			this->i_MemSize++;
			free(this->fp_pStack);
			this->fp_pStack = v_pPointer;
		}
	}
	else if (this->i_MemSize > this->i_Files)
	{
		this->i_Files++;
		this->fp_pStack[this->i_Files - 1] = FPATH();
		this->fp_pStack[this->i_Files - 1].DisolveFilePath(c_pChar);
		if (c_pFile != NULL)this->fp_pStack[this->i_Files - 1].SetFile(c_pFile);
	}
}

void __CC
fstack::Pop(INT16 i_Pos)
{
	this->fp_pStack[i_Pos].Clean();
	this->i_Files--;
	for (INT16 i_Index = i_Pos; i_Index < this->i_Files; i_Index++)
	{
		this->fp_pStack[i_Index] = this->fp_pStack[i_Index + 1];
	}
}

void __CC
fstack::Popall()
{
	for (INT16 i_Index = 0; i_Index < this->i_Files; i_Index++)
	{
		this->fp_pStack[i_Index].Clean();
	}
	this->i_Files = 0;
}


void __CC
fstack::Clean()
{
	for (INT16 i_Index = 0; i_Index < this->i_Files; i_Index++)
	{
		this->fp_pStack[i_Index].Clean();
	}
	this->i_Files = 0;
	this->i_MemSize = 0;
	free(this->fp_pStack);
}

fstack::~fstack()
{
	for (INT16 i_Index = 0; i_Index < this->i_Files; i_Index++)
	{
		this->fp_pStack[i_Index].Clean();
	}
	this->i_Files = 0;
	this->i_MemSize = 0;
	free(this->fp_pStack);
}
