JNIEXPORT jobject JNICALL Java_org_lwjgl_opengl_LinuxEvent_createEventBuffer(JNIEnv* env, jclass unused)
{
	// info("run_createEventBuffer_0")
	return newJavaManagedByteBuffer(env, 0);
}

JNIEXPORT jint JNICALL Java_org_lwjgl_opengl_LinuxEvent_getPending(JNIEnv* env, jclass unused, jlong display_ptr)
{
	// info("run_getPending_0")
	return -1;
}
