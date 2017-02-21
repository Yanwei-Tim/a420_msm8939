package com.lovdream.util;

import android.app.AppGlobals;
import android.os.Binder;
import android.os.RemoteException;
import android.os.SystemProperties;
import android.os.Process;
import android.content.pm.IPackageManager;
import android.text.TextUtils;
import android.util.Log;
/** {@hide} */
public class DeceptionUtil {
    private static boolean DEBUG = true;
    public static final String TAG = "DeceptionUtil";
    private static boolean mIsA420 = SystemProperties.get("ro.build.product").equals("msm8916_64_a420");
    //private static IPackageManager mPm;
    
    private static boolean sIsSystemReady;
            final static String[] pkgLists = {
            "com.qihoo360.mobilesafe.opti",
            "com.qihoo360.mobilesafe.opti_18dfsefe",
            "com.ludashi.benchmark",
            "com.antutu.tester",
            "com.uzywpq.cqlzahm",                //antutu yanji
            "com.antutu.information",
            "com.antutu.ABenchMark",
            "com.dmhxaq.kjdashkl",
            "com.antutu.ABenchMark5",
            "com.pctvtv.android.ttsx",                
            "com.antutu.yanji",
            "com.pctvtv.android.ttsx",
            "com.cpuid.cpu_z",                    //cpu_z
            "com.opda.checkoutdevice",            //zhuo da shi
            "com.example.pphelper",                //PP zhu shou
            "com.tyyj89.androidsuperinfo",        //shou ji  ying jian jian ce
            "com.pc.check",                        //android yanji
            "com.ray.imeicheck",                //shouji chu chang di cha xun
            "com.xiaomi.antifake",
            "com.xiaomi.antifake2"
        };
    public static boolean isShouldDeception(){
        if(!mIsA420) return false;
        IPackageManager pm = AppGlobals.getPackageManager();
        if(null == pm){
           return false;
        }
        int uid = Binder.getCallingUid();
        if(uid < Process.FIRST_APPLICATION_UID){//system process ignore.
            return false;
        }
        String pkgname = "";
        try{
           pkgname = pm.getNameForUid(uid);
           if(DEBUG){
               Log.d(TAG, pkgname);
           }
        }catch(RemoteException e){
           return false;
        }
        if(!TextUtils.isEmpty(pkgname) && findBenchmarkApk(pkgname)){
            return true;
        }
        return false;
    }
    
    public static boolean findBenchmarkApk(String pkgname){
        for(String name : pkgLists){
            if(name.equals(pkgname)){
                return true;
             }
        }
        return false;
    }
    public static void systemReady(){
        sIsSystemReady = true;
    }
}