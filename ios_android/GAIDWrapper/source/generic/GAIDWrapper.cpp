/*
Generic implementation of the GAIDWrapper extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "GAIDWrapper_internal.h"
s3eResult GAIDWrapperInit()
{
    //Add any generic initialisation code here
    return GAIDWrapperInit_platform();
}

void GAIDWrapperTerminate()
{
    //Add any generic termination code here
    GAIDWrapperTerminate_platform();
}

void GAIDGetGoogleAdvertisingId(s3eCallback cb)
{
	GAIDGetGoogleAdvertisingId_platform(cb);
}
