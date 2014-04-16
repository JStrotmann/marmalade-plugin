/*
Generic implementation of the IFAWrapper extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "IFAWrapper_internal.h"
s3eResult IFAWrapperInit()
{
    //Add any generic initialisation code here
    return IFAWrapperInit_platform();
}

void IFAWrapperTerminate()
{
    //Add any generic termination code here
    IFAWrapperTerminate_platform();
}

const char* IFAGetAppleAdvertisingIdentifier()
{
	return IFAGetAppleAdvertisingIdentifier_platform();
}

bool IFAGetIsAdvertisingTrackingEnabled()
{
	return IFAGetIsAdvertisingTrackingEnabled_platform();
}
