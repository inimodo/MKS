#include "s_header.h"

void __CC 
text::vReaduser() 
{
	GetUserNameA();
}

void __CC 
mks::cConsole::vLoadHandle()
{
	this->o_HwndOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	this->o_HwndInput = GetStdHandle(STD_INPUT_HANDLE);
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