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

static jmethodID g_MATMeasureSession;

static jmethodID g_MATMeasureAction;
static jmethodID g_MATMeasureActionWithReferenceId;
static jmethodID g_MATMeasureActionWithRevenue;
static jmethodID g_MATMeasureActionWithItems;

static jmethodID g_MATSetPackageName;

static jmethodID g_MATSetCurrencyCode;
static jmethodID g_MATSetUserEmail;
static jmethodID g_MATSetUserId;
static jmethodID g_MATSetUserName;
static jmethodID g_MATSetEventAttribute1;
static jmethodID g_MATSetEventAttribute2;
static jmethodID g_MATSetEventAttribute3;
static jmethodID g_MATSetEventAttribute4;
static jmethodID g_MATSetEventAttribute5;

static jmethodID g_MATSetEventContentType;
static jmethodID g_MATSetEventContentId;
static jmethodID g_MATSetEventLevel;
static jmethodID g_MATSetEventQuantity;
static jmethodID g_MATSetEventSearchString;
static jmethodID g_MATSetEventRating;
static jmethodID g_MATSetEventDate1;
static jmethodID g_MATSetEventDate2;

static jmethodID g_MATSetExistingUser;
static jmethodID g_MATSetFacebookUserId;
static jmethodID g_MATSetTwitterUserId;
static jmethodID g_MATSetGoogleUserId;
static jmethodID g_MATSetGoogleAdvertisingId;
static jmethodID g_MATSetSiteId;
static jmethodID g_MATSetTRUSTeId;
static jmethodID g_MATSetDebugMode;
static jmethodID g_MATSetAllowDuplicates;
static jmethodID g_MATSetFacebookEventLogging;

static jmethodID g_MATSetPayingUser;
static jmethodID g_MATGetIsPayingUser;

static jmethodID g_MATSetAge;
static jmethodID g_MATSetGender;
static jmethodID g_MATSetLocation;
static jmethodID g_MATSetLocationWithAltitude;

static jmethodID g_MATGetMatId;
static jmethodID g_MATGetOpenLogId;

static jmethodID g_MATCheckForDeferredDeeplink;

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

    g_MATMeasureSession = env->GetMethodID(cls, "MATMeasureSession", "()V");
    if (!g_MATMeasureSession)
        goto fail;

    g_MATMeasureAction = env->GetMethodID(cls, "MATMeasureAction", "(Ljava/lang/String;)V");
    if (!g_MATMeasureAction)
        goto fail;
    
    g_MATMeasureActionWithReferenceId = env->GetMethodID(cls, "MATMeasureActionWithReferenceId", "(Ljava/lang/String;Ljava/lang/String;)V");
    if (!g_MATMeasureActionWithReferenceId)
        goto fail;
    
    g_MATMeasureActionWithRevenue = env->GetMethodID(cls, "MATMeasureActionWithRevenue", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    if (!g_MATMeasureActionWithRevenue)
        goto fail;
    
    g_MATMeasureActionWithItems = env->GetMethodID(cls, "MATMeasureActionWithItems", "(Ljava/lang/String;Ljava/util/List;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;)V");
    if (!g_MATMeasureActionWithItems)
        goto fail;

    g_MATSetPackageName = env->GetMethodID(cls, "MATSetPackageName", "(Ljava/lang/String;)V");
    if (!g_MATSetPackageName)
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
    
    g_MATSetEventContentType = env->GetMethodID(cls, "MATSetEventContentType", "(Ljava/lang/String;)V");
    if (!g_MATSetEventContentType)
        goto fail;

    g_MATSetEventContentId = env->GetMethodID(cls, "MATSetEventContentId", "(Ljava/lang/String;)V");
    if (!g_MATSetEventContentId)
        goto fail;

    g_MATSetEventLevel = env->GetMethodID(cls, "MATSetEventLevel", "(I)V");
    if (!g_MATSetEventLevel)
        goto fail;

    g_MATSetEventQuantity = env->GetMethodID(cls, "MATSetEventQuantity", "(I)V");
    if (!g_MATSetEventQuantity)
        goto fail;

    g_MATSetEventSearchString = env->GetMethodID(cls, "MATSetEventSearchString", "(Ljava/lang/String;)V");
    if (!g_MATSetEventSearchString)
        goto fail;

    g_MATSetEventRating = env->GetMethodID(cls, "MATSetEventRating", "(F)V");
    if (!g_MATSetEventRating)
        goto fail;

    g_MATSetEventDate1 = env->GetMethodID(cls, "MATSetEventDate1", "(Ljava/util/Date;)V");
    if (!g_MATSetEventDate1)
        goto fail;

    g_MATSetEventDate2 = env->GetMethodID(cls, "MATSetEventDate2", "(Ljava/util/Date;)V");
    if (!g_MATSetEventDate2)
        goto fail;

    g_MATSetGoogleAdvertisingId = env->GetMethodID(cls, "MATSetGoogleAdvertisingId", "(Ljava/lang/String;Z)V");
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

    g_MATSetFacebookEventLogging = env->GetMethodID(cls, "MATSetFacebookEventLogging", "(Z)V");
    if (!g_MATSetFacebookEventLogging)
        goto fail;
    
    g_MATSetPayingUser = env->GetMethodID(cls, "MATSetPayingUser", "(Z)V");
    if (!g_MATSetPayingUser)
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
    
    g_MATSetLocation = env->GetMethodID(cls, "MATSetLocation", "(DD)V");
    if (!g_MATSetLocation)
        goto fail;
    
    g_MATSetLocationWithAltitude = env->GetMethodID(cls, "MATSetLocationWithAltitude", "(DDD)V");
    if (!g_MATSetLocationWithAltitude)
        goto fail;
    
    g_MATGetIsPayingUser = env->GetMethodID(cls, "MATGetIsPayingUser", "()Z");
    if (!g_MATGetIsPayingUser)
        goto fail;
    
    g_MATGetMatId = env->GetMethodID(cls, "MATGetMatId", "()Ljava/lang/String;");
    if (!g_MATGetMatId)
        goto fail;
    
    g_MATGetOpenLogId = env->GetMethodID(cls, "MATGetOpenLogId", "()Ljava/lang/String;");
    if (!g_MATGetOpenLogId)
        goto fail;

    g_MATCheckForDeferredDeeplink = env->GetMethodID(cls, "MATCheckForDeferredDeeplink", "(I)Ljava/lang/String;");
    if (!g_MATCheckForDeferredDeeplink)
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

void MATMeasureSession_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    
    env->CallVoidMethod(g_Obj, g_MATMeasureSession);
}

void MATMeasureAction_platform(const char* eventIdOrName)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring evt_jstr = env->NewStringUTF(eventIdOrName);
    
    env->CallVoidMethod(g_Obj, g_MATMeasureAction, evt_jstr);
    
    env->DeleteLocalRef(evt_jstr);
}

void MATMeasureActionWithReferenceId_platform(const char* eventIdOrName, const char* refId)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring evt_jstr = env->NewStringUTF(eventIdOrName);
    jstring ref_jstr = env->NewStringUTF(refId);
    
    env->CallVoidMethod(g_Obj, g_MATMeasureActionWithReferenceId, evt_jstr, ref_jstr);
    
    env->DeleteLocalRef(evt_jstr);
    env->DeleteLocalRef(ref_jstr);
}

void MATMeasureActionWithRevenue_platform(const char* eventIdOrName, const char* refId, const char* revenueAmount, const char* currencyCode)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    
    jstring evt_jstr = env->NewStringUTF(eventIdOrName);
    jstring ref_jstr = env->NewStringUTF(refId);
    jstring rev_jstr = env->NewStringUTF(revenueAmount);
    jstring cur_jstr = env->NewStringUTF(currencyCode);
    
    env->CallVoidMethod(g_Obj, g_MATMeasureActionWithRevenue, evt_jstr, ref_jstr, rev_jstr, cur_jstr);
    
    env->DeleteLocalRef(evt_jstr);
    env->DeleteLocalRef(ref_jstr);
    env->DeleteLocalRef(rev_jstr);
    env->DeleteLocalRef(cur_jstr);
}

void MATMeasureActionWithItems_platform(const char* eventIdOrName, const MATArray* items, const char* refId, const char* revenueAmount, const char* currencyCode, uint8 transactionState, const char* receipt, const char* receiptSignature)
{
    JNIEnv* jni_env = s3eEdkJNIGetEnv();
    
    // local variables for the track action
    jstring evt_jstr = jni_env->NewStringUTF(eventIdOrName);
    jstring ref_jstr = jni_env->NewStringUTF(refId);
    jstring rev_jstr = jni_env->NewStringUTF(revenueAmount);
    jstring cur_jstr = jni_env->NewStringUTF(currencyCode);
    jstring rec_jstr = jni_env->NewStringUTF(receipt);
    jstring sig_jstr = jni_env->NewStringUTF(receiptSignature);
    
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
        jstring attr1Val = jni_env->NewStringUTF(((MATSDKEventItem*)items->m_items)[i].attribute1);
        jstring attr2Val = jni_env->NewStringUTF(((MATSDKEventItem*)items->m_items)[i].attribute2);
        jstring attr3Val = jni_env->NewStringUTF(((MATSDKEventItem*)items->m_items)[i].attribute3);
        jstring attr4Val = jni_env->NewStringUTF(((MATSDKEventItem*)items->m_items)[i].attribute4);
        jstring attr5Val = jni_env->NewStringUTF(((MATSDKEventItem*)items->m_items)[i].attribute5);

        double unitPrice = strtod(((MATSDKEventItem*)items->m_items)[i].unitPrice, NULL);
        double revenue = strtod(((MATSDKEventItem*)items->m_items)[i].revenue, NULL);
        
        // Create a MATEventItem
        jobject jeventitemobj = jni_env->NewObject(clsMATEventItem, constructorID,
            nameVal,
            ((MATSDKEventItem*)items->m_items)[i].quantity,
            unitPrice,
            revenue,
            attr1Val,
            attr2Val,
            attr3Val,
            attr4Val,
            attr5Val);

        // Add the MATEventItem to the List
        jboolean jbool = jni_env->CallBooleanMethod(jlistobj, list_add_mid, jeventitemobj);

        jni_env->DeleteLocalRef(nameVal);
        jni_env->DeleteLocalRef(attr1Val);
        jni_env->DeleteLocalRef(attr2Val);
        jni_env->DeleteLocalRef(attr3Val);
        jni_env->DeleteLocalRef(attr4Val);
        jni_env->DeleteLocalRef(attr5Val);
    }

    jni_env->CallVoidMethod(g_Obj, g_MATMeasureActionWithItems, evt_jstr, jlistobj, ref_jstr, rev_jstr, cur_jstr, transactionState, rec_jstr, sig_jstr);
    
    jni_env->DeleteLocalRef(evt_jstr);
    jni_env->DeleteLocalRef(ref_jstr);
    jni_env->DeleteLocalRef(rev_jstr);
    jni_env->DeleteLocalRef(cur_jstr);
    jni_env->DeleteLocalRef(rec_jstr);
    jni_env->DeleteLocalRef(sig_jstr);
}

void MATStartAppToAppTracking_platform(const char* targetAppId, const char* advertiserId, const char* offerId, const char* publisherId, bool shouldRedirect)
{
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

void MATSetGoogleAdvertisingId_platform(const char* googleId, bool limitAdTracking)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(googleId);
    
    env->CallVoidMethod(g_Obj, g_MATSetGoogleAdvertisingId, data_jstr, limitAdTracking);
    
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

void MATSetEventContentType_platform(const char* contentType)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(contentType);
    
    env->CallVoidMethod(g_Obj, g_MATSetEventContentType, data_jstr);
    
    env->DeleteLocalRef(data_jstr);
}

void MATSetEventContentId_platform(const char* contentId)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(contentId);
    
    env->CallVoidMethod(g_Obj, g_MATSetEventContentId, data_jstr);
    
    env->DeleteLocalRef(data_jstr);
}

void MATSetEventLevel_platform(int level)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    
    env->CallVoidMethod(g_Obj, g_MATSetEventLevel, level);
}

void MATSetEventQuantity_platform(int quantity)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    
    env->CallVoidMethod(g_Obj, g_MATSetEventQuantity, quantity);
}

void MATSetEventSearchString_platform(const char* searchString)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring data_jstr = env->NewStringUTF(searchString);
    
    env->CallVoidMethod(g_Obj, g_MATSetEventSearchString, data_jstr);
    
    env->DeleteLocalRef(data_jstr);
}

void MATSetEventRating_platform(const char* rating)
{
    JNIEnv* env = s3eEdkJNIGetEnv();

    // Convert from string to float
    float ratingFloat = (float)strtod(rating, NULL);
    env->CallVoidMethod(g_Obj, g_MATSetEventRating, ratingFloat);
}

void MATSetEventDate1_platform(const char* dateMillis)
{
    JNIEnv* env = s3eEdkJNIGetEnv();

    // Convert from string to Java Date
    jstring dateMillisUTF = env->NewStringUTF(dateMillis);
    jclass clsDouble = env->FindClass("java/lang/Double");
    jmethodID ctrDouble = env->GetMethodID(clsDouble, "<init>", "(Ljava/lang/String;)V");
    jobject objDouble = env->NewObject(clsDouble, ctrDouble, dateMillisUTF);
    
    jmethodID methodLongValue = env->GetMethodID(clsDouble, "longValue", "()J");
    jlong millis = env->CallLongMethod(objDouble, methodLongValue);
    
    jclass clsDate = env->FindClass("java/util/Date");
    jmethodID ctrDate = env->GetMethodID(clsDate, "<init>", "(J)V");
    jobject objDate = env->NewObject(clsDate, ctrDate, millis);
    
    env->CallVoidMethod(g_Obj, g_MATSetEventDate1, objDate);

    env->DeleteLocalRef(dateMillisUTF);
    env->DeleteLocalRef(objDouble);
    env->DeleteLocalRef(objDate);
}

void MATSetEventDate2_platform(const char* dateMillis)
{
    JNIEnv* env = s3eEdkJNIGetEnv();

    jstring dateMillisUTF = env->NewStringUTF(dateMillis);
    jclass clsDouble = env->FindClass("java/lang/Double");
    jmethodID ctrDouble = env->GetMethodID(clsDouble, "<init>", "(Ljava/lang/String;)V");
    jobject objDouble = env->NewObject(clsDouble, ctrDouble, dateMillisUTF);
    
    jmethodID methodLongValue = env->GetMethodID(clsDouble, "longValue", "()J");
    jlong millis = env->CallLongMethod(objDouble, methodLongValue);
    
    jclass clsDate = env->FindClass("java/util/Date");
    jmethodID ctrDate = env->GetMethodID(clsDate, "<init>", "(J)V");
    jobject objDate = env->NewObject(clsDate, ctrDate, millis);
    
    env->CallVoidMethod(g_Obj, g_MATSetEventDate2, objDate);

    env->DeleteLocalRef(dateMillisUTF);
    env->DeleteLocalRef(objDouble);
    env->DeleteLocalRef(objDate);
}

void MATSetExistingUser_platform(bool isExisting)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    
    env->CallVoidMethod(g_Obj, g_MATSetExistingUser, isExisting);
}

void MATSetFacebookEventLogging_platform(bool enable, bool limitUsage)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    
    env->CallVoidMethod(g_Obj, g_MATSetFacebookEventLogging, enable);
}

void MATSetPayingUser_platform(bool isPaying)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    
    env->CallVoidMethod(g_Obj, g_MATSetPayingUser, isPaying);
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

void MATSetLocation_platform(const char * latitudeStr, const char * longitudeStr)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    
    // Convert from string to double
    double latitude = strtod(latitudeStr, NULL);
    double longitude = strtod(longitudeStr, NULL);
    env->CallVoidMethod(g_Obj, g_MATSetLocation, latitude, longitude);
}

void MATSetLocationWithAltitude_platform(const char * latitudeStr, const char * longitudeStr, const char * altitudeStr)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    
    // Convert from string to double
    double latitude = strtod(latitudeStr, NULL);
    double longitude = strtod(longitudeStr, NULL);
    double altitude = strtod(altitudeStr, NULL);
    env->CallVoidMethod(g_Obj, g_MATSetLocationWithAltitude, latitude, longitude, altitude);
}

bool MATGetIsPayingUser_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    
    jboolean payingUser_jboolean = (jboolean)env->CallBooleanMethod(g_Obj, g_MATGetIsPayingUser);
    
    bool payingUser_bool = (bool)payingUser_jboolean;
    
    return payingUser_bool;
}

const char* MATGetMatId_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    
    jstring matId_jstr = (jstring)env->CallObjectMethod(g_Obj, g_MATGetMatId);
    
    const char *matId_cstr = env->GetStringUTFChars(matId_jstr, 0);
    
    return matId_cstr;
}

const char* MATGetOpenLogId_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    
    jstring openLogId_jstr = (jstring)env->CallObjectMethod(g_Obj, g_MATGetOpenLogId);
    
    const char *openLogId_cstr = env->GetStringUTFChars(openLogId_jstr, 0);

    return openLogId_cstr;
}

void MATCheckForDeferredDeeplink_platform(const char* timeoutStr, s3eCallback cb)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    
    int timeout = strtod(timeoutStr, NULL);
    env->CallObjectMethod(g_Obj, g_MATCheckForDeferredDeeplink, timeout);
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