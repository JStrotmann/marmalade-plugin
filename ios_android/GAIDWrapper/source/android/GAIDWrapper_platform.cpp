/*
 * android-specific implementation of the GAIDWrapper extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "GAIDWrapper_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_GAIDGetGoogleAdvertisingId;

void JNICALL native_onGAIDCallback(JNIEnv *env, jobject obj, jstring gaid, jboolean isLAT);

s3eResult GAIDWrapperInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("GAIDWrapper");
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
    g_GAIDGetGoogleAdvertisingId = env->GetMethodID(cls, "GAIDGetGoogleAdvertisingId", "()V");
    if (!g_GAIDGetGoogleAdvertisingId)
        goto fail;

    static const JNINativeMethod methods[]=
    {
        {"native_onGAIDCallback","(Ljava/lang/String;Z)V",(void*)&native_onGAIDCallback}
    };
    // Register the native hooks
    if(env->RegisterNatives(cls,methods,sizeof(methods)/sizeof(methods[0])))
        goto fail;

    IwTrace(GAIDWRAPPER, ("GAIDWRAPPER init success"));
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
        IwTrace(GAIDWrapper, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void GAIDWrapperTerminate_platform()
{
    // Add any platform-specific termination code here
}

void GAIDGetGoogleAdvertisingId_platform(s3eCallback cb)
{
    JNIEnv* env = s3eEdkJNIGetEnv();

    //register a one-shot callback
    s3eEdkCallbacksRegister(
        S3E_EXT_GAIDWRAPPER_HASH,
        S3E_GAID_CALLBACK_MAX, // max notification ID
        S3E_GAID_RECEIVED, // notification ID
        (s3eCallback)cb, // application side function to be called
        NULL, // pointer to custom data
        S3E_FALSE); // allow for multiple callbacks for this event

    env->CallVoidMethod(g_Obj, g_GAIDGetGoogleAdvertisingId);
}

// Native function called by java
void JNICALL native_onGAIDCallback(JNIEnv *env, jobject obj, jstring gaid, jboolean isLAT)
{
    s3eGoogleAdvertisingIdInformation response;

    const char *nativeString = env->GetStringUTFChars(gaid, 0);

    response.m_Gaid = nativeString;
    response.m_isLAT = (bool)isLAT;

    s3eEdkCallbacksEnqueue(
        S3E_EXT_GAIDWRAPPER_HASH,
        S3E_GAID_RECEIVED,
        &response,
        sizeof(s3eGoogleAdvertisingIdInformation));
}
