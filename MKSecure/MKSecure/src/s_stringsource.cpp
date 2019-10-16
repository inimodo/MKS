#include"s_header.h"

char C_TXT_PREFIX = '@';
char C_TXT_WRONGPWD[] = "INVALID KEY\0";
char C_TXT_REQUESTPWD[] = "KEY REQUEST\0";
char C_TXT_IN = '<';
char C_TXT_OUT = '>';
char C_TXT_KNOWN = '_';
char C_TXT_SPACER = '-';
char C_TXT_ENDL = '\0';
char C_FILE[] = "cfile.key";

char C_MKSS_LOCK[_MKSS_KEYSIZE] = "lock ";
char C_MKSS_LOCK_FAILED[_MKSS_MSGSIZE] = "ALREADY LOCKED ";
char C_MKSS_LOCK_GOOD[_MKSS_MSGSIZE] = "SYSTEM LOCKED  ";

char C_MKSS_LOGIN[_MKSS_KEYSIZE] = "login";
char C_MKSS_LOGIN_FAILED[_MKSS_MSGSIZE] = "INVALID KEY    " ;
char C_MKSS_LOGIN_GOOD[_MKSS_MSGSIZE] = "VALID LOGIN    ";

char C_MKSS_LTTRY[_MKSS_KEYSIZE] = "lttry";
char C_MKSS_LTTRY_FAILED[_MKSS_MSGSIZE] = "OFFLINE WATCHER";
char C_MKSS_LTTRY_GOOD[_MKSS_MSGSIZE] = "VALID REQUEST  ";

char C_MKSS_WATCH[_MKSS_KEYSIZE] = "watch";
char C_MKSS_WATCH_FAILED[_MKSS_MSGSIZE] = "WATCHER ONLINE ";
char C_MKSS_WATCH_GOOD[_MKSS_MSGSIZE] = "WATCHER INVALID";

void __ST 
vAssetWarmup()
 {
	 k_Keylist[_MKSS_LOCK].c_Key = C_MKSS_LOCK;
	 k_Keylist[_MKSS_LOCK].c_Msg_Good = C_MKSS_LOCK_GOOD;
	 k_Keylist[_MKSS_LOCK].c_Msg_Failed = C_MKSS_LOCK_FAILED;

	 k_Keylist[_MKSS_LOGGIN].c_Key = C_MKSS_LOGIN;
	 k_Keylist[_MKSS_LOGGIN].c_Msg_Good = C_MKSS_LOGIN_GOOD;
	 k_Keylist[_MKSS_LOGGIN].c_Msg_Failed = C_MKSS_LOGIN_FAILED;

	 k_Keylist[_MKSS_LTTRY].c_Key = C_MKSS_LTTRY;
	 k_Keylist[_MKSS_LTTRY].c_Msg_Good = C_MKSS_LTTRY_GOOD;
	 k_Keylist[_MKSS_LTTRY].c_Msg_Failed = C_MKSS_LTTRY_FAILED;

	 k_Keylist[_MKSS_WATCH].c_Key = C_MKSS_WATCH;
	 k_Keylist[_MKSS_WATCH].c_Msg_Good = C_MKSS_WATCH_GOOD;
	 k_Keylist[_MKSS_WATCH].c_Msg_Failed = C_MKSS_WATCH_FAILED;
 }