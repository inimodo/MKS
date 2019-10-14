#include "s_header.h"

void __CC 
mks::vSetup()
{
	mks::o_Buffer.vLoadHandle();
}
char __CC
mks::vLoop()
{
	return 1;
}
int __CC
mks::vCleanup()
{
	return 1;
}
char __CC
mks::vCatchloop()
{
	return 1;
}