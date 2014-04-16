/*
 * iphone-specific implementation of the s3eMATSDK extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eMATSDK_internal.h"
#import <UIKit/UIKit.h>
#include "s3eTypes.h"
#include "s3eEdk.h"
#include "s3eEdk_iphone.h"
#include "IwDebug.h"

#include "MobileAppTracker.h"
#include "MATEventItem.h"

#define S3E_CURRENT_EXT MATSDK
#include "s3eEdkError.h"
#define S3E_DEVICE_MATSDK S3E_EXT_MATSDK_HASH
#define PARAMETERS

// Converts C style string to NSString
NSString* CreateNSString (const char* string)
{
    return [NSString stringWithUTF8String:string ? string : ""];
}


@interface MATSDKDelegate : NSObject <MobileAppTrackerDelegate>

@end

@implementation MATSDKDelegate

- (void)mobileAppTrackerDidSucceedWithData:(NSData *)data
{
    NSString * dataString = [[[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding] autorelease];
    NSLog(@"Native: MATSDKDelegate: success: %@", dataString);
}

- (void)mobileAppTrackerDidFailWithError:(NSError *)error
{
    NSInteger errorCode = [error code];
    NSString *errorDescr = [error localizedDescription];
    
    NSString *errorURLString = nil;
    NSDictionary *dictError = [error userInfo];
    
    if(dictError)
    {
        errorURLString = [dictError objectForKey:NSURLErrorFailingURLStringErrorKey];
    }
    
    errorURLString = nil == error ? @"" : errorURLString;
    
    NSString *strError = [NSString stringWithFormat:@"{\"code\":\"%d\",\"localizedDescription\":\"%@\",\"failedURL\":\"%@\"}", errorCode, errorDescr, errorURLString];
    
    NSLog(@"Native: MATSDKDelegate: error = %@", strError);
}

- (void)mobileAppTrackerEnqueuedActionWithReferenceId:(NSString *)referenceId
{
    NSLog(@"Native: MATSDKDelegate: enqueued: %@", referenceId);
}

@end

MATSDKDelegate *matDelegate;

s3eResult MATSDKInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void MATSDKTerminate_platform()
{
    // Add any platform-specific termination code here
}

void MATStartMobileAppTracker_platform(const char* adId, const char* convKey)
{
    NSLog(@"Native: Starting MAT");
    
    if(NULL != adId && NULL != convKey)
    {
        NSString *aid = [NSString stringWithUTF8String:adId];
        NSString *ckey = [NSString stringWithUTF8String:convKey];
        [MobileAppTracker initializeWithMATAdvertiserId:aid MATConversionKey:ckey];
        [MobileAppTracker setPluginName:@"marmalade"];
    }
    else
    {
        NSLog(@"MAT Error! MAT Advertiser ID and MAT Conversion Key cannot be NULL.");
    }
}

void MATMeasureSession_platform()
{
    NSLog(@"Native: measureSession");
    [MobileAppTracker measureSession];
}

void MATMeasureAction_platform(const char* eventIdOrName)
{
    NSLog(@"Native: measureAction");
    
    NSString *strEventIdOrName = NULL == eventIdOrName ? nil : [NSString stringWithUTF8String:eventIdOrName];
    
    [MobileAppTracker measureAction:strEventIdOrName];
}

void MATMeasureActionWithReferenceId_platform(const char* eventIdOrName, const char* refId)
{
    NSLog(@"Native: measureActionWithReferenceId");
    
    NSString *strEventIdOrName = NULL == eventIdOrName ? nil : [NSString stringWithUTF8String:eventIdOrName];
    NSString *strRefId = NULL == refId ? nil : [NSString stringWithUTF8String:refId];
    
    [MobileAppTracker measureAction:strEventIdOrName referenceId:strRefId];
}

void MATMeasureActionWithRevenue_platform(const char* eventIdOrName, const char* refId, const char* revenue, const char* currencyCode)
{
    NSLog(@"Native: measureActionWithRevenue");
    
    NSString *strEventIdOrName = NULL == eventIdOrName ? nil : [NSString stringWithUTF8String:eventIdOrName];
    NSString *strRefId = NULL == refId ? nil : [NSString stringWithUTF8String:refId];
    NSString *strRevenue = NULL == revenue ? nil : [NSString stringWithUTF8String:revenue];
    NSString *strCurrencyCode = NULL == currencyCode ? nil : [NSString stringWithUTF8String:currencyCode];

    [MobileAppTracker measureAction:strEventIdOrName
                      revenueAmount:[strRevenue floatValue]
                       currencyCode:strCurrencyCode];
}

void MATMeasureActionWithItems_platform(const char* eventIdOrName, const MATArray* items, const char* refId, const char* revenueAmount, const char* currencyCode, uint8 transactionState, const char* receipt, const char* receiptSignature)
{
    NSString *strEventIdOrName = NULL == eventIdOrName ? nil : [NSString stringWithUTF8String:eventIdOrName];
    NSString *strRefId = NULL == refId ? nil : [NSString stringWithUTF8String:refId];
    NSString *strRevenueAmount = NULL == revenueAmount ? nil : [NSString stringWithUTF8String:revenueAmount];
    NSString *strCurrencyCode = NULL == currencyCode ? nil : [NSString stringWithUTF8String:currencyCode];
    NSString *strReceipt = NULL == receipt ? nil : [NSString stringWithUTF8String:receipt];
    // iOS does not use the receiptSignature param, it's only for Android.
    
    NSLog(@"Native: measureActionWithItems");
    NSLog(@"eventName        = %@", strEventIdOrName);
    NSLog(@"refId            = %@", strRefId);
    NSLog(@"revenueAmount    = %@", strRevenueAmount);
    NSLog(@"transactionState = %i", (unsigned int)transactionState);
    NSLog(@"currCode         = %@", strCurrencyCode);
    NSLog(@"receipt          = %@", strReceipt);
    
    // print the items array
    NSLog(@"MATSDK events array: %i", items->m_count);
    for (uint i=0; i < items->m_count; i++)
    {
        NSLog(@"Item name = %s, unitPrice = %s, quantity = %i, revenue = %s, attribute1 = %s, attribute2 = %s, attribute3 = %s, attribute4 = %s, attribute5 = %s",
                            ((MATSDKEventItem*)items->m_items)[i].name,
                            ((MATSDKEventItem*)items->m_items)[i].unitPrice,
                            ((MATSDKEventItem*)items->m_items)[i].quantity,
                            ((MATSDKEventItem*)items->m_items)[i].revenue,
                            ((MATSDKEventItem*)items->m_items)[i].attribute1,
                            ((MATSDKEventItem*)items->m_items)[i].attribute2,
                            ((MATSDKEventItem*)items->m_items)[i].attribute3,
                            ((MATSDKEventItem*)items->m_items)[i].attribute4,
                            ((MATSDKEventItem*)items->m_items)[i].attribute5);
    }
    
    // create an NSArray of MATEventItem objects
    NSMutableArray *array = [NSMutableArray array];
    for (uint i=0; i < items->m_count; i++)
    {
        NSString *name = [NSString stringWithUTF8String:((MATSDKEventItem*)items->m_items)[i].name];
        
        NSString *strUnitPrice = [NSString stringWithUTF8String:((MATSDKEventItem*)items->m_items)[i].unitPrice];
        int quantity = ((MATSDKEventItem*)items->m_items)[i].quantity;
        NSString *strRevenue = [NSString stringWithUTF8String:((MATSDKEventItem*)items->m_items)[i].revenue];
        
        NSString *attribute1 = [NSString stringWithUTF8String:((MATSDKEventItem*)items->m_items)[i].attribute1];
        NSString *attribute2 = [NSString stringWithUTF8String:((MATSDKEventItem*)items->m_items)[i].attribute2];
        NSString *attribute3 = [NSString stringWithUTF8String:((MATSDKEventItem*)items->m_items)[i].attribute3];
        NSString *attribute4 = [NSString stringWithUTF8String:((MATSDKEventItem*)items->m_items)[i].attribute4];
        NSString *attribute5 = [NSString stringWithUTF8String:((MATSDKEventItem*)items->m_items)[i].attribute5];
        
        MATEventItem *item = [MATEventItem eventItemWithName:name unitPrice:[strUnitPrice floatValue] quantity:quantity revenue:[strRevenue floatValue] attribute1:attribute1 attribute2:attribute2 attribute3:attribute3 attribute4:attribute4 attribute5:attribute5];
        
        [array addObject:item];
    }
    
    [MobileAppTracker measureAction:strEventIdOrName
                         eventItems:array
                        referenceId:strRefId
                      revenueAmount:[strRevenueAmount floatValue]
                       currencyCode:strCurrencyCode
                   transactionState:(int)transactionState
                            receipt:[strReceipt dataUsingEncoding:NSUTF8StringEncoding]];
}

void MATSetPackageName_platform(const char* packageName)
{
    NSLog(@"Native: setPackageName = %s", packageName);
    
    NSString *strPackageName = NULL == packageName ? nil : [NSString stringWithUTF8String:packageName];
    
    [MobileAppTracker setPackageName:strPackageName];
}

void MATSetCurrencyCode_platform(const char* currencyCode)
{
    NSLog(@"Native: setCurrencyCode = %s", currencyCode);
    
    NSString *strCurrencyCode = NULL == currencyCode ? nil : [NSString stringWithUTF8String:currencyCode];
    
    [MobileAppTracker setCurrencyCode:strCurrencyCode];
}

void MATSetUserEmail_platform(const char* userEmail)
{
    NSLog(@"Native: setUserEmail = %s", userEmail);
    
    NSString *strUserEmail = NULL == userEmail ? nil : [NSString stringWithUTF8String:userEmail];
    
    [MobileAppTracker setUserEmail:strUserEmail];
}

void MATSetUserId_platform(const char* userId)
{
    NSLog(@"Native: setUserId = %s", userId);
    
    NSString *strUserId = NULL == userId ? nil : [NSString stringWithUTF8String:userId];
    
    [MobileAppTracker setUserId:strUserId];
}

void MATSetUserName_platform(const char* userName)
{
    NSLog(@"Native: setUserName = %s", userName);
    
    NSString *strUserName = NULL == userName ? nil : [NSString stringWithUTF8String:userName];
    
    [MobileAppTracker setUserName:strUserName];
}

void MATSetFacebookUserId_platform(const char* userId)
{
    NSLog(@"Native: setFacebookUserId: %s", userId);

    [MobileAppTracker setFacebookUserId:CreateNSString(userId)];
}

void MATSetTwitterUserId_platform(const char* userId)
{
    NSLog(@"Native: setTwitterUserId: %s", userId);
    
    [MobileAppTracker setTwitterUserId:CreateNSString(userId)];
}

void MATSetGoogleUserId_platform(const char* userId)
{
    NSLog(@"Native: setGoogleUserId: %s", userId);
    
    [MobileAppTracker setGoogleUserId:CreateNSString(userId)];
}

void MATSetEventAttribute1_platform(const char* attr)
{
    NSLog(@"Native: setEventAttribute1: %s", attr);
    
    [MobileAppTracker setEventAttribute1:CreateNSString(attr)];
}

void MATSetEventAttribute2_platform(const char* attr)
{
    NSLog(@"Native: setEventAttribute2: %s", attr);
    
    [MobileAppTracker setEventAttribute2:CreateNSString(attr)];
}

void MATSetEventAttribute3_platform(const char* attr)
{
    NSLog(@"Native: setEventAttribute3: %s", attr);
    
    [MobileAppTracker setEventAttribute3:CreateNSString(attr)];
}

void MATSetEventAttribute4_platform(const char* attr)
{
    NSLog(@"Native: setEventAttribute4: %s", attr);
    
    [MobileAppTracker setEventAttribute4:CreateNSString(attr)];
}

void MATSetEventAttribute5_platform(const char* attr)
{
    NSLog(@"Native: setEventAttribute5: %s", attr);
    
    [MobileAppTracker setEventAttribute5:CreateNSString(attr)];
}

void MATSetGoogleAdvertisingId_platform(const char* googleId, bool limitAdTracking)
{
    // NOT IMPLEMENTED FOR iOS
}

void MATSetSiteId_platform(const char* siteId)
{
    NSLog(@"Native: setSiteId = %s", siteId);
    
    NSString *strSiteId = NULL == siteId ? nil : [NSString stringWithUTF8String:siteId];
    
    [MobileAppTracker setSiteId:strSiteId];
}

void MATSetTRUSTeId_platform(const char* tpid)
{
    NSLog(@"Native: setTRUSTeId = %s", tpid);
    
    NSString *strTpid = NULL == tpid ? nil : [NSString stringWithUTF8String:tpid];
    
    [MobileAppTracker setTRUSTeId:strTpid];
}

void MATSetDelegate_platform(bool enable)
{
    matDelegate = enable ? (matDelegate ? matDelegate : [[MATSDKDelegate alloc] init]) : nil;
    
    NSLog(@"Native: setDelegate = %d", enable);
    
    [MobileAppTracker setDelegate:matDelegate];
}

void MATSetDebugMode_platform(bool shouldDebug)
{
    NSLog(@"Native: setDebug mode = %d", shouldDebug);
    [MobileAppTracker setDebugMode:shouldDebug];
}

void MATSetAge_platform(int age)
{
    NSLog(@"Native: setAge = %d", age);
    [MobileAppTracker setAge:age];
}

void MATSetGender_platform(int gender)
{
    NSLog(@"Native: setGender = %d", gender);

    MATGender matGender = MAT_GENDER_MALE;
    if( gender == MAT_GENDER_FEMALE ) matGender = MAT_GENDER_FEMALE;
    
    [MobileAppTracker setGender:matGender];
}

void MATSetLocation_platform(const char* latitude, const char* longitude)
{
	NSString *strLat = NULL == latitude ? nil : [NSString stringWithUTF8String:latitude];
	NSString *strLong = NULL == longitude ? nil : [NSString stringWithUTF8String:longitude];
	
	NSLog(@"Native: setLocation = %@, %@", strLat, strLong);
	
    [MobileAppTracker setLatitude:[strLat floatValue] longitude:[strLong floatValue]];
}

void MATSetLocationWithAltitude_platform(const char* latitude, const char* longitude, const char* altitude)
{
	NSString *strLat = NULL == latitude ? nil : [NSString stringWithUTF8String:latitude];
	NSString *strLong = NULL == longitude ? nil : [NSString stringWithUTF8String:longitude];
	NSString *strAlt = NULL == altitude ? nil : [NSString stringWithUTF8String:altitude];
	
	NSLog(@"Native: setLocationWithAltitude = %@, %@, %@", strLat, strLong, strAlt);
	
    [MobileAppTracker setLatitude:[strLat floatValue] longitude:[strLong floatValue] altitude:[strAlt floatValue]];
}

void MATSetAllowDuplicates_platform(bool allowDuplicates)
{
    NSLog(@"Native: setAllowDuplicates: %d", allowDuplicates);
    
    [MobileAppTracker setAllowDuplicateRequests:allowDuplicates];
}

void MATSetShouldAutoDetectJailbroken_platform(bool shouldAutoDetect)
{
    NSLog(@"Native: setShouldAutoDetectJailbroken: %d", shouldAutoDetect);
    
    [MobileAppTracker setShouldAutoDetectJailbroken:shouldAutoDetect];
}

void MATSetShouldAutoGenerateAppleVendorIdentifier_platform(bool shouldAutoGenerate)
{
    NSLog(@"Native: setShouldAutoGenerateAppleVendorIdentifier: %d", shouldAutoGenerate);
    
    [MobileAppTracker setShouldAutoGenerateAppleVendorIdentifier:shouldAutoGenerate];
}

void MATSetUseCookieTracking_platform(bool useCookieTracking)
{
    NSLog(@"Native: setUseCookieTracking: %d", useCookieTracking);
    
    [MobileAppTracker setUseCookieTracking:useCookieTracking];
}

void MATSetAppAdTracking_platform(bool enable)
{
    NSLog(@"Native: setAppAdTracking: %d", enable);
    
    [MobileAppTracker setAppAdTracking:enable];
}

void MATSetExistingUser_platform(bool isExisting)
{
    NSLog(@"Native: setExistingUser: %d", isExisting);
    
    [MobileAppTracker setExistingUser:isExisting];
}

void MATSetPayingUser_platform(bool isPaying)
{
    NSLog(@"Native: setPayingUser: %d", isPaying);
    
    [MobileAppTracker setPayingUser:isPaying];
}

void MATSetJailbroken_platform(bool isJailbroken)
{
    NSLog(@"Native: setJailbroken: %d", isJailbroken);
    
    [MobileAppTracker setJailbroken:isJailbroken];
}

void MATSetRedirectUrl_platform(const char* redirectUrl)
{
    NSString *strRedirectUrl = NULL == redirectUrl ? nil : [NSString stringWithUTF8String:redirectUrl];
    
    NSLog(@"Native: setRedirectUrl = %@", strRedirectUrl);
    
    [MobileAppTracker setRedirectUrl:strRedirectUrl];
}

void MATSetAppleAdvertisingIdentifier_platform(const char* advertiserId, bool trackingEnabled)
{
    NSString *strAdvertiserId = NULL == advertiserId ? nil : [NSString stringWithUTF8String:advertiserId];
    
    NSLog(@"Native: setAppleAdvertisingIdentifier: %@", strAdvertiserId);
    
    id classNSUUID = NSClassFromString(@"NSUUID");
    
    if(classNSUUID)
    {
        [MobileAppTracker setAppleAdvertisingIdentifier:[[classNSUUID alloc] initWithUUIDString:strAdvertiserId] advertisingTrackingEnabled:trackingEnabled];
    }
}

void MATSetAppleVendorIdentifier_platform(const char* vendorId)
{
    NSString *strVendorId = NULL == vendorId ? nil : [NSString stringWithUTF8String:vendorId];
    
    NSLog(@"Native: setAppleVendorIdentifier: %@", strVendorId);
    
    id classNSUUID = NSClassFromString(@"NSUUID");
    
    if(classNSUUID)
    {
        [MobileAppTracker setAppleVendorIdentifier:[[classNSUUID alloc] initWithUUIDString:strVendorId] ];
    }
}

void MATStartAppToAppTracking_platform(const char* targetAppId, const char* advertiserId, const char* offerId, const char* publisherId, bool shouldRedirect)
{
    NSString *strTargetAppId = NULL == targetAppId ? nil : [NSString stringWithUTF8String:targetAppId];
    NSString *strAdvertiserId = NULL == advertiserId ? nil : [NSString stringWithUTF8String:advertiserId];
    NSString *strOfferId = NULL == offerId ? nil : [NSString stringWithUTF8String:offerId];
    NSString *strPublisherId = NULL == publisherId ? nil : [NSString stringWithUTF8String:publisherId];
    
    NSLog(@"Native: startAppToAppTracking: %@, %@, %@, %@, %d",
          strTargetAppId, strAdvertiserId, strOfferId, strPublisherId, shouldRedirect);

    [MobileAppTracker startAppToAppTracking:[NSString stringWithUTF8String:targetAppId]
                               advertiserId:[NSString stringWithUTF8String:advertiserId]
                                    offerId:[NSString stringWithUTF8String:offerId]
                                publisherId:[NSString stringWithUTF8String:publisherId]
                                   redirect:(BOOL)shouldRedirect];
}

bool MATGetIsPayingUser_platform()
{
    NSLog(@"Native: getIsPayingUser");
    
    return [MobileAppTracker isPayingUser];
}

const char* MATGetMatId_platform()
{
    NSLog(@"Native: getMatId");
    
    return [[MobileAppTracker matId] UTF8String];
}

const char* MATGetOpenLogId_platform()
{
    NSLog(@"Native: getOpenLogId");
    
    return [[MobileAppTracker openLogId] UTF8String];
}
