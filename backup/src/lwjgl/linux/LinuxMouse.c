JNIEXPORT jint JNICALL Java_org_lwjgl_opengl_LinuxMouse_nGetButtonCount(JNIEnv* env, jclass unused, jlong display_p)
{
	// //avoid x11
	// info("run_nGetButtonCount_0")
	return 0;
}

JNIEXPORT jlong JNICALL Java_org_lwjgl_opengl_LinuxMouse_nQueryPointer(JNIEnv* env, jclass unused, jlong display_p, jlong window_p, jobject result_buffer)
{
	// //avoid x11
	// info("run_nQueryPointer_0")
	return 0;
}

JNIEXPORT jint JNICALL Java_org_lwjgl_opengl_LinuxMouse_nGetWindowHeight(JNIEnv* env, jclass unused, jlong display_p, jlong window_p)
{
	// //avoid x11
	// info("run_nGetWindowHeight_0")
	return 1;
}
