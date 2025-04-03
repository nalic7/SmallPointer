JNIEXPORT jobject JNICALL Java_org_lwjgl_opengl_LinuxContextImplementation_nCreate(JNIEnv* env , jclass clazz, jobject peer_handle, jobject attribs, jobject shared_context_handle)
{
	// //avoid x11
	// info("run_LinuxContextImplementation$nCreate_0")
	return newJavaManagedByteBuffer(env, 0);
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_LinuxContextImplementation_nMakeCurrent(JNIEnv* env, jclass clazz, jobject peer_info_handle, jobject context_handle)
{
	// //avoid x11
	// info("run_LinuxContextImplementation$nMakeCurrent_0")

	// //setbuffer

	// // (*env)->GetDirectBufferAddress(env, peer_info_handle);
	// // (*env)->GetDirectBufferAddress(env, context_handle);
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_LinuxContextImplementation_nSetSwapInterval(JNIEnv* env, jclass clazz, jobject peer_info_handle, jobject context_handle, jint value)
{
	// //avoid x11
	// info("run_nSetSwapInterval_0")
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_LinuxContextImplementation_nSwapBuffers(JNIEnv* env, jclass clazz, jobject peer_info_handle)
{
	// //avoid x11
	// info("run_nSwapBuffers_0")
}

JNIEXPORT jboolean JNICALL Java_org_lwjgl_opengl_LinuxContextImplementation_nIsCurrent(JNIEnv* env, jclass clazz, jobject context_handle)
{
	// //avoid x11
	// info("run_nIsCurrent_0")
	// // return JNI_FALSE;
	return JNI_TRUE;
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_LinuxContextImplementation_nReleaseCurrentContext(JNIEnv* env , jclass clazz, jobject peer_info_handle)
{
	// //avoid x11
	// info("run_nReleaseCurrentContext_0")
}
