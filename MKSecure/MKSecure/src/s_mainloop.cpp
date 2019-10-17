#include "s_header.h"

cIOSystem mks_IOSystem;


void __CC 
vSetup()
{
	mks_IOSystem.vSetupBuffer();

	mks_IOSystem.vLoadHandle();
	mks_IOSystem.vGetWinUser();
	mks_IOSystem.vGetWinDir();


	LOG((LPSTR)mks_IOSystem.c_LUser);
	LOG((LPSTR)mks_IOSystem.c_LDir);
}
char __CC
vCatchloop()
{
	mks_IOSystem.vProcessRawKey();
	return 1;
}
char __CC
vLoop()
{
	mks_IOSystem.vProcessKey();
	mks_IOSystem.vProcessMsg();
	return 1;
}
int __CC
vCleanup()
{
	mks_IOSystem.c_LDir.vClean();
	mks_IOSystem.c_LUser.vClean();
	mks_IOSystem.c_RawKey.vClean();
	return 1;
}

SFUNC k_Funclist[_MKSS_REGFUNCTIONS];
SKEY k_Keylist[_MKSS_REGFUNCTIONS];
void __ST
vAssetWarmup()
{
	k_Keylist[_MKSS_K_LOCK].c_Key = C_MKSS_K_LOCK;
	k_Keylist[_MKSS_K_LOCK].c_Msg_Good = C_MKSS_K_LOCK_GOOD;
	k_Keylist[_MKSS_K_LOCK].c_Msg_Failed = C_MKSS_K_LOCK_FAILED;

	k_Keylist[_MKSS_K_LOGGIN].c_Key = C_MKSS_LOGIN;
	k_Keylist[_MKSS_K_LOGGIN].c_Msg_Good = C_MKSS_LOGIN_GOOD;
	k_Keylist[_MKSS_K_LOGGIN].c_Msg_Failed = C_MKSS_LOGIN_FAILED;

	k_Keylist[_MKSS_K_LTTRY].c_Key = C_MKSS_K_LTTRY;
	k_Keylist[_MKSS_K_LTTRY].c_Msg_Good = C_MKSS_K_LTTRY_GOOD;
	k_Keylist[_MKSS_K_LTTRY].c_Msg_Failed = C_MKSS_K_LTTRY_FAILED;

	k_Keylist[_MKSS_K_WATCH].c_Key = C_MKSS_K_WATCH;
	k_Keylist[_MKSS_K_WATCH].c_Msg_Good = C_MKSS_K_WATCH_GOOD;
	k_Keylist[_MKSS_K_WATCH].c_Msg_Failed = C_MKSS_K_WATCH_FAILED;
}