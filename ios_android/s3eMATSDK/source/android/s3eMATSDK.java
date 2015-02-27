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

import com.mobileapptracker.MATEventItem;
import com.mobileapptracker.MobileAppTracker;

import android.R;
import android.graphics.Typeface;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.TextView;

class s3eMATSDK
{
    MobileAppTracker mat;
    
    public void MATStartMobileAppTracker(String adId, String convKey)
    {
        MobileAppTracker.init(LoaderAPI.getActivity(), adId, convKey);
        mat = MobileAppTracker.getInstance();
        mat.setPluginName("marmalade");
    }
    public void MATMeasureSession()
    {
        mat.measureSession();
    }
    
    public void MATMeasureAction(String eventIdOrName)
    {
        mat.measureAction(eventIdOrName, 0, null, null);
    }
    
    public void MATMeasureActionWithReferenceId(String eventIdOrName, String refId)
    {
        mat.measureAction(eventIdOrName, 0, null, refId);
    }
    
    public void MATMeasureActionWithRevenue(String eventIdOrName, String refId, String revenueAmount, String currencyCode)
    {
        mat.measureAction(eventIdOrName, Double.parseDouble(revenueAmount), currencyCode, refId);
    }
    
    // items is one or more event item hash maps
    public void MATMeasureActionWithItems(String eventIdOrName, List<MATEventItem> items, String refId, String revenueAmount, String currencyCode, int transactionState, String receipt, String receiptSignature)
    {
        if (receiptSignature != null && receiptSignature.length() > 0) {
            mat.measureAction(eventIdOrName, items, Double.parseDouble(revenueAmount), currencyCode, refId, receipt, receiptSignature);
        } else {
            mat.measureAction(eventIdOrName, items, Double.parseDouble(revenueAmount), currencyCode, refId);
        }
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
    
    public void MATSetGoogleAdvertisingId(String googleId, boolean limitAdTracking)
    {
        mat.setGoogleAdvertisingId(googleId, limitAdTracking);
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

    public void MATSetEventContentType(String contentType)
    {
        mat.setEventContentType(contentType);
    }

    public void MATSetEventContentId(String contentId)
    {
        mat.setEventContentId(contentId);
    }

    public void MATSetEventLevel(int level)
    {
        mat.setEventLevel(level);
    }

    public void MATSetEventQuantity(int quantity)
    {
        mat.setEventQuantity(quantity);
    }

    public void MATSetEventSearchString(String searchString)
    {
        mat.setEventSearchString(searchString);
    }

    public void MATSetEventRating(float rating)
    {
        mat.setEventRating(rating);
    }

    public void MATSetEventDate1(Date date)
    {
        mat.setEventDate1(date);
    }

    public void MATSetEventDate2(Date date)
    {
        mat.setEventDate2(date);
    }

    public void MATSetExistingUser(boolean isExisting)
    {
        mat.setExistingUser(isExisting);
    }

    public void MATSetFacebookEventLogging(boolean enable)
    {
        mat.setFacebookEventLogging(LoaderAPI.getActivity(), enable);
    }

    public void MATSetPayingUser(boolean isPaying)
    {
        mat.setIsPayingUser(isPaying);
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
    
    public void MATSetLocation(double latitude, double longitude)
    {
        mat.setLatitude(latitude);
        mat.setLongitude(longitude);
    }
    
    public void MATSetLocationWithAltitude(double latitude, double longitude, double altitude)
    {
        mat.setLatitude(latitude);
        mat.setLongitude(longitude);
        mat.setAltitude(altitude);
    }
    
    public boolean MATGetIsPayingUser()
    {
        return mat.getIsPayingUser();
    }
    
    public String MATGetMatId()
    {
        return mat.getMatId();
    }
    
    public String MATGetOpenLogId()
    {
        return mat.getOpenLogId();
    }
    
    public String MATCheckForDeferredDeeplink(int timeout)
    {
        return mat.checkForDeferredDeeplink(timeout);
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
