JNIEXPORT void JNICALL Java_org_lwjgl_openal_ALC10_initNativeStubs(JNIEnv *env, jclass clazz)
{
}

JNIEXPORT jlong JNICALL Java_org_lwjgl_openal_ALC10_nalcOpenDevice(JNIEnv *env, jclass clazz, jlong devicename)
{
	return -1;
}

JNIEXPORT jlong JNICALL Java_org_lwjgl_openal_ALC10_nalcCreateContext(JNIEnv *env, jclass clazz, jlong device, jlong attrList)
{
	return -1;
}

JNIEXPORT jint JNICALL Java_org_lwjgl_openal_ALC10_nalcGetError(JNIEnv *env, jclass clazz, jlong device)
{
	return alcGetError(m_alcdevice);
}

JNIEXPORT jint JNICALL Java_org_lwjgl_openal_ALC10_nalcMakeContextCurrent(JNIEnv *env, jclass clazz, jlong context)
{
	return -1;
}

JNIEXPORT void JNICALL Java_org_lwjgl_openal_ALC10_nalcGetIntegerv(JNIEnv *env, jclass clazz, jlong device, jint pname, jint size, jlong integerdata)
{
	alcGetIntegerv(m_alcdevice, pname, size, (ALCint *)(intptr_t)integerdata);
}

JNIEXPORT jboolean JNICALL Java_org_lwjgl_openal_ALC10_nalcIsExtensionPresent(JNIEnv *env, jclass clazz, jlong device, jlong extName)
{
	return JNI_TRUE;
}
