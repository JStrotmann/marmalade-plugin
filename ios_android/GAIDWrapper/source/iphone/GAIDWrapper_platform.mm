/*
 * iphone-specific implementation of the GAIDWrapper extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "GAIDWrapper_internal.h"

s3eResult GAIDWrapperInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void GAIDWrapperTerminate_platform()
{
    // Add any platform-specific termination code here
}

void GAIDGetGoogleAdvertisingId_platform(s3eCallback cb)
{
}
