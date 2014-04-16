/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */

#include "s3eExt.h"
#include "IwDebug.h"
#include "s3eDevice.h"


#include "IFAWrapper.h"


#ifndef S3E_EXT_SKIP_LOADER_CALL_LOCK
// For MIPs (and WP8) platform we do not have asm code for stack switching
// implemented. So we make LoaderCallStart call manually to set GlobalLock
#if defined __mips || defined S3E_ANDROID_X86 || (defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP))
#define LOADER_CALL_LOCK
#endif
#endif

/**
 * Definitions for functions types passed to/from s3eExt interface
 */
typedef const char*(*IFAGetAppleAdvertisingIdentifier_t)();
typedef       bool(*IFAGetIsAdvertisingTrackingEnabled_t)();

/**
 * struct that gets filled in by IFAWrapperRegister
 */
typedef struct IFAWrapperFuncs
{
    IFAGetAppleAdvertisingIdentifier_t m_IFAGetAppleAdvertisingIdentifier;
    IFAGetIsAdvertisingTrackingEnabled_t m_IFAGetIsAdvertisingTrackingEnabled;
} IFAWrapperFuncs;

static IFAWrapperFuncs g_Ext;
static bool g_GotExt = false;
static bool g_TriedExt = false;
static bool g_TriedNoMsgExt = false;

static bool _extLoad()
{
    if (!g_GotExt && !g_TriedExt)
    {
        s3eResult res = s3eExtGetHash(0xa5e30816, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        else
            s3eDebugAssertShow(S3E_MESSAGE_CONTINUE_STOP_IGNORE,                 "error loading extension: IFAWrapper");

        g_TriedExt = true;
        g_TriedNoMsgExt = true;
    }

    return g_GotExt;
}

static bool _extLoadNoMsg()
{
    if (!g_GotExt && !g_TriedNoMsgExt)
    {
        s3eResult res = s3eExtGetHash(0xa5e30816, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        g_TriedNoMsgExt = true;
        if (g_TriedExt)
            g_TriedExt = true;
    }

    return g_GotExt;
}

s3eBool IFAWrapperAvailable()
{
    _extLoadNoMsg();
    return g_GotExt ? S3E_TRUE : S3E_FALSE;
}

const char* IFAGetAppleAdvertisingIdentifier()
{
    IwTrace(IFAWRAPPER_VERBOSE, ("calling IFAWrapper[0] func: IFAGetAppleAdvertisingIdentifier"));

    if (!_extLoad())
        return NULL;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    const char* ret = g_Ext.m_IFAGetAppleAdvertisingIdentifier();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return ret;
}

bool IFAGetIsAdvertisingTrackingEnabled()
{
    IwTrace(IFAWRAPPER_VERBOSE, ("calling IFAWrapper[1] func: IFAGetIsAdvertisingTrackingEnabled"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    bool ret = g_Ext.m_IFAGetIsAdvertisingTrackingEnabled();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return ret;
}