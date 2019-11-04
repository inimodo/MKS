#include "s_header.h"

MKS o_Object;
int main()
{
	if (o_Object.vBuffeWarmup())
	{
		o_Object.vAssetWarmup();
		while (o_Object.b_Register[_MKSR_R_KEEPALIVE])
		{
			o_Object.vInputRoutine();
			o_Object.vFetchInput();
			o_Object.vFetchOutput();
			o_Object.vOutputRoutine();
		} 
	}
	return o_Object.vCleanup();
}
