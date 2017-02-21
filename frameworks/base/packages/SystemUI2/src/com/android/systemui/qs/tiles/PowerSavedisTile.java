package com.android.systemui.qs.tiles;

import static android.os.PowerManager.ACTION_POWER_SAVE_MODE_CHANGING;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.AsyncTask;
import android.os.Handler;
import android.os.PowerManager;
import android.util.Log;

import com.android.systemui.R;

import com.android.systemui.qs.QSTile;
import com.android.systemui.qs.QSTile.Host;
import com.android.systemui.qs.QSTile.BooleanState;
import com.android.systemui.qs.QSTile.ResourceIcon;
import com.android.internal.logging.MetricsLogger;

public class PowerSavedisTile extends QSTile<QSTile.BooleanState>{

    private final Intent PowerSaveaction = new Intent().setComponent(new ComponentName(
	            "com.android.settings", "com.android.settings.Settings$BatterySaverSettingsActivity"));

    private PowerManager mPowerManager = null;
    
    private Handler mHandler = new Handler();
    
    private Receiver mReceiver = null;
	 
	public PowerSavedisTile(Host host) {
		super(host);
		if(mPowerManager == null)
		{
			  mPowerManager = (PowerManager) mContext.getSystemService(Context.POWER_SERVICE);
		}
		if(mReceiver == null)
		{
			mReceiver = new Receiver();
			mReceiver.setListening(true);
		}
	}
	
	 private final class Receiver extends BroadcastReceiver {
	        private boolean mRegistered;

	        @Override
	        public void onReceive(Context context, Intent intent) {
	        	refreshState();
	        }

	        public void setListening(boolean listening) {
	            if (listening && !mRegistered) {
	                mContext.registerReceiver(this, new IntentFilter(ACTION_POWER_SAVE_MODE_CHANGING));
	                mRegistered = true;
	            } else if (!listening && mRegistered) {
	                mContext.unregisterReceiver(this);
	                mRegistered = false;
	            }
	        }
	    }

	
	@Override
	protected BooleanState newTileState() {
		// TODO Auto-generated method stub
		return new BooleanState();
	}

	@Override
	protected void handleClick() {
	
		mHandler.post(mStartMode);
		
		refreshState();
	}
	
	  private final Runnable mStartMode = new Runnable() {
	        @Override
	        public void run() {
	            AsyncTask.execute(new Runnable() {
	                @Override
	                public void run() {
	                    try{
		                	if(mPowerManager.isPowerSaveMode())
		            		{
		            			mPowerManager.setPowerSaveMode(false);
		            		}else
		            		{
		            			mPowerManager.setPowerSaveMode(true);
		            		}
	                    }catch(Exception e)
	                    {
	                    	
	                    }
	                }
	            });
	        }
	    };
	
	 @Override
    protected void handleLongClick() {
	   // TODO Auto-generated method stub
	   super.handleLongClick();
	    	
	   mHost.startActivityDismissingKeyguard(PowerSaveaction);   
   }

	@Override
	protected void handleUpdateState(BooleanState state, Object arg) {
		// TODO Auto-generated method stub
		if(state != null)
		{
			state.visible = true;
			state.label = mContext.getString(R.string.qs_suppowersave);
			
		}
		if(mPowerManager.isPowerSaveMode())
		{
			state.icon  = ResourceIcon.get(R.drawable.supersaving);
		}else{
			state.icon  = ResourceIcon.get(R.drawable.supersaving2);
		}
	}

	@Override
	public int getMetricsCategory() {
		// TODO Auto-generated method stub
		return  MetricsLogger.QS_POWERSAVA;
	}

	@Override
	public void setListening(boolean listening) {
		// TODO Auto-generated method stub
		
	}

}
