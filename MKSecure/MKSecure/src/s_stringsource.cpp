#include"s_header.h"

char C_TXT_INPUT_PREFIX = ':'; // $

char C_TXT_OUTPUT_SUFIX = '!'; // $
char C_TXT_INFO_SUFIX = '?'; // $
char C_TXT_INPUT_SUFIX= '$'; // >>175

char C_TXT_FETCH_REQUEST = 64; //@
char C_TXT_DO_REQUEST_START = '['; //!
char C_TXT_DO_REQUEST_STOP= ']'; //!
char C_TXT_REAL_REQUEST = ' ';

char C_TXT_ENDL = '\0';
char C_TXT_NEWL = '\n';

char C_MKSS_E_UNKNOW[_MKSS_MSGSIZE] = "Could not locate Operation";
char C_MKSS_E_PERM[_MKSS_MSGSIZE] = "Not enough Permission";
char C_MKSS_E_ERROR[_MKSS_MSGSIZE] = "Operation could not succeed!";
char C_MKSS_E_GOOD[_MKSS_MSGSIZE] = "Operation was successful";
char C_MKSS_E_UNKNOWF[_MKSS_MSGSIZE] = "Could not locate file";
char C_MKSS_E_KNOWF[_MKSS_MSGSIZE] = "File opened and Executed!";

char C_MKSS_I_RPUSH[_MKSS_REGFUNCTIONSIZE] = "rpush";
char C_MKSS_I_FILER[_MKSS_REGFUNCTIONSIZE] = "filer";


char C_MKSS_K_BREAK[_MKSS_REGFUNCTIONSIZE] = "break"; // Locks System
char C_MKSS_K_LOGIN[_MKSS_REGFUNCTIONSIZE] = "login"; // Unlocks Admin Rights
char C_MKSS_K_LTTRY[_MKSS_REGFUNCTIONSIZE] = "lttry"; // Lists all Buffers if watcher ist enabled
char C_MKSS_K_WKDIR[_MKSS_REGFUNCTIONSIZE] = "wkdir"; // Attaches Buffer to sertain Buffer
char C_MKSS_K_CLEAR[_MKSS_REGFUNCTIONSIZE] = "clear"; // Clears Buffer 
char C_MKSS_K_INPUT[_MKSS_REGFUNCTIONSIZE] = "input"; // Sets register Buffer  
char C_MKSS_K_LSTBF[_MKSS_REGFUNCTIONSIZE] = "lstbf"; // Gets current Buffer index
char C_MKSS_K_CLOSE[_MKSS_REGFUNCTIONSIZE] = "close"; // Closes appliction
char C_MKSS_K_REGST[_MKSS_REGFUNCTIONSIZE] = "regst"; // Closes appliction



