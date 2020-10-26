
#include"sf_sharedfunctions.h"


char __CC
encryption::TranslateInt(INT16 i_Value)
{
	if (i_Value <= 10)return '0' + i_Value - 1;
	if (i_Value <= 26 + 10)	return 'a' + i_Value - 11;
	if (i_Value <= 26 + 26 + 10)return 'A' + i_Value - 26 - 11;
	return 0;
}

INT16 __CC
encryption::TranslateChar(char c_Char)
{
	if (c_Char <= '9' && c_Char >= '0')return c_Char - '0' + 1;
	if (c_Char <= 'z' && c_Char >= 'a')return c_Char - 'a' + 11;
	if (c_Char <= 'Z' && c_Char >= 'A')return c_Char - 'A' + ('z' - 'a' + 12);
	return 0;
}
INT16 * __CC
encryption::TranslateKey(CSTR * c_pKey)
{
	INT16 * i_Key = (INT16*)malloc(sizeof(INT16)*c_pKey->s_Length);		
	for (INT16 i_Index = 0; i_Index < c_pKey->s_Length; i_Index++)
	{
		i_Key[i_Index] = encryption::TranslateChar(c_pKey->c_pStr[i_Index]);
		if (i_Key[i_Index] == 0) 
		{
			free(i_Key);
			return NULL;
		}
	}
	return i_Key;
}
void __CC
encryption::DeLinkStream(char * c_pStream, INT16 * i_pKey, INT16 i_Keylength, QWORD * i_Offset)
{
	for (int i_StreamIndex = 0; i_StreamIndex < M_FILEBUFFERSIZE; i_StreamIndex++)
	{
		QWORD c_rOffset = 1;
		for (unsigned char c_Layer = 0; c_Layer < i_Keylength - 1; c_Layer++)
		{
			c_rOffset += (QWORD)((QWORD)i_pKey[c_Layer] * (QWORD)c_rOffset + ((QWORD)((QWORD)i_StreamIndex + *i_Offset) * (QWORD)i_pKey[c_Layer + 1]));
			c_rOffset = c_rOffset % 254;
		}
		c_pStream[i_StreamIndex] = (c_pStream[i_StreamIndex] - (unsigned char)((int)c_rOffset - 127) - 127) * -1;
	}

}

void __CC 
encryption::LinkStream(char * c_pStream, INT16 * i_pKey, INT16 i_Keylength, QWORD * i_Offset)
{

	for (int i_StreamIndex = 0; i_StreamIndex < M_FILEBUFFERSIZE; i_StreamIndex++)
	{
		QWORD c_rOffset = 1;
		for (unsigned char c_Layer = 0; c_Layer < i_Keylength - 1; c_Layer++)
		{
			c_rOffset += (QWORD)((QWORD)i_pKey[c_Layer] * (QWORD)c_rOffset + ((QWORD)((QWORD)i_StreamIndex + *i_Offset) * (QWORD)i_pKey[c_Layer + 1]));
			c_rOffset = c_rOffset % 254;
		}
		c_pStream[i_StreamIndex] = ((char)127 - c_pStream[i_StreamIndex]) + (unsigned char)((int)c_rOffset - 127);
	}
}

TMSG __CC
encryption::EncryptStream(FPATH * fp_pFilepath, INT16 * i_pKey, INT16 i_Keylength,QWORD * i_Offset)
{
	CSTR * c_Filepath = fp_pFilepath->BuildWithFile(&fp_pFilepath->c_Filename);
	INT16 i_OriginFile = _sopen(c_Filepath->c_pStr, _O_BINARY, _SH_DENYRW, _S_IREAD);
	if (i_OriginFile == -1)return M_MESSAGES_FILE_FACCESS;

	c_Filepath->Append(M_FILE_KSFILEEX);
	INT16 i_DestinyFile = _sopen(c_Filepath->c_pStr, _O_BINARY | _O_RDWR | _O_CREAT, _SH_DENYRW, _S_IREAD | _S_IWRITE);
	if (i_DestinyFile == -1)return M_MESSAGES_FILE_FACCESS;


	char * c_Buffer = (char*)malloc(M_FILEBUFFERSIZE);
	if (c_Buffer == NULL) 
	{
		return M_MESSAGES_FUNCTION_ERROR;
	}
	QWORD l_ReturnBytes = 0, l_CaughtBytes = 0;

	if(_write(i_DestinyFile,i_Offset,sizeof(QWORD)) == 0)return M_MESSAGES_FILE_FACCESS;


	while (!_eof(i_OriginFile))
	{
		l_ReturnBytes = _read(i_OriginFile, c_Buffer, M_FILEBUFFERSIZE);
		if (l_ReturnBytes == -1)
		{
			_close(i_OriginFile);
			_close(i_DestinyFile);
			free(c_Buffer);
			*i_Offset -= l_CaughtBytes;
			return M_MESSAGES_FILE_READF;
		}
		encryption::LinkStream(c_Buffer, i_pKey, i_Keylength, i_Offset);

		if (_write(i_DestinyFile, c_Buffer, l_ReturnBytes) == -1)
		{
			_close(i_OriginFile);
			_close(i_DestinyFile);
			free(c_Buffer);
			*i_Offset -= l_CaughtBytes;
			return M_MESSAGES_FILE_WRITEF;
		}
		l_CaughtBytes += l_ReturnBytes;
		*i_Offset += l_ReturnBytes;
	}

	free(c_Buffer);
	_close(i_OriginFile);
	_close(i_DestinyFile);
	c_Filepath->Clean();
	free(c_Filepath);

	return M_MESSAGES_FILE_OKAY;
}

TMSG __CC
encryption::DecryptStream(FPATH * fp_pFilepath, INT16 * i_pKey, INT16 i_Keylength, QWORD * i_Offset)
{
	CSTR * c_Filepath = fp_pFilepath->BuildWithFile(&fp_pFilepath->c_Filename);
	INT16 i_DestinyFile = _sopen(c_Filepath->c_pStr, _O_BINARY | _O_RDWR | _O_CREAT, _SH_DENYRW, _S_IREAD | _S_IWRITE);
	if (i_DestinyFile == -1)return M_MESSAGES_FILE_FACCESS;

	c_Filepath->Append(M_FILE_KSFILEEX);
	INT16 i_OriginFile = _sopen(c_Filepath->c_pStr, _O_BINARY, _SH_DENYRW, _S_IREAD);
	if (i_OriginFile == -1)return M_MESSAGES_FILE_FACCESS;

	char * c_Buffer = (char*)malloc(M_FILEBUFFERSIZE);
	if (c_Buffer == NULL)
	{
		return M_MESSAGES_FUNCTION_ERROR;
	}
	QWORD l_ReturnBytes = 0, l_CaughtBytes = 0;

	QWORD i_FileOffset = 0;
	if (_read(i_OriginFile, &i_FileOffset, sizeof(QWORD)) == 0)return M_MESSAGES_FILE_FACCESS;

	while (!_eof(i_OriginFile))
	{
		l_ReturnBytes = _read(i_OriginFile, c_Buffer, M_FILEBUFFERSIZE);
		if (l_ReturnBytes == -1)
		{
			_close(i_OriginFile);
			_close(i_DestinyFile);
			free(c_Buffer);
			*i_Offset -= l_CaughtBytes;
			return M_MESSAGES_FILE_READF;
		}
		encryption::DeLinkStream(c_Buffer, i_pKey, i_Keylength, &i_FileOffset);
		if (_write(i_DestinyFile, c_Buffer, l_ReturnBytes) == -1)
		{
			_close(i_OriginFile);
			_close(i_DestinyFile);
			free(c_Buffer);
			*i_Offset -= l_CaughtBytes;
			return M_MESSAGES_FILE_WRITEF;
		}
		i_FileOffset += l_ReturnBytes;
		l_CaughtBytes += l_ReturnBytes;
	}

	free(c_Buffer);
	_close(i_OriginFile);
	_close(i_DestinyFile);
	return M_MESSAGES_FILE_OKAY;
}
TMSG __CC
encryption::RequestMSTOpen(CSTR * c_pQuerry)
{
	if (c_pQuerry->c_pStr[0] == M_KW_SELLECT)
	{
		INT16 i_Selected = StringToInt(c_pQuerry->c_pStr + 1, c_pQuerry->s_Length - 1);
		if (i_Selected >= 0 && i_Selected < mst_Openfiles.i_Files)
		{
			if (mst_Openfiles.mst_pStack[i_Selected].Load() == -1)
			{
				return M_MESSAGES_FUNCTION_LOAD_ERROR;
			}
			mst_Openfiles.i_Sellected = i_Selected;
		}
		else return M_MESSAGES_FUNCTION_PARAMETER;
	}
	else
	{
		CSTR * c_AbsoluteFilepath = p_WorkDirectory.BuildWithFile(c_pQuerry);
		c_AbsoluteFilepath->Append(M_FILE_STFILEEX);
		mst_Openfiles.Open(c_AbsoluteFilepath);
		if (mst_Openfiles.GetFilestack()->Load() == -1)
		{
			return M_MESSAGES_FUNCTION_LOAD_ERROR;
		}
		c_AbsoluteFilepath->Clean();
		free(c_AbsoluteFilepath);
	}
	return M_MESSAGES_FILE_OKAY;
}
void __CC
encryption::AddFileToMST(CSTR * c_pPath ,WIN32_FIND_DATA * o_pData)
{
	mst_Openfiles.GetFilestack()->fs_Filestack.Push(c_pPath->c_pStr, o_pData->cFileName);
	mst_Openfiles.GetFilestack()->fs_Filestack.fp_pStack[mst_Openfiles.GetFilestack()->fs_Filestack.i_Files - 1].o_Data = *o_pData;
}