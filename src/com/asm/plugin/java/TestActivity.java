package com.asm.plugin.java;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Toast;
import com.asm.plugin.java.NativeBridge;


public class TestActivity extends Activity
{
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		Toast.makeText(this, NativeBridge.stringFromJNI(), Toast.LENGTH_LONG).show();
	}
}
