JNIEXPORT void JNICALL Java_org_lwjgl_openal_AL10_initNativeStubs(JNIEnv *env, jclass clazz)
{
}

JNIEXPORT jint JNICALL Java_org_lwjgl_openal_AL10_nalGetError(JNIEnv *env, jclass clazz)
{
	return alGetError();
}

JNIEXPORT void JNICALL Java_org_lwjgl_openal_AL10_nalListenerfv(JNIEnv *env, jclass clazz, jint pname, jlong value)
{
	alListenerfv(pname, (ALfloat *)(intptr_t)value);
}

JNIEXPORT void JNICALL Java_org_lwjgl_openal_AL10_nalDopplerFactor(JNIEnv *env, jclass clazz, jfloat value)
{
	alDopplerFactor(value);
}

JNIEXPORT void JNICALL Java_org_lwjgl_openal_AL10_nalDopplerVelocity(JNIEnv *env, jclass clazz, jfloat value)
{
	alDopplerVelocity(value);
}

JNIEXPORT void JNICALL Java_org_lwjgl_openal_AL10_nalGenSources(JNIEnv *env, jclass clazz, jint sources_n, jlong sources)
{
	alGenSources(sources_n, (ALuint *)(intptr_t)sources);
}

JNIEXPORT void JNICALL Java_org_lwjgl_openal_AL10_nalSourcef(JNIEnv *env, jclass clazz, jint source, jint pname, jfloat value)
{
	alSourcef(source, pname, value);
}

JNIEXPORT void JNICALL Java_org_lwjgl_openal_AL10_nalListenerf(JNIEnv *env, jclass clazz, jint pname, jfloat value)
{
	alListenerf(pname, value);
}
