#include "s_header.h"
int main()
{
	mks::vSetup();
	do
	{
		mks::vCatchloop();
	} while (mks::vLoop());
	return mks::vCleanup();
}