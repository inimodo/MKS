#include "..\header\s_structs.h"

INT32 __CC
mstfile::Load()
{
	if (this->i_FileDescriptor != -1)
	{
		this->i_FileSize = 0;
		_lseek(this->i_FileDescriptor, 0L, SEEK_SET);
		this->i_FileSize += _read(this->i_FileDescriptor, &this->fs_Filestack.i_Files, sizeof(INT16));
		this->fs_Filestack.fp_pStack = (FPATH*)malloc(sizeof(FPATH)* this->fs_Filestack.i_Files);
		this->fs_Filestack.i_MemSize = this->fs_Filestack.i_Files;
		for (INT16 i_Index = 0; i_Index < this->fs_Filestack.i_Files; i_Index++)
		{
			this->fs_Filestack.fp_pStack[i_Index] = FPATH();
			this->i_FileSize += _read(this->i_FileDescriptor, &this->fs_Filestack.fp_pStack[i_Index].i_Folders, sizeof(INT16));
			this->fs_Filestack.fp_pStack[i_Index].c_pFolders = (CSTR*)malloc(sizeof(CSTR)*this->fs_Filestack.fp_pStack[i_Index].i_Folders);
			for (INT16 i_FolderIndex = 0; i_FolderIndex < this->fs_Filestack.fp_pStack[i_Index].i_Folders; i_FolderIndex++)
			{
				this->fs_Filestack.fp_pStack[i_Index].c_pFolders[i_FolderIndex] = CSTR();
				this->fs_Filestack.fp_pStack[i_Index].c_pFolders[i_FolderIndex].Set(MAX_PATH);
				this->i_FileSize += _read(this->i_FileDescriptor, this->fs_Filestack.fp_pStack[i_Index].c_pFolders[i_FolderIndex].c_pStr, MAX_PATH);
			}
			this->fs_Filestack.fp_pStack[i_Index].c_Filename.Set(MAX_PATH);
			this->i_FileSize += _read(this->i_FileDescriptor, this->fs_Filestack.fp_pStack[i_Index].c_Filename, MAX_PATH);
			this->fs_Filestack.fp_pStack[i_Index].c_Filename.s_Length = this->fs_Filestack.fp_pStack[i_Index].c_Filename.MeasureLength();
			this->i_FileSize += _read(this->i_FileDescriptor, &this->fs_Filestack.fp_pStack[i_Index].o_Data, sizeof(WIN32_FIND_DATA));
		}
		return this->i_FileSize;
	}
	return -1;
}

INT32 __CC 
mstfile::Save()
{
	if (this->i_FileDescriptor != -1) 
	{
		this->i_FileSize = 0;
		_lseek(this->i_FileDescriptor, 0L, SEEK_SET);
		this->i_FileSize+=_write(this->i_FileDescriptor, &this->fs_Filestack.i_Files, sizeof(INT16));
		for (INT16 i_Index = 0; i_Index < this->fs_Filestack.i_Files; i_Index++)
		{
			this->i_FileSize += _write(this->i_FileDescriptor, &this->fs_Filestack.fp_pStack[i_Index].i_Folders, sizeof(INT16));
			for (INT16 i_FolderIndex = 0; i_FolderIndex < this->fs_Filestack.fp_pStack[i_Index].i_Folders; i_FolderIndex++)
			{
				this->i_FileSize += _write(this->i_FileDescriptor, this->fs_Filestack.fp_pStack[i_Index].c_pFolders[i_FolderIndex].c_pStr, MAX_PATH);
			}
			this->i_FileSize += _write(this->i_FileDescriptor, this->fs_Filestack.fp_pStack[i_Index].c_Filename, MAX_PATH);
			this->i_FileSize += _write(this->i_FileDescriptor, &this->fs_Filestack.fp_pStack[i_Index].o_Data, sizeof(WIN32_FIND_DATA));
		}
		return this->i_FileSize;
	}
	return -1;
}

BOOL __CC 
mstfile::Open(CSTR * c_pFilename)
{
	this->i_FileDescriptor = _sopen(c_pFilename->c_pStr, _O_BINARY | _O_RDWR | _O_CREAT, _SH_DENYRW, _S_IREAD | _S_IWRITE);
	if (i_FileDescriptor == -1) 
	{
		return FALSE;
	}
	this->fp_Filepath.DisolveFilePath(c_pFilename->c_pStr);

	return TRUE;
}

void __CC 
mstfile::Close()
{
	_close(this->i_FileDescriptor);
}
INT32 __CC
mstfile::GetFd() 
{
	return this->i_FileDescriptor;
}
INT32 __CC
mstfile::GetFs()
{
	return this->i_FileSize;
}
