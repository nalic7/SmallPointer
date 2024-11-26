JNIEXPORT jlong JNICALL Java_org_lwjgl_opengl_LinuxKeyboard_getModifierMapping(JNIEnv* env, jclass unused, jlong display_ptr)
{
	// //avoid x11
	// info("run_getModifierMapping_0")
	return 0;
}

JNIEXPORT jboolean JNICALL Java_org_lwjgl_opengl_LinuxKeyboard_nSetDetectableKeyRepeat(JNIEnv* env, jclass unused, jlong display_ptr, jboolean set_enabled)
{
	// //avoid x11
	// info("run_nSetDetectableKeyRepeat_0")
	return JNI_FALSE;
}

JNIEXPORT jlong JNICALL Java_org_lwjgl_opengl_LinuxKeyboard_openIM(JNIEnv* env, jclass unused, jlong display_ptr)
{
	// //avoid x11
	// info("run_openIM_0")
	return -1;
}

JNIEXPORT jlong JNICALL Java_org_lwjgl_opengl_LinuxKeyboard_createIC(JNIEnv* env, jclass unused, jlong xim_ptr, jlong window_ptr)
{
	// //avoid x11
	// info("run_createIC_0")
	return -1;
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_LinuxKeyboard_setupIMEventMask(JNIEnv* env, jclass unused, jlong display_ptr, jlong window_ptr, jlong xic_ptr)
{
	// //avoid x11
	// info("run_setupIMEventMask_0")
}

JNIEXPORT jobject JNICALL Java_org_lwjgl_opengl_LinuxKeyboard_allocateComposeStatus(JNIEnv* env, jclass unused)
{
	// //avoid x11
	// info("run_allocateComposeStatus_0")
	return newJavaManagedByteBuffer(env, 0);
}
