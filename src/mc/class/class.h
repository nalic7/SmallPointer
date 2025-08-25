#ifndef _MCC_H
	#define _MCC_H

	void JNICALL mcc_jvmtiEventClassLoad(jvmtiEnv *jvmti_env, JNIEnv *jni_env, jthread thread, jclass klass);
#endif
