char lwjgl_debug;

jobject newJavaManagedByteBuffer(JNIEnv* env, const int size)
{
	jclass bufferutils_class = (*env)->FindClass(env, "org/lwjgl/BufferUtils");
	jmethodID createByteBuffer = (*env)->GetStaticMethodID(env, bufferutils_class, "createByteBuffer", "(I)Ljava/nio/ByteBuffer;");
	jobject buffer = (*env)->CallStaticObjectMethod(env, bufferutils_class, createByteBuffer, size);
	return buffer;
}

JNIEXPORT jint JNICALL Java_org_lwjgl_DefaultSysImplementation_getPointerSize(JNIEnv* env, jobject obj)
{
	int size = sizeof(void*);
	info("pointer_size %db", size)
	return size;
}

JNIEXPORT jint JNICALL Java_org_lwjgl_DefaultSysImplementation_getJNIVersion(JNIEnv* env, jobject obj)
{
	int ver = (*env)->GetVersion(env);
	info("jni_version %d", ver)
	info("set_fake_jni_version 19")
	return 19;//org_lwjgl_LinuxSysImplementation_JNI_VERSION
}

JNIEXPORT void JNICALL Java_org_lwjgl_DefaultSysImplementation_setDebug(JNIEnv* env, jobject obj, jboolean debug)
{
	lwjgl_debug = debug;
	info("lwjgl_debug %d", lwjgl_debug)
}
