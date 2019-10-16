#include "s_header.h"
int main()
{
	vSetup();
	do
	{
		vCatchloop();
	} while (vLoop());
	return vCleanup();
}