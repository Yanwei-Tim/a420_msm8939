package com.android.systemui.statusbar.phone;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.widget.ImageButton;

public class DisplayPanalBn extends ImageButton{
	
	public DisplayPanalBn(Context context) {
		super(context);
		
	}

	public DisplayPanalBn(Context context, AttributeSet attrs) {
		super(context, attrs);
		
	}
	
	@SuppressLint("NewApi") 
	public void rotation(float rotation)
	{
		setRotation(rotation);
		invalidate();
	}

	@Override
	protected void onDraw(Canvas canvas) {
	
		super.onDraw(canvas);
	}
	
}
