/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */
/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */
#ifndef S3E_EXT_MATSDK_H
#define S3E_EXT_MATSDK_H

#include <s3eTypes.h>

#define S3E_MATSDK_STRING_MAX 255

typedef struct MATSDKEventItem
{
    char        name[S3E_MATSDK_STRING_MAX];
    char        unitPrice[S3E_MATSDK_STRING_MAX];
    int         quantity;
    char        revenue[S3E_MATSDK_STRING_MAX];
    char        attribute1[S3E_MATSDK_STRING_MAX];
    char        attribute2[S3E_MATSDK_STRING_MAX];
    char        attribute3[S3E_MATSDK_STRING_MAX];
    char        attribute4[S3E_MATSDK_STRING_MAX];
    char        attribute5[S3E_MATSDK_STRING_MAX];
} MATSDKEventItem;

typedef struct MATArray {
    void *m_items; // Items in array
    unsigned int m_count; // number of items
} MATArray;

typedef enum MATExtensionCallback
{
    MAT_CALLBACK_OPENURL,
    MAT_CALLBACK_MAX
} MATExtensionCallback;
// \cond HIDDEN_DEFINES
S3E_BEGIN_C_DECL
// \endcond

/**
 * Returns S3E_TRUE if the MATSDK extension is available.
 */
s3eBool s3eMATSDKAvailable();

void MATStartMobileAppTracker(const char* adId, const char* convKey);

void MATCheckForDeferredDeeplink(const char* timeout, s3eCallback function);

void MATMeasureSession();

void MATMeasureAction(const char* eventIdOrName);

void MATMeasureActionWithReferenceId(const char* eventIdOrName, const char* refId);

void MATMeasureActionWithRevenue(const char* eventIdOrName, const char* refId, const char* revenueAmount, const char* currencyCode);

void MATMeasureActionWithItems(const char* eventIdOrName, const MATArray* items, const char* refId, const char* revenueAmount, const char* currencyCode, uint8 transactionState, const char* receipt, const char* receiptSignature);

void MATSetPackageName(const char* packageName);

void MATSetCurrencyCode(const char* currencyCode);

void MATSetUserEmail(const char* userEmail);

void MATSetUserId(const char* userId);

void MATSetUserName(const char* userName);

void MATSetFacebookUserId(const char* userFacebookId);

void MATSetTwitterUserId(const char* userTwitterId);

void MATSetGoogleUserId(const char* userGoogleId);

void MATSetGoogleAdvertisingId(const char* googleId, bool limitAdTracking);

void MATSetSiteId(const char* siteId);

void MATSetTRUSTeId(const char* tpid);

void MATSetAppAdTracking(bool enable);

void MATSetDelegate(bool enable);

void MATSetEventAttribute1(const char* attr);

void MATSetEventAttribute2(const char* attr);

void MATSetEventAttribute3(const char* attr);

void MATSetEventAttribute4(const char* attr);

void MATSetEventAttribute5(const char* attr);

void MATSetEventContentType(const char* contentType);

void MATSetEventContentId(const char* contentId);

void MATSetEventLevel(int level);

void MATSetEventQuantity(int quantity);

void MATSetEventSearchString(const char* searchString);

void MATSetEventRating(const char * rating);

void MATSetEventDate1(const char* date);

void MATSetEventDate2(const char* date);

void MATSetExistingUser(bool isExisting);

void MATSetFacebookEventLogging(bool enable, bool limitUsage);

void MATSetPayingUser(bool isPaying);

void MATSetJailbroken(bool isJailbroken);

void MATSetShouldAutoDetectJailbroken(bool shouldAutoDetect);

void MATSetUseCookieTracking(bool useCookieTracking);

void MATSetAge(int age);

void MATSetGender(int gender);

void MATSetLocation(const char* latitude, const char* longitude);

void MATSetLocationWithAltitude(const char* latitude, const char* longitude, const char* altitude);

bool MATGetIsPayingUser();

const char* MATGetMatId();

const char* MATGetOpenLogId();

void MATStartAppToAppTracking(const char* targetAppId, const char* advertiserId, const char* offerId, const char* publisherId, bool shouldRedirect);

void MATSetRedirectUrl(const char* redirectUrl);

void MATSetAppleAdvertisingIdentifier(const char* ifa, bool advertisingTrackingEnabled);

void MATSetAppleVendorIdentifier(const char* ifv);

void MATSetShouldAutoGenerateAppleVendorIdentifier(bool shouldAutoGenerate);

void MATSetDebugMode(bool shouldDebug);

void MATSetAllowDuplicates(bool allowDuplicates);

S3E_END_C_DECL


#endif /* !S3E_EXT_MATSDK_H */
