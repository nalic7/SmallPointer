JNIEXPORT void JNICALL Java_org_lwjgl_opengl_LinuxDisplay_nLockAWT(JNIEnv* env, jclass clazz)
{
	// info("run_nLockAWT_0")
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_LinuxDisplay_nUnlockAWT(JNIEnv* env, jclass clazz)
{
	// info("run_nUnlockAWT_0")
}

JNIEXPORT jlong JNICALL Java_org_lwjgl_opengl_LinuxDisplay_setErrorHandler(JNIEnv* env, jclass unused)
{
	// //avoid x11
	// info("run_setErrorHandler_0")
	return -1;
}

JNIEXPORT jlong JNICALL Java_org_lwjgl_opengl_LinuxDisplay_openDisplay(JNIEnv* env, jclass clazz)
{
	// //avoid x11
	// info("run_openDisplay_0")
	return -1;
}

JNIEXPORT jlong JNICALL Java_org_lwjgl_opengl_LinuxDisplay_nInternAtom(JNIEnv* env, jclass unused, jlong display_ptr, jstring atom_name_obj, jboolean only_if_exists)
{
	// //avoid x11
	// info("run_nInternAtom_0")
	return -1;
}

JNIEXPORT jboolean JNICALL Java_org_lwjgl_opengl_LinuxDisplayandrS_nIsXrupported(JNIEnv* env, jclass unused, jlong display)
{
	// //avoid x11
	// info("run_nIsXrupported_1")
	return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_org_lwjgl_opengl_LinuxDisplay_nIsXrandrSupported(JNIEnv* env, jclass unused, jlong display)
{
	// //avoid x11
	// info("run_nIsXrandrSupported_1")
	return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_org_lwjgl_opengl_LinuxDisplay_nIsXF86VidModeSupported(JNIEnv* env, jclass unused, jlong display)
{
	// //avoid x11
	// info("run_nIsXF86VidModeSupported_1")
	return JNI_TRUE;
}

JNIEXPORT jint JNICALL Java_org_lwjgl_opengl_LinuxDisplay_nGetDefaultScreen(JNIEnv* env, jclass unused, jlong display_ptr)
{
	// //avoid x11
	// info("run_nGetDefaultScreen_0")
	return -1;
}

JNIEXPORT jobjectArray JNICALL Java_org_lwjgl_opengl_LinuxDisplay_nGetAvailableDisplayModes(JNIEnv* env, jclass clazz, jlong display, jint screen, jint extension)
{
	// //avoid x11
	// info("run_nGetAvailableDisplayModes_0")

	jclass displayModeClass = (*env)->FindClass(env, "org/lwjgl/opengl/DisplayMode");
	jobjectArray ret = (*env)->NewObjectArray(env, 0, displayModeClass, NULL);
	return ret;
}

JNIEXPORT jobject JNICALL Java_org_lwjgl_opengl_LinuxDisplay_nGetCurrentGammaRamp(JNIEnv* env, jclass unused, jlong display, jint screen)
{
	// //avoid x11
	// info("run_nGetCurrentGammaRamp_0")
	jobject ramp_buffer = newJavaManagedByteBuffer(env, 0);
	return ramp_buffer;
}

JNIEXPORT jlong JNICALL Java_org_lwjgl_opengl_LinuxDisplay_getRootWindow(JNIEnv* env, jclass clazz, jlong display, jint screen)
{
	// //avoid x11
	// info("run_getRootWindow_0")
	return -1;
}

JNIEXPORT jlong JNICALL Java_org_lwjgl_opengl_LinuxDisplay_nCreateWindow(JNIEnv* env, jclass clazz, jlong display, jint screen, jobject peer_info_handle, jobject mode, jint window_mode, jint x, jint y, jboolean undecorated, jlong parent_handle, jboolean resizable)
{
	// //avoid x11
	// info("run_nCreateWindow_0")
	return -1;
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_LinuxDisplay_nSetClassHint(JNIEnv* env, jclass clazz, jlong display, jlong window_ptr, jlong wm_name, jlong wm_class)
{
	// //avoid x11
	// info("run_nSetClassHint_0")
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_LinuxDisplay_mapRaised(JNIEnv* env, jclass unused, jlong display, jlong window_ptr)
{
	// //avoid x11
	// info("run_mapRaised_0")
}

JNIEXPORT jlong JNICALL Java_org_lwjgl_opengl_LinuxDisplay_nCreateBlankCursor(JNIEnv* env, jclass unused, jlong display_ptr, jlong window_ptr)
{
	// //avoid x11
	// info("run_nCreateBlankCursor_0")
	return -1;
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_LinuxDisplay_nSetTitle(JNIEnv* env, jclass clazz, jlong display, jlong window_ptr, jlong title, jint len)
{
	// //avoid x11
	// info("run_nSetTitle_0")
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_LinuxDisplay_nSetWindowIcon(JNIEnv* env, jclass clazz, jlong display, jlong window_ptr, jobject icons_buffer, jint icons_buffer_size)
{
	// //avoid x11
	// info("run_nSetWindowIcon_0")
}
