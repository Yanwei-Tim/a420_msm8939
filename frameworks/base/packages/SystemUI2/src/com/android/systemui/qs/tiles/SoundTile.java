package com.android.systemui.qs.tiles;



import android.app.NotificationManager;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.database.ContentObserver;
import android.media.AudioManager;
import android.net.Uri;
import android.provider.Settings;
import android.util.Log;

import com.android.systemui.qs.QSTile;
import com.android.systemui.qs.QSTile.BooleanState;
import com.android.systemui.qs.QSTile.Host;
import com.android.systemui.qs.QSTile.ResourceIcon;
import com.android.internal.logging.MetricsLogger;
import com.android.systemui.R;

public class SoundTile extends QSTile<QSTile.BooleanState>{

	private AudioManager mAudioManager = (AudioManager) mContext.getSystemService(Context.AUDIO_SERVICE);
	
    private  Receiver mReceiver = null;
	
    private final Intent Soundaction = new Intent().setComponent(new ComponentName(
            "com.android.settings", "com.android.settings.Settings$NotificationSettingsActivity"));

    
	public SoundTile(Host host) {
		super(host);
		// TODO Auto-generated constructor stub
		if(mReceiver == null)
		{
			mReceiver = new Receiver();	
			mReceiver.register(true);
		}
	}

	
	private class Receiver extends BroadcastReceiver {
        private boolean mRegistered;

        public void register(boolean register) {
            if (mRegistered == register) return;
            if (register) {
                final IntentFilter filter = new IntentFilter();
                filter.addAction(AudioManager.INTERNAL_RINGER_MODE_CHANGED_ACTION);
                mContext.registerReceiver(this, filter);
            } else {
                mContext.unregisterReceiver(this);
            }
            mRegistered = register;
        }

        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            
            refreshState();
        }
    }
	
	@Override
	public void setListening(boolean listening) {
		// TODO Auto-generated method stub
		
	}

	@Override
	protected BooleanState newTileState() {
		// TODO Auto-generated method stub
		 return new BooleanState();
	}
	


	@Override
	protected void handleClick() {
	
		 int ringerMode2 = mAudioManager.getRingerMode();
		
		 Log.i(TAG, "ringerMode2 = " + ringerMode2 );
	
		 mAudioManager.setRingerMode((--ringerMode2 + 3 ) % 3);
		 
		 refreshState();
		
	}
	
	  @Override
	    protected void handleLongClick() {
	    	// TODO Auto-generated method stub
	    	super.handleLongClick();
	    	
	        mHost.startActivityDismissingKeyguard(Soundaction);
	    
	    }

	@Override
	protected void handleUpdateState(BooleanState state, Object arg) {
		if(state != null)
		{
			state.visible = true;
			//state.label = mContext.getString(R.string.qs_sound);
			
		}
		 int ringerMode = mAudioManager.getRingerMode();
		 
		 if(ringerMode == 2)
		 {
			 state.icon  = ResourceIcon.get(R.drawable.sound);
			 state.label = mContext.getString(R.string.qs_sound);
		 }else if(ringerMode == 1)
		 {
			 state.icon  = ResourceIcon.get(R.drawable.sound2);
			 state.label = mContext.getString(R.string.qs_sound2);
		 }else
		 {
			 state.icon  = ResourceIcon.get(R.drawable.sound3);
			 state.label = mContext.getString(R.string.qs_sound3);
		 }
		 
	}

	@Override
	public int getMetricsCategory() {
		// TODO Auto-generated method stub
		return  MetricsLogger.QS_SOUND;
	}

	/* private final class SettingsObserver extends ContentObserver {
	        private final Uri VIBRATE_WHEN_RINGING_URI =
	                Settings.System.getUriFor(Settings.System.VIBRATE_WHEN_RINGING);
	        private final Uri NOTIFICATION_LIGHT_PULSE_URI =
	                Settings.System.getUriFor(Settings.System.NOTIFICATION_LIGHT_PULSE);
	        private final Uri LOCK_SCREEN_PRIVATE_URI =
	                Settings.Secure.getUriFor(Settings.Secure.LOCK_SCREEN_ALLOW_PRIVATE_NOTIFICATIONS);
	        private final Uri LOCK_SCREEN_SHOW_URI =
	                Settings.Secure.getUriFor(Settings.Secure.LOCK_SCREEN_SHOW_NOTIFICATIONS);
	  
	        private final Uri ZEN_MODE = Settings.Global.getUriFor("zen_mode");
	        private final Uri VIBRATE_MODE = Settings.Global.getUriFor("mode_ringer");
	   
	        public SettingsObserver() {
	            super(mHandler);
	        }

	        public void register(boolean register) {
	            final ContentResolver cr = mContext.getContentResolver();
	            if (register) {
	                cr.registerContentObserver(VIBRATE_WHEN_RINGING_URI, false, this);
	                cr.registerContentObserver(NOTIFICATION_LIGHT_PULSE_URI, false, this);
	                cr.registerContentObserver(LOCK_SCREEN_PRIVATE_URI, false, this);
	                cr.registerContentObserver(LOCK_SCREEN_SHOW_URI, false, this);
	        //fix bug VibrateWhenRinging switch  disable  by chenxu start
	                cr.registerContentObserver(ZEN_MODE, false, this);
	                cr.registerContentObserver(VIBRATE_MODE, false, this);
	        //fix bug VibrateWhenRinging switch  disable  by chenxu end
	            } else {
	                cr.unregisterContentObserver(this);
	            }
	        }

	        @Override
	        public void onChange(boolean selfChange, Uri uri) {
	            super.onChange(selfChange, uri);
	            if (VIBRATE_WHEN_RINGING_URI.equals(uri)) {
	              
	            }
	            if (NOTIFICATION_LIGHT_PULSE_URI.equals(uri)) {
	              
	            }
	            if (LOCK_SCREEN_PRIVATE_URI.equals(uri) || LOCK_SCREEN_SHOW_URI.equals(uri)) {
	             
	            }
	     
	            if(ZEN_MODE.equals(uri)){
	                    boolean isZenMode=getZenMode();
	                 
	            }
	            if(VIBRATE_MODE.equals(uri)){
	                   boolean isZenMode=getZenMode();
	                  
	            }
	    
	        }
	    }
	 
	 
	  private boolean getZenMode(){
	       return (Settings.Global.getInt(mContext.getContentResolver(), "zen_mode", 1) == 2)||(Settings.Global.getInt(mContext.getContentResolver(), "mode_ringer",1) == 1);

	     }
	  
	  */
	
}
