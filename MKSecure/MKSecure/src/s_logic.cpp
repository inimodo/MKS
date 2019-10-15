#include "s_header.h"

void __CC 
mks::cConsole::vLoadHandle()
{
	o_HwndOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	o_HwndInput = GetStdHandle(STD_INPUT_HANDLE);
}
void __CC 
mks::cConsole::vGetWinUser()
{
	this->c_LUser.s_Length = UNLEN + 1;
	this->c_LUser.c_pStr = (LPSTR)malloc(UNLEN+1);
	GetUserNameA(this->c_LUser, (LPDWORD)& this->c_LUser.s_Length);
}
void __CC 
mks::cPassword::vFileread() 
{

}
void __CC
mks::cPassword::vRequestCheck(char & c_Check)
{

}
void __CC
mks::cPassword::vPushValue(char c_Value)
{

}