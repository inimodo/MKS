#include"..\header\s_structs.h"

void __CC
mststack::Open(CSTR* c_pFilename)
{
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