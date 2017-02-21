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
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.nfc.NfcAdapter;
import android.R.integer;
import android.app.StatusBarManager;
import android.provider.Settings.Global;
import android.util.Log;

import com.android.internal.logging.MetricsLogger;
import com.android.systemui.R;
import com.android.systemui.qs.GlobalSetting;
import com.android.systemui.qs.QSTile;
import com.android.systemui.qs.QSTile.ResourceIcon;
import com.android.systemui.statusbar.policy.NfcController;


/** Quick settings tile: Airplane mode **/
public class NfcTile extends QSTile<QSTile.BooleanState> {
//    private final AnimationIcon mEnable =
//            new AnimationIcon(R.drawable.ic_signal_airplane_enable_animation);
//    private final AnimationIcon mDisable =
//            new AnimationIcon(R.drawable.ic_signal_airplane_disable_animation);
//    private final GlobalSetting mSetting;
//
//    private boolean mListening;
	
	private final String nfc_open = "com.lovdream.nfc.pen";
	
	private final String nfc_close = "com.lovdream.nfc.close";
	
    private  NfcAdapter mNfcAdapter;
    private NfcController mNfcController;
	private Intent nfcintent = new Intent("android.settings.NFC_SETTINGS");
	
	private  Intent intent = new Intent(nfc_open);
	/*.setComponent(new ComponentName(
            "com.android.settings", "com.android.settings.Settings$WirelessSettingsActivity")); */
	private StatusBarManager mStatusBarManager;
	
	public static final String NFC_STATUS_ICON_PLACEHOLDER = "nfc";
	
	private int nfc_flag = 0;

    public NfcTile(Host host) {
        super(host);
        
   //     mNfcController = host.getNfcContoller();
      
    
//        mSetting = new GlobalSetting(mContext, mHandler, Global.AIRPLANE_MODE_ON) {
//            @Override
//            protected void handleValueChanged(int value) {
//                handleRefreshState(value);
//            }
//        };
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(NfcAdapter.ACTION_ADAPTER_STATE_CHANGED);
        mContext.registerReceiver(mReceiver, intentFilter);
        
        mStatusBarManager = (StatusBarManager) mContext.getSystemService(Context.STATUS_BAR_SERVICE);
     
    }

    @Override
    protected BooleanState newTileState() {
        return new BooleanState();
    }
    
    @Override
    protected void handleLongClick() {
	   // TODO Auto-generated method stub
	   super.handleLongClick();
	    	
	   //mHost.startActivityDismissingKeyguard(nfcintent);   
   }
    
    @Override
    public void handleClick() {
        MetricsLogger.action(mContext, getMetricsCategory(), !mState.value);
     
//        if(mNfcAdapter == null)
//        {
//        	Log.i(TAG, "===============handleClick===============mNfcAdapter =  null" );
//        	mNfcAdapter = NfcAdapter.getDefaultAdapter(mContext);
//        }
        
       
        mContext.sendBroadcast(intent);
        
//        Log.i(TAG, "===============handleClick===============mNfcAdapter = " + mNfcAdapter);
//        
//        if(mNfcAdapter != null && mNfcAdapter.isEnabled())
//        {
//        	mNfcAdapter.disable();
//        }
//        if(mNfcAdapter != null && !mNfcAdapter.isEnabled()){
//        	mNfcAdapter.enable();   
//        }
//        refreshState();
        
    }

//    private void setEnabled(boolean enabled) {
//        final ConnectivityManager mgr =
//                (ConnectivityManager) mContext.getSystemService(Context.CONNECTIVITY_SERVICE);
//        mgr.setAirplaneMode(enabled);
//    }

    @Override
    protected void handleUpdateState(BooleanState state, Object arg) {
//        final int value = arg instanceof Integer ? (Integer)arg : mSetting.getValue();
//        final boolean airplaneMode = value != 0;
        state.value = true;
        state.visible = true;
        state.label = mContext.getString(R.string.qs_nfc);
        state.icon = ResourceIcon.get(R.drawable.nfc2);
        
//        if(mNfcAdapter == null)
//        {
//        	Log.i(TAG, "===========mNfcAdapter= null================");
//        	
//        	mNfcAdapter = NfcAdapter.getDefaultAdapter(mContext);
//       
//        }
//        
        if(nfc_flag == 1)
        {
        	 state.icon = ResourceIcon.get(R.drawable.nfc1);
        }
        if(nfc_flag == 0)
        {
        	 state.icon = ResourceIcon.get(R.drawable.nfc2);
        }
        Log.i(TAG, "==============================mNfcAdapter = " + mNfcAdapter);
        if(mNfcAdapter != null &&  mNfcAdapter.isEnabled())
        {
        	state.icon = ResourceIcon.get(R.drawable.nfc1);
        	 mStatusBarManager.setIcon(NFC_STATUS_ICON_PLACEHOLDER, R.drawable.nfc_icon,
                     0, mContext.getString(R.string.qs_nfc));
        }
        if(mNfcAdapter != null &&  !mNfcAdapter.isEnabled()){
        	state.icon = ResourceIcon.get(R.drawable.nfc2);
        	mStatusBarManager.removeIcon(NFC_STATUS_ICON_PLACEHOLDER);
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

//    public void setListening(boolean listening) {
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
//    }

   

	@Override
	public void setListening(boolean listening) {
		// TODO Auto-generated method stub
		
	}
	
	 private final BroadcastReceiver mReceiver = new BroadcastReceiver() {
	        @Override
	        public void onReceive(Context context, Intent intent) {
	            String action = intent.getAction();
	            if (NfcAdapter.ACTION_ADAPTER_STATE_CHANGED.equals(action)) {
//	                handleNfcStateChanged(intent.getIntExtra(NfcAdapter.EXTRA_ADAPTER_STATE,
//	                        NfcAdapter.STATE_OFF));
	            	int state =	intent.getIntExtra(NfcAdapter.EXTRA_ADAPTER_STATE,
	                        NfcAdapter.STATE_OFF);
	            	
	            	if(state == NfcAdapter.STATE_ON)
	            	{
	            		 mStatusBarManager.setIcon(NFC_STATUS_ICON_PLACEHOLDER, R.drawable.nfc_icon,
	                             0, mContext.getString(R.string.qs_nfc));
	            		 
	            		 nfc_flag = 1;
	            		 
	            	}
	            	
	            	else if(state == NfcAdapter.STATE_OFF)
	            	{
	            		mStatusBarManager.removeIcon(NFC_STATUS_ICON_PLACEHOLDER);
	            		 nfc_flag = 0;
	            	}
	            	
	            	Log.i(TAG, "============ACTION_ADAPTER_STATE_CHANGED===============");
	            	
	            	refreshState();
	            }
	        }
	    };
}
