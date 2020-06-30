#pragma once
#ifndef M_NOTNEEDED
#define _CRT_SECURE_NO_WARNINGS
	#include <stdlib.h>
	#include <Windows.h>
	#include <malloc.h>
	#include <Lmcons.h>
	#include <iostream>
	#include <direct.h>
	#include <conio.h>
	#include <time.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <io.h>
	#include <fcntl.h>
#endif 

#define DEBUGER
#ifndef DEBUGER
	#define LOG(X) 
	#define STOP
#else
	#define LOG(X)	std::cout<<X<<std::endl
	#define STOP	std::system("pause")
#endif 

#define M_WIDTH 120
#define M_HEIGHT 29
#define M_TOP 1

#define M_PATH_BUFFER	{{ 0,0},			 { M_WIDTH ,M_TOP },144}
#define M_STATUS_BUFFER	{{ 0,M_TOP},		 { M_WIDTH ,M_TOP}, 144}
#define M_REQUEST_BUFFER {{ 0,M_TOP+M_TOP},	 { M_WIDTH ,M_TOP },144}

#define M_FEEDBACK_BUFFER	{{0,M_TOP*3},		 { M_WIDTH/2,M_HEIGHT }, 16}
#define M_MSTFILE_BUFFER	{{M_WIDTH/2,M_TOP*3},{ M_WIDTH/2 ,M_HEIGHT },16}

#define M_INDEX(CD,CS) (INT32)((((COORD)CD).Y*((COORD)CS).X)+((COORD)CD).X)

#define M_FILE_STFILEEX (CLPSTR)".mst"
#define M_FILE_KSFILEEX (CLPSTR)".mks"

#define M_FUNC_ARGS 4
#define M_FUNC_COUNT 11
#define M_FUNC_KWLEN 8
#define M_FUNC_KWLENRAW (M_FUNC_KWLEN-1)
#define M_MSGSIZE 32

#define M_BUFFERS 5
#define M_BUFFER_PATH 0
#define M_BUFFER_FEEDBACK 1
#define M_BUFFER_MSTFILE 2
#define M_BUFFER_REQUEST 3
#define M_BUFFER_STATUS 4

#define M_MESSAGES 10
#define M_MESSAGES_QUERRY_UNKNOW 0 
#define M_MESSAGES_FUNCTION_ERROR 1 
#define M_MESSAGES_FUNCTION_OKAY 2
#define M_MESSAGES_FUNCTION_PARAMETER 6
#define M_MESSAGES_FUNCTION_LOAD_ERROR 7
#define M_MESSAGES_FUNCTION_LOAD_NOPNFILE 9
#define M_MESSAGES_FUNCTION_LOAD_OKAY 8
#define M_MESSAGES_FOLDER_UNKOW 3
#define M_MESSAGES_FOLDER_ERROR 4
#define M_MESSAGES_FOLDER_OKAY 5
#define M_MESSAGES_FILE_READF 10
#define M_MESSAGES_FILE_WRITEF 11
#define M_MESSAGES_FILE_OKAY 12
#define M_MESSAGES_FILE_FACCESS 13

#define M_MODES 4
#define M_MODES_SHOW	's'
#define M_MODES_PUSH	'p'
#define M_MODES_ALL		'a'
#define M_MODES_LOCAL	'l'


#define M_STATUS_KEEPALIVE 0xA000
#define M_STATUS_QUIT		0xAEEE


#define M_COLOR(c) (WORD)(c)
#define M_BACKGROUND			 M_COLOR(0 )
#define M_COLOR_FAILED			 M_COLOR(12)
#define M_COLOR_UNKNOW			 M_COLOR(12)
#define M_COLOR_GOOD			 M_COLOR(10)
#define M_COLOR_NAME			 M_COLOR(13)
#define M_COLOR_INDEXES			 M_COLOR(15)
#define M_COLOR_INPUT			 M_COLOR(15)
#define M_COLOR_FUNCTION		 M_COLOR(7 )
#define M_COLOR_SYMPOL_UPLIGHT	 M_COLOR(7 )
#define M_COLOR_SYMPOL			 M_COLOR(8 )
#define M_COLOR_SYMPOL_HIGHLIGHT M_COLOR(15)
#define M_COLOR_FUNCTION_OUTPUT	 M_COLOR(13)


#define M_KW_INPUT		'?'
#define M_KW_STARTFUNC	'['
#define M_KW_STOPFUNC	']'
#define M_KW_MOVEPATH	'@'
#define M_KW_SPACE		' '
#define M_KW_WILDCARD	'-'
#define M_KW_SELLECT	'#'

#define M_ENDL '\0'
#define M_NEWL '\n'
#define M_BASL '\\'
#define M_WLCD '*'