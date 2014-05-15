/*
java implementation of the GAIDWrapper extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import com.ideaworks3d.marmalade.LoaderAPI;

import com.google.android.gms.ads.identifier.AdvertisingIdClient;
import com.google.android.gms.ads.identifier.AdvertisingIdClient.Info;
import com.google.android.gms.common.GooglePlayServicesNotAvailableException;
import com.google.android.gms.common.GooglePlayServicesRepairableException;
import java.io.IOException;

class GAIDWrapper
{
    public native void native_onGAIDCallback(String gaid, boolean isLAT);

    public void GAIDGetGoogleAdvertisingId()
    {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Info adInfo = AdvertisingIdClient.getAdvertisingIdInfo(LoaderAPI.getActivity());
                    native_onGAIDCallback(adInfo.getId(), adInfo.isLimitAdTrackingEnabled());
                } catch (IOException e) {
                } catch (GooglePlayServicesNotAvailableException e) {
                } catch (GooglePlayServicesRepairableException e) {
                }
            }
        }).start();
    }
}
