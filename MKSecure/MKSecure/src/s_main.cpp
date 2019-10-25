#include "s_header.h"

MKS o_Object;
int main()
{
	if (!o_Object.vSetup())
	{
		return o_Object.vCleanup();
	}
	while (o_Object.vLoop())
	{
		o_Object.vCatchloop();
	} 
	return o_Object.vCleanup();
}
