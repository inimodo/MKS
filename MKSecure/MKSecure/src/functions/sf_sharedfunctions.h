#define _MKS_REQ_DATA_ACCESS
#include "..\header\s_functions.h"
#pragma once

namespace encryption
{
	extern char __CC TranslateInt(INT16 i_Value);
	extern INT16 __CC TranslateChar(char c_Char);
	extern INT16 * __CC TranslateKey(CSTR * c_pKey);
	extern void __CC LinkStream(char * c_pStream, INT16 i_Streamlength, INT16 * i_pKey, INT16 i_Keylength, QWORD * i_Offset);
	extern void __CC DeLinkStream(char * c_pStream, INT16 i_Streamlength, INT16 * i_pKey, INT16 i_Keylength, QWORD * i_Offset);
	extern INT16 __CC	EncryptStream(FPATH * fp_pFilepath, INT16 i_SubStreamlength, INT16 * i_pKey, INT16 i_Keylength, QWORD * i_Offset);
	extern INT16 __CC	DecryptStream(FPATH * fp_pFilepath, INT16 i_SubStreamlength, INT16 * i_pKey, INT16 i_Keylength, QWORD * i_Offset);

}
