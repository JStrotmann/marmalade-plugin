#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "ExamplesMain.h"
#include "GAIDWrapper.h"
#include "IFAWrapper.h"
#include "IwDebug.h"
#include "s3e.h"
#include "s3eDevice.h"
#include "s3eMATSDK.h"

//Simple structure to track touches
struct CTouch
{
    int32 x; // position x
    int32 y; // position y
    bool active; // is touch active (currently down)
    int32 id; // touch's unique identifier
};


bool g_UseMultiTouch = false;
char g_TouchEventMsg[128] = {0};
#define MAX_TOUCHES 10


Button* btnInit = 0;
Button* btnSession = 0;
Button* btnActionWithRef = 0;
Button* btnActionWithItems = 0;
Button* btnSetDelegate = 0;
Button* btnSetDebugMode = 0;
Button* btnSetAllowDups = 0;
Button* btnSetter = 0;
Button* btnGetter = 0;

bool shouldDebug = false;
char g_package_name[128] = {0};
char g_site_id[128] = {0};

bool isPointInButton(s3ePointerEvent* event, Button* button)
{
    if (event->m_x < button->m_XPos)
        return false;
    
    if (event->m_x > button->m_XPos + button->m_Width)
        return false;
    
    if (event->m_y < button->m_YPos)
        return false;
    
    if (event->m_y > button->m_YPos + button->m_Height)
        return false;
    
    return true;
}

static int32 HandleMATOpenUrl(void *systemData, void *userData)
{
    const char *response = (const char *)systemData;
    IwTrace(MATSDKSAMPLE_VERBOSE, ("HandleMATOpenUrl CALLBACK %s, %p", response , userData));
    
    return 0;
}

void checkDeferredDeeplink()
{
    char strTimeout[32];
    sprintf(strTimeout, "%f", 750.0f); // 750ms
    MATCheckForDeferredDeeplink(strTimeout, &HandleMATOpenUrl);
}

// GAID callback function, called by Marmalade when the GAID is received
static int32 SetGAID(void *systemData, void *userData)
{
    s3eGoogleAdvertisingIdInformation* adInfo = (s3eGoogleAdvertisingIdInformation*)systemData;
    MATSetGoogleAdvertisingId(adInfo->m_Gaid, adInfo->m_isLAT);
    
    checkDeferredDeeplink();
    
    return 0;
}

void SingleTouchButtonCB(s3ePointerEvent* event)
{
    // Don't register press events, actions will occur on release.
    if (event->m_Pressed)
    {
        return;
    }
    else if (isPointInButton(event, btnInit))
    {
        MATStartMobileAppTracker("877", "8c14d6bbe466b65211e781d62e301eec");
        MATSetPackageName(g_package_name);
        MATSetSiteId(g_site_id);
        
        int os = s3eDeviceGetInt(S3E_DEVICE_OS);
        if (S3E_OS_ID_IPHONE == os)
        {
            MATSetAppleAdvertisingIdentifier(IFAGetAppleAdvertisingIdentifier(), IFAGetIsAdvertisingTrackingEnabled());
            
            checkDeferredDeeplink();
        }
        else if (S3E_OS_ID_ANDROID == os)
        {
            GAIDGetGoogleAdvertisingId(&SetGAID);
        }
        
        MATSetFacebookEventLogging(true, false);
        
        sprintf(g_TouchEventMsg, "`x666666 Initialize MAT with %s, %s", g_package_name, g_site_id);
    }
    else if (isPointInButton(event, btnSetDelegate))
    {
        MATSetDelegate(true);
        sprintf(g_TouchEventMsg, "`x666666 Set Delegate");
    }
    else if (isPointInButton(event, btnSetDebugMode))
    {
        MATSetDebugMode(true);
        sprintf(g_TouchEventMsg, "`x666666 Set Debug Mode");
    }
    else if (isPointInButton(event, btnSetAllowDups))
    {
        MATSetAllowDuplicates(true);
        sprintf(g_TouchEventMsg, "`x666666 Set AllowDuplicates");
    }
    else if (isPointInButton(event, btnSession))
    {
        MATMeasureSession();
        sprintf(g_TouchEventMsg, "`x666666 Measure Session");
    }
    else if (isPointInButton(event, btnActionWithRef))
    {
        char strRevenue[32];
        sprintf(strRevenue, "%f", 12.34f);
        
        MATMeasureActionWithRevenue("testDCLRev", "ref123", strRevenue, "GBP");
        sprintf(g_TouchEventMsg, "`x666666 Measure Action with Reference Id");
    }
    else if (isPointInButton(event, btnActionWithItems))
    {
        MATSDKEventItem *items = (MATSDKEventItem *)s3eMalloc(sizeof(MATSDKEventItem) * 2);
        
        char strUnitPrice1[32];
        sprintf(strUnitPrice1, "%f", 1.55f);
        
        char strRevenue1[32];
        sprintf(strRevenue1, "%f", 1.55f);
        
        strncpy(items[0].name, "coin", S3E_MATSDK_STRING_MAX);
        strncpy(items[0].unitPrice, strUnitPrice1, S3E_MATSDK_STRING_MAX);
        items[0].quantity = 1;
        strncpy(items[0].revenue, strRevenue1, S3E_MATSDK_STRING_MAX);
        strncpy(items[0].attribute1, "attrib_1_1", S3E_MATSDK_STRING_MAX);
        strncpy(items[0].attribute2, "attrib_1_2", S3E_MATSDK_STRING_MAX);
        strncpy(items[0].attribute3, "attrib_1_3", S3E_MATSDK_STRING_MAX);
        strncpy(items[0].attribute4, "attrib_1_4", S3E_MATSDK_STRING_MAX);
        strncpy(items[0].attribute5, "attrib_1_5", S3E_MATSDK_STRING_MAX);
        
        // Note: Even if your app does not use event item attributes,
        // you might have to add strncpy for each attribute 1-5 to make
        // sure that the app does not crash due to memory corruption.
        // ex. strncpy(items[0].attribute1-5, "", S3E_MATSDK_STRING_MAX);
        
        char strUnitPrice2[32];
        sprintf(strUnitPrice2, "%f", 2.10f);
        
        char strRevenue2[32];
        sprintf(strRevenue2, "%f", 2.10f);
        
        strncpy(items[1].name, "sword", S3E_MATSDK_STRING_MAX);
        strncpy(items[1].unitPrice, strUnitPrice2, S3E_MATSDK_STRING_MAX);
        items[1].quantity = 1;
        strncpy(items[1].revenue, strRevenue2, S3E_MATSDK_STRING_MAX);
        strncpy(items[1].attribute1, "attrib_2_1", S3E_MATSDK_STRING_MAX);
        strncpy(items[1].attribute3, "attrib_2_3", S3E_MATSDK_STRING_MAX);
        strncpy(items[1].attribute5, "attrib_2_5", S3E_MATSDK_STRING_MAX);
        
        MATArray array;
        array.m_count = 2;
        array.m_items = items;
        
        char strRevAmount[32];
        sprintf(strRevAmount, "%f", 13.67f);
        
        MATMeasureActionWithItems("testDCLEventItems",
                                &array,
                                "testdclitems",
                                strRevAmount,
                                "GBP",
                                0,
                                NULL,
                                NULL);
        
        sprintf(g_TouchEventMsg, "`x666666 Measure Action With Event Items");
    }
    else if (isPointInButton(event, btnSetter))
    {
        sprintf(g_TouchEventMsg, "`x666666 Test Setter Methods");
        
        char strLat[32];
        char strLong[32];
        char strAlt[32];
        sprintf(strLat, "%f", 12.34f);
        sprintf(strLong, "%f", 23.45f);
        sprintf(strAlt, "%f", 567.89f);
        
        MATSetAge(23);
        MATSetAppAdTracking(true);
        MATSetAppleAdvertisingIdentifier(IFAGetAppleAdvertisingIdentifier(), IFAGetIsAdvertisingTrackingEnabled());
        MATSetAppleVendorIdentifier("12345678-1234-1234-1234-123456789012");
        MATSetCurrencyCode("tempCurrencyCode");
        MATSetEventAttribute1("eventAttr1");
        MATSetEventAttribute2("eventAttr2");
        MATSetEventAttribute3("eventAttr3");
        MATSetEventAttribute4("eventAttr4");
        MATSetEventAttribute5("eventAttr5");
        MATSetEventContentType("coins");
        MATSetEventContentId("coin12345678");
        MATSetEventLevel(5);
        MATSetEventQuantity(7);
        MATSetEventSearchString("searchString");

        char strRating[32];
        sprintf(strRating, "%f", 3.5f);
        MATSetEventRating(strRating);
        
        struct timeval tv;
        gettimeofday(&tv, NULL);
        unsigned long long millisSinceEpoch = (unsigned long long)(tv.tv_sec) * 1000 + (unsigned long long)(tv.tv_usec) / 1000;

        char millisDate1[256];
        sprintf(millisDate1, "%llu", millisSinceEpoch);
        MATSetEventDate1(millisDate1);
        
        char millisDate2[256];
        sprintf(millisDate2, "%llu", millisSinceEpoch + 60 * 1000);
        MATSetEventDate2(millisDate2);
        
        MATSetExistingUser(false);
        MATSetFacebookEventLogging(true, false);
        MATSetFacebookUserId("tempFacebookId");
        MATSetGender(1);
        MATSetGoogleUserId("tempGoogleId");
        MATSetJailbroken(false);
        MATSetLocation(strLat, strLong);
        MATSetLocationWithAltitude(strLat, strLong, strAlt);
        MATSetPackageName("testPackageName");
        MATSetPayingUser(true);
        MATSetTRUSTeId("tempTrusteId");
        MATSetTwitterUserId("tempTwitterId");
        MATSetUseCookieTracking(false);
        MATSetUserEmail("tempUserEmail@tempUserCompany.com");
        MATSetUserId("tempUserId");
        MATSetUserName("tempUserName");
    }
    else if (isPointInButton(event, btnGetter))
    {
        const char* matId = MATGetMatId();
        const char* openLogId = MATGetOpenLogId();
        bool payingUser = MATGetIsPayingUser();
        
        sprintf(g_TouchEventMsg, "`x666666 Test Getter Methods");
        
        sprintf(g_TouchEventMsg, "`x666666 matId = %s,\nopenLogId = %s,\nisPayingUser = %s", matId, openLogId, (payingUser ? "true" : "false"));
    }

}

void SingleTouchMotionCB(s3ePointerMotionEvent* event)
{

}

//--------------------------------------------------------------------------
void ExampleInit()
{
    //Register for standard pointer events
    s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB, NULL);
    s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)SingleTouchMotionCB, NULL);
    
    // Init buttons.
    btnInit             = NewButton("Start MAT SDK");
    btnSetDelegate      = NewButton("Set Delegate");
    btnSetDebugMode     = NewButton("Set Debug Mode");
    btnSetAllowDups     = NewButton("Set Allow Duplicates");
    btnSession          = NewButton("Measure Session");
    btnActionWithRef    = NewButton("Measure Event With Ref");
    btnActionWithItems  = NewButton("Measure Event Items");
    btnSetter           = NewButton("Test Setter Methods");
    btnGetter           = NewButton("Test Getter Methods");
    
    int32 osInt = s3eDeviceGetInt(S3E_DEVICE_OS);
    if (osInt == S3E_OS_ID_ANDROID)
    {
        strcpy(g_package_name, "com.marmaladeandroidtest");
        strcpy(g_site_id, "7488");
    }
    else
    {
        strcpy(g_package_name, "2GLFC47AY5.com.hasoffers.marmaladeTestApp");
        strcpy(g_site_id, "6864");
    }
    SetButtonScale(2);
}

//--------------------------------------------------------------------------
void ExampleShutDown()
{
    s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB);
    s3ePointerUnRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)SingleTouchMotionCB);
    
    DeleteButtons();
}


//--------------------------------------------------------------------------
bool ExampleUpdate()
{
    s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB, NULL);
    s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)SingleTouchMotionCB, NULL);

    return true;
}

void ExampleRender()
{
    // Get pointer to the screen surface
    // (pixel depth is 2 bytes by default)
    uint16* screen = (uint16*)s3eSurfacePtr();
    int height = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);
    int width = s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
    int pitch = s3eSurfaceGetInt(S3E_SURFACE_PITCH);
    
    // Clear screen to white
    for (int i=0; i < height; i++)
    {
        memset((char*)screen + pitch * i, 255, (width * 2));
    }
    
    // This was causing an error to pop up.
    s3ePointerUpdate();
    
    ButtonsRender();
    
    s3eDebugPrint(20, 365, g_TouchEventMsg, 1);
}

void ExampleTerm()
{
}
