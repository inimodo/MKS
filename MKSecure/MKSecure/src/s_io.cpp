#include"s_header.h"

void __ST
cIOBuffer::vSetupBuffer()
{
	this->c_LUser.vSet(UNLEN);
	this->c_LDir.vSet(MAX_PATH);
}
void __ST
cIOSystem::vSetupBuffer()
{
	this->c_RawKey.vSet(_BUFFER_S);
}
void __CC 
cIOBuffer::vRequestInput(cStr* c_InputBuffer)
{
}
void __CC
cIOBuffer::vProcessOutput(DWORD dw_Msg)
{
}
