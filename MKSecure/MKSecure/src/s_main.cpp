#include "s_header.h"

int main()
{
	vAssetWarmup();
	vSetup();
	do
	{
		vCatchloop();
	} while (vLoop());
	return vCleanup();
}

IOSYS mks_IOSystem;
SFUNC k_Funclist[_MKSR_REGFUNCTIONS];

void __CC
vSetup()
{
	mks_IOSystem.vSetupBuffer();
	mks_IOSystem.vSetupHandle();
}
char __CC
vCatchloop()
{

	mks_IOSystem.vLoadBuffer();

	return 1;
}
char __CC
vLoop()
{

	mks_IOSystem.vProcessKey();
	mks_IOSystem.vProcessMsg();
	mks_IOSystem.vProcessRawKey();
	return 1;
}
int __CC
vCleanup()
{
	mks_IOSystem.c_LDir.vClean();
	mks_IOSystem.c_LUser.vClean();
	mks_IOSystem.c_RawKey.vClean();

	free(mks_IOSystem.c_pOutputBuffer);
	free(mks_IOSystem.c_pRegisterBuffer);

	return 1;
}


void __ST
vAssetWarmup()
{
	k_Funclist[_MKSS_K_LOCK].f_Register = vRegister_break;
	k_Funclist[_MKSS_K_LOCK].k_Key.c_Key = C_MKSS_K_LOCK;
	k_Funclist[_MKSS_K_LOCK].k_Key.c_Msg_Good = C_MKSS_K_LOCK_GOOD;
	k_Funclist[_MKSS_K_LOCK].k_Key.c_Msg_Failed = C_MKSS_K_LOCK_FAILED;

	k_Funclist[_MKSS_K_LOGGIN].f_Register = vRegister_login;
	k_Funclist[_MKSS_K_LOGGIN].k_Key.c_Key = C_MKSS_K_LOGIN;
	k_Funclist[_MKSS_K_LOGGIN].k_Key.c_Msg_Good = C_MKSS_K_LOGIN_GOOD;
	k_Funclist[_MKSS_K_LOGGIN].k_Key.c_Msg_Failed = C_MKSS_K_LOGIN_FAILED;

	k_Funclist[_MKSS_K_LTTRY].f_Register = vRegister_lttry;
	k_Funclist[_MKSS_K_LTTRY].k_Key.c_Key = C_MKSS_K_LTTRY;
	k_Funclist[_MKSS_K_LTTRY].k_Key.c_Msg_Good = C_MKSS_K_LTTRY_GOOD;
	k_Funclist[_MKSS_K_LTTRY].k_Key.c_Msg_Failed = C_MKSS_K_LTTRY_FAILED;

	k_Funclist[_MKSS_K_WATCH].f_Register = vRegister_watch;
	k_Funclist[_MKSS_K_WATCH].k_Key.c_Key = C_MKSS_K_WATCH;
	k_Funclist[_MKSS_K_WATCH].k_Key.c_Msg_Good = C_MKSS_K_WATCH_GOOD;
	k_Funclist[_MKSS_K_WATCH].k_Key.c_Msg_Failed = C_MKSS_K_WATCH_FAILED;
}