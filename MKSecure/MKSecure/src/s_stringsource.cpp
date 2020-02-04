#include"s_header.h"

char C_TXT_INPUT_PREFIX = 175; // $
char C_TXT_INPUT_SUFIX= 36; // >>

char C_TXT_FETCH_ARGUMENT = 34; // "
char C_TXT_FETCH_REQUEST = 64; //@

char C_TXT_ENDL = '\0';
char C_TXT_NEWL = '\n';

char C_MKSS_E_UNKNOW[_MKSS_MSGSIZE] = "REGISTER NOT FOUND";
char C_MKSS_E_PERM[_MKSS_MSGSIZE] = "INVALID PERMSSION";
char C_MKSS_E_ERROR[_MKSS_MSGSIZE] = "INVALID OPERATION";
char C_MKSS_E_GOOD[_MKSS_MSGSIZE] = "OPERATION FINISHED";


char C_MKSS_K_BREAK[_MKSS_REGFUNCTIONSIZE] = "break"; // Locks System
char C_MKSS_K_LOGIN[_MKSS_REGFUNCTIONSIZE] = "login"; // Unlocks Admin Rights
char C_MKSS_K_LTTRY[_MKSS_REGFUNCTIONSIZE] = "lttry"; // Lists all Buffers if watcher ist enabled
char C_MKSS_K_WATCH[_MKSS_REGFUNCTIONSIZE] = "watch"; // Attaches Buffer to sertain Buffer
char C_MKSS_K_CLEAR[_MKSS_REGFUNCTIONSIZE] = "clear"; // Clears Buffer 
char C_MKSS_K_INPUT[_MKSS_REGFUNCTIONSIZE] = "input"; // Sets register Buffer  
char C_MKSS_K_LSTBF[_MKSS_REGFUNCTIONSIZE] = "lstbf"; // Gets current Buffer index
char C_MKSS_K_CLOSE[_MKSS_REGFUNCTIONSIZE] = "close"; // Closes appliction
char C_MKSS_K_REGST[_MKSS_REGFUNCTIONSIZE] = "regst"; // Closes appliction



