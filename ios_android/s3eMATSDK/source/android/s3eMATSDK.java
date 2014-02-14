/*
java implementation of the s3eMATSDK extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import com.ideaworks3d.marmalade.LoaderAPI;

import java.util.*;

import android.view.View;
import android.view.ViewGroup;

import com.mobileapptracker.MATEventItem;
import com.mobileapptracker.MobileAppTracker;
import android.util.Log;

import android.R;
import android.widget.Button;
import android.widget.TextView;
import android.graphics.Typeface;
import android.view.Gravity;
import android.widget.LinearLayout;
import android.widget.FrameLayout;

class s3eMATSDK
{
    MobileAppTracker mat;
    
    public void MATStartMobileAppTracker(String adId, String convKey)
    {
        MobileAppTracker.init(LoaderAPI.getActivity(), adId, convKey);
        mat = MobileAppTracker.getInstance();
        mat.setPluginName("marmalade");
    }
    public void MATTrackSession()
    {
        mat.trackSession();
    }
    public void MATTrackSessionWithReferenceId(String refId)
    {
         mat.trackAction("session", 0, null, refId);
    }
    public void MATTrackActionForEventIdOrName(String eventIdOrName, String refId)
    {
        mat.trackAction(eventIdOrName, 0, null, refId);
    }
    
    // items is one or more event item hash maps
    public void MATTrackActionForEventIdOrNameItems(String eventIdOrName, List<MATEventItem> items, String refId, String revenueAmount, String currencyCode, int transactionState, String receipt, String receiptSignature)
    {
        if (receiptSignature != null && receiptSignature.length() > 0) {
            mat.trackAction(eventIdOrName, items, Double.parseDouble(revenueAmount), currencyCode, refId, receipt, receiptSignature);
        } else {
            mat.trackAction(eventIdOrName, items, Double.parseDouble(revenueAmount), currencyCode, refId);
        }
    }
    
    public void MATTrackAction(String eventIdOrName, String revenueAmount, String currencyCode)
    {
        mat.trackAction(eventIdOrName, Double.parseDouble(revenueAmount), currencyCode);
    }
    
    public void MATStartAppToAppTracking(String targetAppId, String advertiserId, String offerId, String publisherId, boolean shouldRedirect)
    {
        mat.setTracking(advertiserId, targetAppId, publisherId, offerId, shouldRedirect);
    }
    
    public void MATSetPackageName(String packageName)
    {
        mat.setPackageName(packageName);
    }
    
    public void MATSetCurrencyCode(String currencyCode)
    {
        mat.setCurrencyCode(currencyCode);
    }
    
    public void MATSetUserEmail(String userEmail)
    {
        mat.setUserEmail(userEmail);
    }
    
    public void MATSetUserId(String userId)
    {
        mat.setUserId(userId);
    }
    
    public void MATSetUserName(String userName)
    {
        mat.setUserName(userName);
    }

    public void MATSetFacebookUserId(String facebookUserId)
    {
        mat.setFacebookUserId(facebookUserId);
    }

    public void MATSetTwitterUserId(String twitterUserId)
    {
        mat.setTwitterUserId(twitterUserId);
    }

    public void MATSetGoogleUserId(String googleUserId)
    {
        mat.setGoogleUserId(googleUserId);
    }
    
    public void MATSetSiteId(String siteId)
    {
        mat.setSiteId(siteId);
    }
    
    public void MATSetTRUSTeId(String tpid)
    {
        mat.setTRUSTeId(tpid);
    }
    
    public void MATSetDebugMode(boolean shouldDebug)
    {
        mat.setDebugMode(shouldDebug);
    }
    
    public void MATSetGoogleAdvertisingId(String googleId)
    {
        mat.setGoogleAdvertisingId(googleId);
    }
    
    public void MATSetEventAttribute1(String attr)
    {
        mat.setEventAttribute1(attr);
    }
    
    public void MATSetEventAttribute2(String attr)
    {
        mat.setEventAttribute2(attr);
    }
    
    public void MATSetEventAttribute3(String attr)
    {
        mat.setEventAttribute3(attr);
    }
    
    public void MATSetEventAttribute4(String attr)
    {
        mat.setEventAttribute4(attr);
    }
    
    public void MATSetEventAttribute5(String attr)
    {
        mat.setEventAttribute5(attr);
    }
    
    public void MATSetExistingUser(boolean isExisting)
    {
        mat.setExistingUser(isExisting);
    }
    
    public void MATSetAllowDuplicates(boolean allowDuplicates)
    {
		mat.setAllowDuplicates(allowDuplicates);
    }
    
    public void MATSetAge(int age)
    {
		mat.setAge(age);
    }
    
    public void MATSetGender(int gender)
    {
		mat.setGender(1 == gender ? MobileAppTracker.GENDER_FEMALE : MobileAppTracker.GENDER_MALE);
    }
    
    public void MATSetLocation(double latitude, double longitude, double altitude)
    {
		mat.setLatitude(latitude);
        mat.setLongitude(longitude);
        mat.setAltitude(altitude);
    }
    
    public void MATSetAppAdTracking(boolean enable)
    {
        // not available in android
    }
    
    public void MATSetShouldAutoDetectJailbroken(boolean shouldAutoDetect)
    {
        // not available in android
    }
    
    public void MATSetShouldAutoGenerateAppleVendorIdentifier(boolean shouldAutoGenerate)
    {
        // not available in android
    }
    
    public void MATSetAppleAdvertisingIdentifier(String appleAdvertisingId, boolean trackingEnabled)
    {
        // not available in android
    }
    
    public void MATSetAppleVendorIdentifier(String appleVendorId)
    {
        // not available in android
    }
    
    public void MATSetJailbroken(boolean isJailbroken)
    {
        // not available in android
    }
    
    public void MATSetRedirectUrl(String redirectUrl)
    {
        // not available in android
    }
    
    public void MATSetUseCookieTracking(boolean useCookieTracking)
    {
        // not available in android
    }
}
