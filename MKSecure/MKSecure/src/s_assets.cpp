#define _MKS_REQ_FUNCTION_ACCESS
#include "header\s_functions.h"


CHAR mks::data::a_Assets_Messages[M_MESSAGES][M_MSGSIZE] =
{
	{ "Querry could not be Resolved!  " },
	{ "Function end was not Reached!  " },
	{ "Operation done without note!   " },
	{ "This Folder is Unreachable!    " },
	{ "Directory did not change!      " },
	{ "Moved to Folder!               " },
	{ "Invalid parameter value!       " },
	{ "File was unable to be used!    " },
	{ "File reading Finsihed!         " },
	{ "There are no open files        " },
	{ "No such file in directory      " }
};

SFUNC mks::data::a_Assets_Functions[M_FUNC_COUNT] =
{
	{1,FALSE,(CHAR*)"crwpush",crwpush },
	{0,FALSE,(CHAR*)"crwpeek",crwpeek },
	{1,FALSE,(CHAR*)"crwseek",crwseek },
	{0,FALSE,(CHAR*)"foclose",foclose },
	{1,TRUE, (CHAR*)"bkeygen",bkeygen },
	{0,FALSE,(CHAR*)"mstlist",mstlist },
	{1,FALSE,(CHAR*)"mstopen",mstopen },
	{0,FALSE,(CHAR*)"mstexit",mstexit },
	{1,FALSE,(CHAR*)"mstsave",mstsave },
	{1,FALSE,(CHAR*)"mstrmve",mstrmve },
	{2,FALSE,(CHAR*)"encrypt",encrypt },
	{2,FALSE,(CHAR*)"decrypt",decrypt },
	{1,FALSE,(CHAR*)"packint",packint },
	{2,FALSE,(CHAR*)"packout",packout }
};

WORD mks::data::a_Assets_MColors[M_MESSAGES] = {
	M_COLOR_FAILED,
	M_COLOR_FAILED,
	M_COLOR_GOOD,
	M_COLOR_FAILED,
	M_COLOR_FAILED,
	M_COLOR_GOOD,
	M_COLOR_FAILED,
	M_COLOR_FAILED,
	M_COLOR_GOOD,
	M_COLOR_FAILED,
	M_COLOR_FAILED
};

BUFFER mks::data::a_Assets_Buffer[M_BUFFERS];
