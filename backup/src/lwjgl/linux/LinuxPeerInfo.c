JNIEXPORT jobject JNICALL Java_org_lwjgl_opengl_LinuxPeerInfo_createHandle(JNIEnv* env, jclass clazz)
{
	// //avoid x11
	// info("run_createHandle_0")
	return newJavaManagedByteBuffer(env, 0);
}
