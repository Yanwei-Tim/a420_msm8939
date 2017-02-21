package com.android.systemui.qs.tiles;

import android.app.Instrumentation;
import android.os.Handler;
import android.os.Message;
import android.view.KeyEvent;

import com.android.systemui.R;

import com.android.systemui.qs.QSTile;
import com.android.systemui.qs.QSTile.Host;
import com.android.systemui.qs.QSTile.BooleanState;
import com.android.internal.logging.MetricsLogger;

public class ScreenShotTile extends QSTile<QSTile.BooleanState>{
	
	private Handler handler  = new Handler(){

		@Override
		public void handleMessage(Message msg) {
			super.handleMessage(msg);
			if(msg.what == 0x11)
			{
				Scrrenshot(KeyEvent.KEYCODE_SYSRQ);
			}
		}
		
		
	};

	public ScreenShotTile(Host host) {
		super(host);
		// TODO Auto-generated constructor stub
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
		
		Scrrenshot(KeyEvent.KEYCODE_BACK);
		
		handler.sendEmptyMessageDelayed(0x11, 600);
		
	}
	
	
	@Override
	protected void handleUpdateState(BooleanState state, Object arg) {
		// TODO Auto-generated method stub
		if(state != null)
		{
			state.visible = true;
			state.label = mContext.getString(R.string.qs_ScreenShot);
			state.icon  = ResourceIcon.get(R.drawable.screenshot);
		}
	}

	@Override
	public int getMetricsCategory() {
		// TODO Auto-generated method stub
		return   MetricsLogger.QS_SCREENSHOT;
	}

}
