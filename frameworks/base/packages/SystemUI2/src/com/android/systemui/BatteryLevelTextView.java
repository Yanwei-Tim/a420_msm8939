package com.android.systemui;

import android.app.ActivityManager;
import android.content.Context;
import android.os.Handler;
import android.os.UserHandle;
import android.provider.Settings;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.android.systemui.statusbar.policy.BatteryController;

public class BatteryLevelTextView extends TextView implements
        BatteryController.BatteryStateChangeCallback{

    private final String TAG = "BatteryLevelTextView";
    
    private BatteryController mBatteryController;
    private boolean mShow = true;// android.os.SystemProperties.get("ro.product.name").equals("msm8916_64_a538u");


    public BatteryLevelTextView(Context context, AttributeSet attrs) {
        super(context, attrs);
        loadShowBatteryTextSetting();
        setVisibility(mShow ? View.VISIBLE : View.GONE);
    }

    private void loadShowBatteryTextSetting() {
        int currentUserId = ActivityManager.getCurrentUser();
      
    }

    @Override
    public void onBatteryLevelChanged(int level, boolean pluggedIn, boolean charging) {
       Log.i(TAG, "level = " + level);
       setText(getResources().getString(R.string.battery_level_template, level));
    }

    public void setBatteryController(BatteryController batteryController) {
        mBatteryController = batteryController;
        mBatteryController.addStateChangedCallback(this);
    }

    @Override
    public void onPowerSaveChanged() {
        // Not used
    }

    @Override
    public void onAttachedToWindow() {
        super.onAttachedToWindow();
      
    }

    @Override
    public void onDetachedFromWindow() {
        super.onDetachedFromWindow();
      
        if (mBatteryController != null) {
            mBatteryController.removeStateChangedCallback(this);
        }
    }
}
