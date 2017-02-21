/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.systemui.qs.tiles;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.database.ContentObserver;
import android.net.ConnectivityManager;
import android.os.Handler;
import android.provider.Settings;
import android.provider.Settings.Global;
import android.util.Log;

import com.android.internal.logging.MetricsLogger;
import com.android.systemui.R;
import com.android.systemui.qs.GlobalSetting;
import com.android.systemui.qs.QSTile;
import com.android.systemui.qs.QSTile.ResourceIcon;

/** Quick settings tile: Airplane mode **/
public class PutoutSreentile extends QSTile<QSTile.BooleanState> {
    private final AnimationIcon mEnable =
            new AnimationIcon(R.drawable.ic_signal_airplane_enable_animation);
    private final AnimationIcon mDisable =
            new AnimationIcon(R.drawable.ic_signal_airplane_disable_animation);
    private final GlobalSetting mSetting;

    private boolean mListening;

    private DozeObserver mDozeObserver;
    public PutoutSreentile(Host host) {
        super(host);

        mSetting = new GlobalSetting(mContext, mHandler, Global.AIRPLANE_MODE_ON) {
            @Override
            protected void handleValueChanged(int value) {
                handleRefreshState(value);
            }
        };
        mDozeObserver = new DozeObserver(new Handler());
        
        mContext.getContentResolver().registerContentObserver(Settings.Secure.getUriFor(Settings.Secure.DOZE_ENABLED), false, mDozeObserver);
    }

    private class DozeObserver extends ContentObserver{

		public DozeObserver(Handler handler) {
			super(handler);
			// TODO Auto-generated constructor stub
		}
    	
    	public void  onChange(boolean selfChange)
    	{
    		refreshState();
    	}
    }
    
    @Override
    protected BooleanState newTileState() {
        return new BooleanState();
    }

    @Override
    public void handleClick() {
        MetricsLogger.action(mContext, getMetricsCategory(), !mState.value);
//        setEnabled(!mState.value);
//        mEnable.setAllowAnimation(true);
//        mDisable.setAllowAnimation(true);
        try {
        	  if(Settings.Secure.getInt(mContext.getContentResolver(),Settings.Secure.DOZE_ENABLED, 1 ) == 0 )
              {
              	Settings.Secure.putInt(mContext.getContentResolver(), Settings.Secure.DOZE_ENABLED, 1 );
              }else {
              	Settings.Secure.putInt(mContext.getContentResolver(), Settings.Secure.DOZE_ENABLED, 0);
      		  }
		} catch (Exception e) {
			Log.i(TAG, "Exception"+ e.getMessage()+"==========="+ e.getLocalizedMessage() + e.getCause());
		}
      
        refreshState();
    }

    private void setEnabled(boolean enabled) {
//        final ConnectivityManager mgr =
//                (ConnectivityManager) mContext.getSystemService(Context.CONNECTIVITY_SERVICE);
//        mgr.setAirplaneMode(enabled);
    }

    @Override
    protected void handleUpdateState(BooleanState state, Object arg) {
        final int value = arg instanceof Integer ? (Integer)arg : mSetting.getValue();
        state.value = true;
        state.visible = true;
        state.label = mContext.getString(R.string.qs_putoutscreen);  
        try {
        	 if(Settings.Secure.getInt(mContext.getContentResolver(),Settings.Secure.DOZE_ENABLED, 1 ) == 0 )
             {
             	 state.icon = ResourceIcon.get(R.drawable.screen2);
             }else {
             	 state.icon = ResourceIcon.get(R.drawable.screen1);
     		}
		} catch (Exception e) {
			 state.icon = ResourceIcon.get(R.drawable.screen1);
		}
       
       
    }

    @Override
    public int getMetricsCategory() {
        return MetricsLogger.QS_AIRPLANEMODE;
    }

    @Override
    protected String composeChangeAnnouncement() {
        if (mState.value) {
            return mContext.getString(R.string.accessibility_quick_settings_airplane_changed_on);
        } else {
            return mContext.getString(R.string.accessibility_quick_settings_airplane_changed_off);
        }
    }

    public void setListening(boolean listening) {
//        if (mListening == listening) return;
//        mListening = listening;
//        if (listening) {
//            final IntentFilter filter = new IntentFilter();
//            filter.addAction(Intent.ACTION_AIRPLANE_MODE_CHANGED);
//            mContext.registerReceiver(mReceiver, filter);
//        } else {
//            mContext.unregisterReceiver(mReceiver);
//        }
//        mSetting.setListening(listening);
    }

//    private final BroadcastReceiver mReceiver = new BroadcastReceiver() {
//        @Override
//        public void onReceive(Context context, Intent intent) {
//            if (Intent.ACTION_AIRPLANE_MODE_CHANGED.equals(intent.getAction())) {
//                refreshState();
//            }
//        }
//    };
}
