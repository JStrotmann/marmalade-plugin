/*
 * Internal header for the s3eMATSDK extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef S3EMATSDK_INTERNAL_H
#define S3EMATSDK_INTERNAL_H

#include "s3eTypes.h"
#include "s3eMATSDK.h"
#include "s3eMATSDK_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult s3eMATSDKInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult MATSDKInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void s3eMATSDKTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void MATSDKTerminate_platform();
void MATStartMobileAppTracker_platform(const char* adId, const char* convKey);

void MATMeasureSession_platform();

void MATMeasureAction_platform(const char* action);
void MATMeasureActionWithReferenceId_platform(const char* eventIdOrName, const char* refId);
void MATMeasureActionWithRevenue_platform(const char* eventIdOrName, const char* refId, const char* revenue, const char* currency);
void MATMeasureActionWithItems_platform(const char* eventIdOrName, const MATArray* items, const char* refId, const char* revenueAmount, const char* currencyCode, uint8 transactionState, const char* receipt, const char* receiptSignature);

void MATStartAppToAppTracking_platform(const char *targetAppId, const char *advertiserId, const char *offerId, const char *publisherId, bool shouldRedirect);

void MATSetAge_platform(int age);
void MATSetAllowDuplicates_platform(bool allowDuplicates);
void MATSetAppAdTracking_platform(bool enable);
void MATSetAppleAdvertisingIdentifier_platform(const char* advertiserId, bool trackingEnabled);
void MATSetAppleVendorIdentifier_platform(const char* vendorId);
void MATSetCurrencyCode_platform(const char* currencyCode);
void MATSetDelegate_platform(bool enable);
void MATSetDebugMode_platform(bool shouldDebug);
void MATSetEventAttribute1_platform(const char* attr);
void MATSetEventAttribute2_platform(const char* attr);
void MATSetEventAttribute3_platform(const char* attr);
void MATSetEventAttribute4_platform(const char* attr);
void MATSetEventAttribute5_platform(const char* attr);
void MATSetExistingUser_platform(bool shouldDebug);
void MATSetPayingUser_platform(bool isPaying);
void MATSetGender_platform(int gender);
void MATSetGoogleAdvertisingId_platform(const char* googleId, bool limitAdTracking);
void MATSetJailbroken_platform(bool isJailbroken);
void MATSetLocation_platform(const char* latitude, const char* longitude);
void MATSetLocationWithAltitude_platform(const char* latitude, const char* longitude, const char* altitude);
void MATSetPackageName_platform(const char* packageName);
void MATSetSiteId_platform(const char* siteId);
void MATSetTRUSTeId_platform(const char* tpid);
void MATSetUserEmail_platform(const char* userEmail);
void MATSetUserId_platform(const char* userId);
void MATSetUserName_platform(const char* userName);
void MATSetFacebookUserId_platform(const char* userFacebookId);
void MATSetTwitterUserId_platform(const char* userTwitterId);
void MATSetGoogleUserId_platform(const char* userGoogleId);

void MATSetShouldAutoDetectJailbroken_platform(bool shouldAutoDetect);
void MATSetShouldAutoGenerateAppleVendorIdentifier_platform(bool shouldAutoGenerate);

void MATSetUseCookieTracking_platform(bool useCookieTracking);
void MATSetRedirectUrl_platform(const char* redirectUrl);

bool MATGetIsPayingUser_platform();
const char* MATGetMatId_platform();
const char* MATGetOpenLogId_platform();


#endif /* !S3EMATSDK_INTERNAL_H */
