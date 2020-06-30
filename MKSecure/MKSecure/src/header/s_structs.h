#pragma once

#include "s_includes.h"

/*
Contains all Structs an Class DefINT32ionss
*/


#define __CC __stdcall
#define __ST __cdecl
#define __REG register


typedef const LPSTR CLPSTR; 
typedef void* ARGT;
typedef INT16 TMSG;
typedef unsigned long long int QWORD;

typedef class str
{
public:
	str(CLPSTR);
	str();
	str(INT16);
	~str();
	INT16		s_Length{ 0 };
	INT16		s_MemLen{ 0 };
	LPSTR		c_pStr{ 0 };

	void __CC	Set(CLPSTR);
	void __CC	Set(str);
	void __CC	Set(INT16);
	void __CC	Set(LPSTR , INT16 );
	void __CC	Set(LPSTR, INT16, INT16);
	void __CC	Copy(str * c_pRef);
	void __CC	CopyAll(str * c_pRef);
	void __CC	Clean();
	void __CC	Clear();

	void __CC	ToString(DWORD i_Value, INT16 i_Digits);

	void __CC	Append(str*);
	void __CC	Append(str);
	void __CC	Append(CLPSTR);
	INT16 __CC	MeasureLength();
	INT16 __CC	ToInt(INT16 i_Offset = 0);

	operator INT16() {
		return s_Length;
	}
	operator LPSTR() {
		return c_pStr;
	}
}CSTR;


typedef class buffer {
	WORD i_Backcolor;
public:
	CHAR_INFO * c_pBuffer;
	COORD		i_Size, i_Cursor, i_Pos;
	static HANDLE	o_Output;
	SMALL_RECT	sm_Rect;

	BOOL __CC	Setup(COORD i_Loc, COORD i_Dim, WORD i_Backcolor);
	void __CC	Cleanup();

	BOOL __CC	WriteOutput(LPSTR c_pMsg, WORD w_Color, INT16 i_Length );
	BOOL __CC	WriteOutput(LPSTR c_pMsg, WORD w_Color);
	BOOL __CC	WriteOutput(DWORD i_Value, INT16 i_Digits, WORD w_Color);

	BOOL __CC	WriteChar(CHAR c_Msg, WORD w_Color, BOOL b_Add = TRUE);

	BOOL __CC	ReadInput(CSTR*, INT32 *, WORD);
	BOOL __CC	ReadInput(CSTR*, INT32 *, WORD, CHAR);

	BOOL __CC	WriteBuffer();
	void __CC	Break();
	void __CC	Tab(INT32);
	void __CC	BufferClear();
	void __CC	SetCursor(COORD);
	void __CC	SetCursor(INT32, INT32);
}BUFFER;

typedef struct buffer_info {
	COORD i_Pos, i_Size;
	WORD i_Color;
}BUFFER_INFO;

typedef struct branch
{
	INT32		i_Key;
	branch*		b_ArgBuf[M_FUNC_ARGS];
	CSTR		a_Args[M_FUNC_ARGS];
	CSTR		a_ArgBufReturn;
}BRANCH;

typedef  TMSG(*FUNC)(BRANCH*);
typedef struct func
{
	char		c_Arguments, c_Return;
	char*		c_Name;
	FUNC f_Function;
}SFUNC;

typedef class path
{
public:
	~path();
	path(char* c_pPath, INT16 i_Overshoot = 0);
	path();
	CSTR * c_pFolders;
	INT16 i_Folders;

	void __CC	DisolvePath(char* c_pPath, INT16 i_Overshoot = 0);
	void __CC	Build(CSTR * c_pPath);
	CSTR* __CC	Build();
	CSTR* __CC	BuildWithFile(CSTR * c_pFilename);
} PATH;


typedef class fpath : public path
{
public:
	~fpath();
	fpath(char* c_pPath);
	fpath();

	CSTR  c_Filename;
	WIN32_FIND_DATA o_Data;

	void __CC	Clean();
	void __CC	SetFile(char* c_pFile);
	void __CC	DisolveFilePath(char* c_pPath);
	void  __CC	BuildFilePath(CSTR * c_pPath) ;

} FPATH;

typedef class fstack 
{
public: 
	~fstack();

	FPATH * fp_pStack;
	INT16 i_MemSize{0}, i_Files{ 0 };

	void __CC Push(char * c_pChar, char * c_pFile = NULL);
	void __CC Pop(INT16 i_Index);
	void __CC Popall();
	void __CC Clean();
}FSTACK;

typedef class mstfile
{
	INT32	i_FileDescriptor;
	INT32	i_FileSize;
public:
	FPATH	fp_Filepath;
	FSTACK	fs_Filestack;

	INT32 __CC	Load();
	INT32 __CC	Save();
	BOOL __CC	Open(CSTR* c_pFilename);
	void __CC	Close();
	INT32 __CC	GetFd();
	INT32 __CC	GetFs();

} MSTFILE;

typedef class mststack
{
public:
	~mststack();

	MSTFILE * mst_pStack;
	INT16 i_MemSize{ 0 }, i_Files{ 0 }, i_Sellected{0};

	void __CC Open(CSTR* c_pFilename);
	void __CC Close(INT16 i_Index);
	void __CC Closeall();
	INT16 __CC IsOpen(CSTR * c_pFilename);

	MSTFILE* __CC GetFilestack(INT16 i_Index = -1);
}MSTSTACK;


extern inline INT32 __CC TermLength(CLPSTR);
extern inline INT32 __CC Tenth(char);
extern inline INT32 __CC StringToInt(CSTR, INT32);
extern inline INT32 __CC StringToInt(CSTR, INT32, INT32);
extern void __CC IntToString(INT32, CSTR *);
