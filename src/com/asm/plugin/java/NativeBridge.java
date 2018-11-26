package com.asm.plugin.java;


public class NativeBridge
{
	static {
		System.loadLibrary("asm-core");
	}
	
	
	public static native String stringFromJNI();
}
