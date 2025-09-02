JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM *vm, char *options, void *reserved)
{
	#ifdef SMPT_CM_DEBUG
		smpt_db_set();
	#endif

	jvmtiEnv *jvmtienv;
	SMPT_DB_N2L("getEnv %d", (*vm)->GetEnv(vm, (void**)&jvmtienv, JVMTI_VERSION_1_2));

	jvmtiEventCallbacks jvmtieventcallbacks = {0};
	jvmtieventcallbacks.ClassLoad = &mcc_jvmtiEventClassLoad;

	(*jvmtienv)->SetEventCallbacks(jvmtienv, &jvmtieventcallbacks, sizeof(jvmtieventcallbacks));
	(*jvmtienv)->SetEventNotificationMode(jvmtienv, JVMTI_ENABLE, JVMTI_EVENT_CLASS_LOAD, NULL);

	//! edit bytecode/switch to opengl
	//! switch wayland opengl/lwjgl3 openal to drm vulkan libinput pipewire
	//main();
	return JNI_OK;
}
