#ifndef _ASM_ANALYSIS
#define _ASM_ANALYSIS


#include <string.h>
#include <jni.h>


//#include "basedef.cpp"

#include "asm-analysis/modules.cpp"


// JNI declares
extern "C"
{
	
	JNIEXPORT jstring JNICALL Java_com_asm_plugin_java_NativeBridge_stringFromJNI(JNIEnv* env, jclass thiz) {
		return env->NewStringUTF("*~<*");//ai::StringBuilder("abc").append("def").chars());
	}
}

#endif
