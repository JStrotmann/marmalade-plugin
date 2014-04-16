/*
 * iphone-specific implementation of the IFAWrapper extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "IFAWrapper_internal.h"
#import <AdSupport/AdSupport.h>

s3eResult IFAWrapperInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void IFAWrapperTerminate_platform()
{
    // Add any platform-specific termination code here
}

const char* IFAGetAppleAdvertisingIdentifier_platform()
{
    NSLog(@"IFA: ifa = %@", [[ASIdentifierManager sharedManager] advertisingIdentifier]);
    
    NSString *strIFA = [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
    
    const char *ifa = strIFA ? [strIFA UTF8String] : NULL;
    
    return ifa;
}

bool IFAGetIsAdvertisingTrackingEnabled_platform()
{
    NSLog(@"IFA: trackingEnabled = %d", [[ASIdentifierManager sharedManager] isAdvertisingTrackingEnabled]);
    
    return [[ASIdentifierManager sharedManager] isAdvertisingTrackingEnabled];
}
