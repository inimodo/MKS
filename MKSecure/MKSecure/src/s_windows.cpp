#include "s_header.h"

mks::cIOBuffer mks_IOBuffer;
mks::cIOSystem mks_IOSystem;

void __CC 
mks::vSetup()
{
	mks_IOBuffer.vLoadHandle();
	mks_IOBuffer.vGetWinUser();
	LOG((LPSTR)mks_IOBuffer.c_LUser);
}
char __CC
mks::vLoop()
{
	mks_IOSystem.vProcessRequest(&mks_IOBuffer.c_RequestEntry);
	return 1;
}
int __CC
mks::vCleanup()
{
	return 1;
}
char __CC
mks::vCatchloop()
{
	mks_IOBuffer.vProcessMsg(mks_IOSystem.dw_Msg);
	mks_IOBuffer.vRequestInput(mks_IOSystem.dw_State);
	return 1;
}