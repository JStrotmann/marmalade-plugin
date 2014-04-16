/*
Generic implementation of the s3eMATSDK extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "s3eMATSDK_internal.h"

s3eResult s3eMATSDKInit()
{
    //Add any generic initialisation code here
    return MATSDKInit_platform();
}


void s3eMATSDKTerminate()
{
    //Add any generic termination code here
    MATSDKTerminate_platform();
}

void MATStartMobileAppTracker(const char* adId, const char* convKey)
{
    MATStartMobileAppTracker_platform(adId, convKey);
}

void MATMeasureSession()
{
    MATMeasureSession_platform();
}

void MATMeasureAction(const char* eventIdOrName)
{
    MATMeasureAction_platform(eventIdOrName);
}

void MATMeasureActionWithReferenceId(const char* eventIdOrName, const char* refId)
{
    MATMeasureActionWithReferenceId_platform(eventIdOrName, refId);
}

void MATMeasureActionWithRevenue(const char* eventIdOrName, const char* refId, const char* revenue, const char*  currency)
{
    MATMeasureActionWithRevenue_platform(eventIdOrName, refId, revenue, currency);
}

void MATMeasureActionWithItems(const char* eventIdOrName, const MATArray* items, const char* refId, const char* revenueAmount, const char* currencyCode, uint8 transactionState, const char* receipt, const char* receiptSignature)
{
    MATMeasureActionWithItems_platform(eventIdOrName, items, refId, revenueAmount, currencyCode, transactionState, receipt, receiptSignature);
}

void MATStartAppToAppTracking(const char* targetAppId, const char* advertiserId, const char* offerId, const char* publisherId, bool shouldRedirect)
{
    MATStartAppToAppTracking_platform(targetAppId, advertiserId, offerId, publisherId, shouldRedirect);
}

void MATSetPackageName(const char* packageName)
{
    MATSetPackageName_platform(packageName);
}

void MATSetCurrencyCode(const char* currencyCode)
{
    MATSetCurrencyCode_platform(currencyCode);
}

void MATSetJailbroken(bool isJailbroken)
{
    MATSetJailbroken_platform(isJailbroken);
}

void MATSetUserEmail(const char* userEmail)
{
    MATSetUserEmail_platform(userEmail);
}

void MATSetUserId(const char* userId)
{
    MATSetUserId_platform(userId);
}

void MATSetUserName(const char* userName)
{
    MATSetUserName_platform(userName);
}

void MATSetFacebookUserId(const char* userFacebookId)
{
    MATSetFacebookUserId_platform(userFacebookId);
}

void MATSetTwitterUserId(const char* userTwitterId)
{
    MATSetTwitterUserId_platform(userTwitterId);
}

void MATSetGoogleUserId(const char* userGoogleId)
{
    MATSetGoogleUserId_platform(userGoogleId);
}

void MATSetGoogleAdvertisingId(const char* googleId, bool limitAdTracking)
{
    MATSetGoogleAdvertisingId_platform(googleId, limitAdTracking);
}

void MATSetSiteId(const char* siteId)
{
    MATSetSiteId_platform(siteId);
}

void MATSetTRUSTeId(const char* tpid)
{
    MATSetTRUSTeId_platform(tpid);
}

void MATSetAppAdTracking(bool enable)
{
    MATSetAppAdTracking_platform(enable);
}

void MATSetDelegate(bool enable)
{
    MATSetDelegate_platform(enable);
}

void MATSetDebugMode(bool shouldDebug)
{
    MATSetDebugMode_platform(shouldDebug);
}

void MATSetEventAttribute1(const char* attr)
{
    MATSetEventAttribute1_platform(attr);
}

void MATSetEventAttribute2(const char* attr)
{
    MATSetEventAttribute2_platform(attr);
}

void MATSetEventAttribute3(const char* attr)
{
    MATSetEventAttribute3_platform(attr);
}

void MATSetEventAttribute4(const char* attr)
{
    MATSetEventAttribute4_platform(attr);
}

void MATSetEventAttribute5(const char* attr)
{
    MATSetEventAttribute5_platform(attr);
}

void MATSetExistingUser(bool isExistingUser)
{
    MATSetExistingUser_platform(isExistingUser);
}

void MATSetPayingUser(bool isPayingUser)
{
    MATSetPayingUser_platform(isPayingUser);
}

void MATSetAllowDuplicates(bool allowDuplicates)
{
    MATSetAllowDuplicates_platform(allowDuplicates);
}

void MATSetShouldAutoDetectJailbroken(bool shouldAutoDetect)
{
    MATSetShouldAutoDetectJailbroken_platform(shouldAutoDetect);
}

void MATSetShouldAutoGenerateAppleVendorIdentifier(bool shouldAutoGenerate)
{
    MATSetShouldAutoGenerateAppleVendorIdentifier_platform(shouldAutoGenerate);
}

void MATSetUseCookieTracking(bool useCookieTracking)
{
    MATSetUseCookieTracking_platform(useCookieTracking);
}

void MATSetRedirectUrl(const char* redirectUrl)
{
   MATSetRedirectUrl_platform(redirectUrl);
}

void MATSetAppleAdvertisingIdentifier(const char* appleAdvertisingId, bool trackingEnabled)
{
    MATSetAppleAdvertisingIdentifier_platform(appleAdvertisingId, trackingEnabled);
}

void MATSetAppleVendorIdentifier(const char* vendorId)
{
    MATSetAppleVendorIdentifier_platform(vendorId);
}

void MATSetAge(int age)
{
    MATSetAge_platform(age);
}

void MATSetGender(int gender)
{
    MATSetGender_platform(gender);
}

void MATSetLocation(const char* latitude, const char* longitude)
{
    MATSetLocation_platform(latitude, longitude);
}

void MATSetLocationWithAltitude(const char* latitude, const char* longitude, const char* altitude)
{
    MATSetLocationWithAltitude_platform(latitude, longitude, altitude);
}

bool MATGetIsPayingUser()
{
    return MATGetIsPayingUser_platform();
}

const char* MATGetMatId()
{
    return MATGetMatId_platform();
}

const char* MATGetOpenLogId()
{
    return MATGetOpenLogId_platform();
}