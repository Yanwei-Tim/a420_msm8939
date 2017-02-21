package com.android.systemui.statusbar.policy;

import android.annotation.SuppressLint;
import android.content.Context;
import android.nfc.NfcAdapter;

public class NfcController {

	private  NfcAdapter mNfcAdapter;
	private  Context mContext;
	
	@SuppressLint("NewApi")
	public NfcController(Context context)
	{
		mNfcAdapter = NfcAdapter.getDefaultAdapter(context);
		mContext = context;
	}
	
	@SuppressLint("NewApi")
	public NfcAdapter getNfcAdapter()
	{
		if(mNfcAdapter == null)
		{
			mNfcAdapter = NfcAdapter.getDefaultAdapter(mContext);
		}
		return mNfcAdapter;
	}
}
