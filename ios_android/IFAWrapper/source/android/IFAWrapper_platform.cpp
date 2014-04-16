/*
 * android-specific implementation of the IFAWrapper extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "IFAWrapper_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_IFAGetAppleAdvertisingIdentifier;
static jmethodID g_IFAGetIsAdvertisingTrackingEnabled;

s3eResult IFAWrapperInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("IFAWrapper");
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
    g_IFAGetAppleAdvertisingIdentifier = env->GetMethodID(cls, "IFAGetAppleAdvertisingIdentifier", "()Ljava/lang/String;");
    if (!g_IFAGetAppleAdvertisingIdentifier)
        goto fail;

    g_IFAGetIsAdvertisingTrackingEnabled = env->GetMethodID(cls, "IFAGetIsAdvertisingTrackingEnabled", "()Z");
    if (!g_IFAGetIsAdvertisingTrackingEnabled)
        goto fail;



    IwTrace(IFAWRAPPER, ("IFAWRAPPER init success"));
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
        IwTrace(IFAWrapper, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void IFAWrapperTerminate_platform()
{
    // Add any platform-specific termination code here
}

// iOS only functions that do nothing on Android

const char* IFAGetAppleAdvertisingIdentifier_platform()
{
    return NULL;
}

bool IFAGetIsAdvertisingTrackingEnabled_platform()
{
    return false;
}
