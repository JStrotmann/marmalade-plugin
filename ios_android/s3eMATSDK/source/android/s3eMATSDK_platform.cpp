/*
 * android-specific implementation of the s3eMATSDK extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eMATSDK_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"
#include <android/log.h>

static jobject g_Obj;
static jmethodID g_MATStartMobileAppTracker;
static jmethodID g_MATTrackSession;
static jmethodID g_MATTrackSessionWithReferenceId;
static jmethodID g_MATTrackActionForEventIdOrName;
static jmethodID g_MATTrackActionForEventIdOrNameItems;
static jmethodID g_MATTrackAction;
static jmethodID g_MATSetPackageName;
static jmethodID g_MATStartAppToAppTracking;

static jmethodID g_MATSetCurrencyCode;
static jmethodID g_MATSetUserEmail;
static jmethodID g_MATSetUserId;
static jmethodID g_MATSetUserName;
static jmethodID g_MATSetEventAttribute1;
static jmethodID g_MATSetEventAttribute2;
static jmethodID g_MATSetEventAttribute3;
static jmethodID g_MATSetEventAttribute4;
static jmethodID g_MATSetEventAttribute5;
static jmethodID g_MATSetExistingUser;
static jmethodID g_MATSetFacebookUserId;
static jmethodID g_MATSetTwitterUserId;
static jmethodID g_MATSetGoogleUserId;
static jmethodID g_MATSetGoogleAdvertisingId;
static jmethodID g_MATSetSiteId;
static jmethodID g_MATSetTRUSTeId;
static jmethodID g_MATSetDebugMode;
static jmethodID g_MATSetAllowDuplicates;

static jmethodID g_MATSetAge;
static jmethodID g_MATSetGender;
static jmethodID g_MATSetLocation;

s3eResult MATSDKInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("s3eMATSDK");
    if (!cls)
        goto fail;

    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    // Get all the extension methods
    g_MATStartMobileAppTracker = env->GetMethodID(cls, "MATStartMobileAppTracker", "(Ljava/lang/String;Ljava/lang/String;)V");
    if (!g_MATStartMobileAppTracker)
        goto fail;

    g_MATTrackSession = env->GetMethodID(cls, "MATTrackSession", "()V");
    if (!g_MATTrackSession)
        goto fail;

    g_MATTrackSessionWithReferenceId = env->GetMethodID(cls, "MATTrackSessionWithReferenceId", "(Ljava/lang/String;)V");
    if (!g_MATTrackSessionWithReferenceId)
        goto fail;

    g_MATTrackActionForEventIdOrName = env->GetMethodID(cls, "MATTrackActionForEventIdOrName", "(Ljava/lang/String;Ljava/lang/String;)V");
    if (!g_MATTrackActionForEventIdOrName)
        goto fail;

    g_MATTrackActionForEventIdOrNameItems = env->GetMethodID(cls, "MATTrackActionForEventIdOrNameItems", "(Ljava/lang/String;Ljava/util/List;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;)V");
    if (!g_MATTrackActionForEventIdOrNameItems)
        goto fail;
    
    g_MATTrackAction = env->GetMethodID(cls, "MATTrackAction", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    if (!g_MATTrackAction)
        goto fail;

    g_MATSetPackageName = env->GetMethodID(cls, "MATSetPackageName", "(Ljava/lang/String;)V");
    if (!g_MATSetPackageName)
        goto fail;
    
    g_MATStartAppToAppTracking = env->GetMethodID(cls, "MATStartAppToAppTracking", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");
    if (!g_MATStartAppToAppTracking)
        goto fail;
    ///////
    g_MATSetCurrencyCode = env->GetMethodID(cls, "MATSetCurrencyCode", "(Ljava/lang/String;)V");
    if (!g_MATSetCurrencyCode)
        goto fail;
    
    g_MATSetUserEmail = env->GetMethodID(cls, "MATSetUserEmail", "(Ljava/lang/String;)V");
    if (!g_MATSetUserEmail)
        goto fail;
    
    g_MATSetUserId = env->GetMethodID(cls, "MATSetUserId", "(Ljava/lang/String;)V");
    if (!g_MATSetUserId)
        goto fail;
    
    g_MATSetUserName = env->GetMethodID(cls, "MATSetUserName", "(Ljava/lang/String;)V");
    if (!g_MATSetUserName)
        goto fail;

    g_MATSetFacebookUserId = env->GetMethodID(cls, "MATSetFacebookUserId", "(Ljava/lang/String;)V");
    if (!g_MATSetFacebookUserId)
        goto fail;

    g_MATSetTwitterUserId = env->GetMethodID(cls, "MATSetTwitterUserId", "(Ljava/lang/String;)V");
    if (!g_MATSetTwitterUserId)
        goto fail;

    g_MATSetGoogleUserId = env->GetMethodID(cls, "MATSetGoogleUserId", "(Ljava/lang/String;)V");
    if (!g_MATSetGoogleUserId)
        goto fail;
    
    g_MATSetEventAttribute1 = env->GetMethodID(cls, "MATSetEventAttribute1", "(Ljava/lang/String;)V");
    if (!g_MATSetEventAttribute1)
        goto fail;
    
    g_MATSetEventAttribute2 = env->GetMethodID(cls, "MATSetEventAttribute2", "(Ljava/lang/String;)V");
    if (!g_MATSetEventAttribute2)
        goto fail;
    
    g_MATSetEventAttribute3 = env->GetMethodID(cls, "MATSetEventAttribute3", "(Ljava/lang/String;)V");
    if (!g_MATSetEventAttribute3)
        goto fail;
    
    g_MATSetEventAttribute4 = env->GetMethodID(cls, "MATSetEventAttribute4", "(Ljava/lang/String;)V");
    if (!g_MATSetEventAttribute4)
        goto fail;
    
    g_MATSetEventAttribute5 = env->GetMethodID(cls, "MATSetEventAttribute5", "(Ljava/lang/String;)V");
    if (!g_MATSetEventAttribute5)
        goto fail;
    
    g_MATSetGoogleAdvertisingId = env->GetMethodID(cls, "MATSetGoogleAdvertisingId", "(Ljava/lang/String;)V");
    if (!g_MATSetGoogleAdvertisingId)
        goto fail;
    
    g_MATSetSiteId = env->GetMethodID(cls, "MATSetSiteId", "(Ljava/lang/String;)V");
    if (!g_MATSetSiteId)
        goto fail;
    
    g_MATSetTRUSTeId = env->GetMethodID(cls, "MATSetTRUSTeId", "(Ljava/lang/String;)V");
    if (!g_MATSetTRUSTeId)
        goto fail;
    
    g_MATSetDebugMode = env->GetMethodID(cls, "MATSetDebugMode", "(Z)V");
    if (!g_MATSetDebugMode)
        goto fail;
    
    g_MATSetExistingUser = env->GetMethodID(cls, "MATSetExistingUser", "(Z)V");
    if (!g_MATSetExistingUser)
        goto fail;
    
	g_MATSetAllowDuplicates = env->GetMethodID(cls, "MATSetAllowDuplicates", "(Z)V");
	if (!g_MATSetAllowDuplicates)
		goto fail;
    
    g_MATSetAge = env->GetMethodID(cls, "MATSetAge", "(I)V");
	if (!g_MATSetAge)
		goto fail;
    
    g_MATSetGender = env->GetMethodID(cls, "MATSetGender", "(I)V");
	if (!g_MATSetGender)
		goto fail;
    
    g_MATSetLocation = env->GetMethodID(cls, "MATSetLocation", "(DDD)V");
	if (!g_MATSetLocation)
		goto fail;
    
    //////
    IwTrace(MATSDK, ("MATSDK init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;

fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(s3eMATSDK, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void MATSDKTerminate_platform()
{
    // Add any platform-specific termination code here
}

void MATStartMobileAppTracker_platform(const char* adId, const char* convKey)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring adId_jstr = env->NewStringUTF(adId);
    jstring convKey_jstr = env->NewStringUTF(convKey);
    env->CallVoidMethod(g_Obj, g_MATStartMobileAppTracker, adId_jstr, convKey_jstr);
    env->DeleteLocalRef(adId_jstr);
    env->DeleteLocalRef(convKey_jstr);
}

void MATTrackSession_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_MATTrackSession);
}

void MATTrackSessionWithReferenceId_platform(const char* refId)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring refId_jstr = env->NewStringUTF(refId);
    env->CallVoidMethod(g_Obj, g_MATTrackSessionWithReferenceId, refId_jstr);
    env->DeleteLocalRef(refId_jstr);
}

void MATTrackActionForEventIdOrName_platform(const char* eventIdOrName, const char* refId)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring eventIdOrName_jstr = env->NewStringUTF(eventIdOrName);
    jstring refId_jstr = env->NewStringUTF(refId);
    env->CallVoidMethod(g_Obj, g_MATTrackActionForEventIdOrName, eventIdOrName_jstr, refId_jstr);
    env->DeleteLocalRef(eventIdOrName_jstr);
    env->DeleteLocalRef(refId_jstr);
}

void MATTrackAction_platform(const char* eventIdOrName, const char* revenue, const char* currency)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring eventIdOrName_jstr = env->NewStringUTF(eventIdOrName);
    jstring revenue_jstr = env->NewStringUTF(revenue);
    jstring currency_jstr = env->NewStringUTF(currency);
    env->CallVoidMethod(g_Obj, g_MATTrackAction, eventIdOrName_jstr, revenue_jstr, currency_jstr);
    env->DeleteLocalRef(eventIdOrName_jstr);
    env->DeleteLocalRef(revenue_jstr);
    env->DeleteLocalRef(currency_jstr);
}

void MATTrackActionForEventIdOrNameItems_platform(const char* eventIdOrName, const MATArray* items, const char* refId, const char* revenueAmount, const char* currencyCode, uint8 transactionState, const char* receipt, const char* receiptSignature)
{
    JNIEnv* jni_env = s3eEdkJNIGetEnv();
    
    // local variables for the track action
    jstring eventIdOrName_jstr = jni_env->NewStringUTF(eventIdOrName);
    jstring refId_jstr = jni_env->NewStringUTF(refId);
    jstring revenue_jstr = jni_env->NewStringUTF(revenueAmount);
    jstring currencyCode_jstr = jni_env->NewStringUTF(currencyCode);
    jstring receipt_jstr = jni_env->NewStringUTF(receipt);
    jstring receiptSignature_jstr = jni_env->NewStringUTF(receiptSignature);
    
    // create an ArrayList class
    const char* list_class_name = "java/util/ArrayList";
    jclass clsList = jni_env->FindClass(list_class_name);
    jmethodID constructorIDList = jni_env->GetMethodID(clsList, "<init>", "()V");
    jobject jlistobj = jni_env->NewObject(clsList, constructorIDList);
    jmethodID list_add_mid = 0;
    list_add_mid = jni_env->GetMethodID(clsList, "add", "(Ljava/lang/Object;)Z");
    
    // MATEventItem definition
    const char* mateventitem_class_name = "com/mobileapptracker/MATEventItem";
    jclass clsMATEventItem = jni_env->FindClass(mateventitem_class_name);
    jmethodID constructorID = jni_env->GetMethodID(clsMATEventItem, "<init>", "(Ljava/lang/String;IDDLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

    // Add a MATEventItem for each item to a List
    for (uint i = 0; i < items->m_count; i++) {
        jstring nameVal = jni_env->NewStringUTF(((MATSDKEventItem*)items->m_items)[i].name);
        jstring att1Val = jni_env->NewStringUTF(((MATSDKEventItem*)items->m_items)[i].attribute1);
        jstring att2Val = jni_env->NewStringUTF(((MATSDKEventItem*)items->m_items)[i].attribute2);
        jstring att3Val = jni_env->NewStringUTF(((MATSDKEventItem*)items->m_items)[i].attribute3);
        jstring att4Val = jni_env->NewStringUTF(((MATSDKEventItem*)items->m_items)[i].attribute4);
        jstring att5Val = jni_env->NewStringUTF(((MATSDKEventItem*)items->m_items)[i].attribute5);

        double unitPrice = strtod(((MATSDKEventItem*)items->m_items)[i].unitPrice, NULL);
        double revenue = strtod(((MATSDKEventItem*)items->m_items)[i].revenue, NULL);
        
        // Create a MATEventItem
        jobject jeventitemobj = jni_env->NewObject(clsMATEventItem, constructorID,
            nameVal,
            ((MATSDKEventItem*)items->m_items)[i].quantity,
            unitPrice,
            revenue,
            att1Val,
            att2Val,
            att3Val,
            att4Val,
            att5Val);

        // Add the MATEventItem to the List
        jboolean jbool = jni_env->CallBooleanMethod(jlistobj, list_add_mid, jeventitemobj);

        jni_env->DeleteLocalRef(nameVal);
        jni_env->DeleteLocalRef(att1Val);
        jni_env->DeleteLocalRef(att2Val);
        jni_env->DeleteLocalRef(att3Val);
        jni_env->DeleteLocalRef(att4Val);
        jni_env->DeleteLocalRef(att5Val);
    }

    jni_env->CallVoidMethod(g_Obj, g_MATTrackActionForEventIdOrNameItems, eventIdOrName_jstr, jlistobj, refId_jstr, revenue_jstr, currencyCode_jstr, transactionState, receipt_jstr, receiptSignature_jstr);
    
    jni_env->DeleteLocalRef(eventIdOrName_jstr);
    jni_env->DeleteLocalRef(refId_jstr);
    jni_env->DeleteLocalRef(revenue_jstr);
    jni_env->DeleteLocalRef(currencyCode_jstr);
    jni_env->DeleteLocalRef(receipt_jstr);
    jni_env->DeleteLocalRef(receiptSignature_jstr);
}

void MATStartAppToAppTracking_platform(const char* targetAppId, const char* advertiserId, const char* offerId, const char* publisherId, bool shouldRedirect)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    
    jstring targetAppIdUTF = env->NewStringUTF(targetAppId);
    jstring advertiserIdUTF = env->NewStringUTF(advertiserId);
    jstring offerIdUTF = env->NewStringUTF(offerId);
    jstring publisherIdUTF = env->NewStringUTF(publisherId);
    
    // Call setTracking from Android SDK
    env->CallVoidMethod(g_Obj, g_MATStartAppToAppTracking, advertiserIdUTF, targetAppIdUTF, publisherIdUTF, offerIdUTF, shouldRedirect);
    
    env->DeleteLocalRef(targetAppIdUTF);
    env->DeleteLocalRef(advertiserIdUTF);
    env->DeleteLocalRef(offerIdUTF);
    env->DeleteLocalRef(publisherIdUTF);
    
    return;
}

// Set Methods
void MATSetPackageName_platform(const char* packageName)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring packageName_jstr = env->NewStringUTF(packageName);
    env->CallVoidMethod(g_Obj, g_MATSetPackageName, packageName_jstr);
    env->DeleteLocalRef(packageName_jstr);
}

void MATSetCurrencyCode_platform(const char* currencyCode)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(currencyCode);
    env->CallVoidMethod(g_Obj, g_MATSetCurrencyCode, data_jstr);
    env->DeleteLocalRef(data_jstr);
}

void MATSetUserEmail_platform(const char* userEmail)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(userEmail);
    env->CallVoidMethod(g_Obj, g_MATSetUserEmail, data_jstr);
    env->DeleteLocalRef(data_jstr);
}

void MATSetUserId_platform(const char* userId)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(userId);
    env->CallVoidMethod(g_Obj, g_MATSetUserId, data_jstr);
    env->DeleteLocalRef(data_jstr);
}

void MATSetUserName_platform(const char* userName)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(userName);
    env->CallVoidMethod(g_Obj, g_MATSetUserName, data_jstr);
    env->DeleteLocalRef(data_jstr);
}

void MATSetFacebookUserId_platform(const char* userId)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(userId);
    env->CallVoidMethod(g_Obj, g_MATSetFacebookUserId, data_jstr);
    env->DeleteLocalRef(data_jstr);
}

void MATSetTwitterUserId_platform(const char* userId)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(userId);
    env->CallVoidMethod(g_Obj, g_MATSetTwitterUserId, data_jstr);
    env->DeleteLocalRef(data_jstr);
}

void MATSetGoogleUserId_platform(const char* userId)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(userId);
    env->CallVoidMethod(g_Obj, g_MATSetGoogleUserId, data_jstr);
    env->DeleteLocalRef(data_jstr);
}

void MATSetGoogleAdvertisingId_platform(const char* googleId)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(googleId);
    env->CallVoidMethod(g_Obj, g_MATSetGoogleAdvertisingId, data_jstr);
    env->DeleteLocalRef(data_jstr);
}

void MATSetEventAttribute1_platform(const char* attr)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(attr);
    env->CallVoidMethod(g_Obj, g_MATSetEventAttribute1, data_jstr);
    env->DeleteLocalRef(data_jstr);
}

void MATSetEventAttribute2_platform(const char* attr)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(attr);
    env->CallVoidMethod(g_Obj, g_MATSetEventAttribute2, data_jstr);
    env->DeleteLocalRef(data_jstr);
}

void MATSetEventAttribute3_platform(const char* attr)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(attr);
    env->CallVoidMethod(g_Obj, g_MATSetEventAttribute3, data_jstr);
    env->DeleteLocalRef(data_jstr);
}

void MATSetEventAttribute4_platform(const char* attr)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(attr);
    env->CallVoidMethod(g_Obj, g_MATSetEventAttribute4, data_jstr);
    env->DeleteLocalRef(data_jstr);
}

void MATSetEventAttribute5_platform(const char* attr)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(attr);
    env->CallVoidMethod(g_Obj, g_MATSetEventAttribute5, data_jstr);
    env->DeleteLocalRef(data_jstr);
}

void MATSetExistingUser_platform(bool isExisting)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_MATSetExistingUser, isExisting);
}

void MATSetSiteId_platform(const char* siteId)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(siteId);
    env->CallVoidMethod(g_Obj, g_MATSetSiteId, data_jstr);
    env->DeleteLocalRef(data_jstr);
}
void MATSetTRUSTeId_platform(const char* tpid)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(tpid);
    env->CallVoidMethod(g_Obj, g_MATSetTRUSTeId, data_jstr);
    env->DeleteLocalRef(data_jstr);
}
void MATSetDebugMode_platform(bool shouldDebug)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_MATSetDebugMode, shouldDebug);
}

void MATSetAllowDuplicates_platform(bool allowDuplicates)
{
	JNIEnv* env = s3eEdkJNIGetEnv();
	env->CallVoidMethod(g_Obj, g_MATSetAllowDuplicates, allowDuplicates);
}

void MATSetAge_platform(int age)
{
	JNIEnv* env = s3eEdkJNIGetEnv();
	env->CallVoidMethod(g_Obj, g_MATSetAge, age);
}

void MATSetGender_platform(int gender)
{
	JNIEnv* env = s3eEdkJNIGetEnv();
	env->CallVoidMethod(g_Obj, g_MATSetGender, gender);
}

void MATSetLocation_platform(const char * latitude, const char * longitude, const char * altitude)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_MATSetLocation, latitude, longitude, altitude);
}

// iOS only functions that do nothing on Android

void MATSetAppleAdvertisingIdentifier_platform(const char* appleAdvertisingIdentifier, bool trackingEnabled)
{
    
}

void MATSetAppleVendorIdentifier_platform(const char* appleVendorIdentifier)
{
    
}

void MATSetAppAdTracking_platform(bool enable)
{
    
}

void MATSetDelegate_platform(bool enable)
{
    
}

void MATSetJailbroken_platform(bool isJailbroken)
{
    
}

void MATSetRedirectUrl_platform(const char* redirectUrl)
{
    
}

void MATSetShouldAutoDetectJailbroken_platform(bool shouldAutoDetect)
{
    
}

void MATSetShouldAutoGenerateAppleVendorIdentifier_platform(bool shouldAutoGenerate)
{
    
}

void MATSetUseCookieTracking_platform(bool useCookieTracking)
{
    
}