JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM *vm, char *options, void *reserved)
{
	#ifdef _CM_DEBUG
		_db_set();
	#endif

	jvmtiEnv *jvmtienv;
	_DB_N2L("getEnv %d", (*vm)->GetEnv(vm, (void**)&jvmtienv, JVMTI_VERSION_1_2));

	jvmtiEventCallbacks jvmtieventcallbacks = {0};
	jvmtieventcallbacks.ClassLoad = &mcc_jvmtiEventClassLoad;

	(*jvmtienv)->SetEventCallbacks(jvmtienv, &jvmtieventcallbacks, sizeof(jvmtieventcallbacks));
	(*jvmtienv)->SetEventNotificationMode(jvmtienv, JVMTI_ENABLE, JVMTI_EVENT_CLASS_LOAD, NULL);

	//! edit bytecode/switch to opengl
	//main();
	return JNI_OK;
}
