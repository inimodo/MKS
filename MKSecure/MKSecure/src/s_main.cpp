#include "s_header.h"
int main()
{
	vAssetWarmup();
	vSetup();
	do
	{
		vCatchloop();
	} while (vLoop());
	return vCleanup();
}