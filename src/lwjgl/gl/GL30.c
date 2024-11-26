typedef const GLubyte* (*GLGETSTRINGI)(GLenum name, GLuint index);

JNIEXPORT jstring JNICALL Java_org_lwjgl_opengl_GL30_nglGetStringi(JNIEnv* env, jclass clazz, jint name, jint index, jlong function_pointer)
{
	// info("run_GL30$nglGetStringi_0")

	GLGETSTRINGI glGetStringi = (GLGETSTRINGI)glXGetProcAddress((const GLubyte*)"glGetStringi");
	const GLubyte* glString = glGetStringi(name, index);
	// info("run_GL30$nglGetStringi")
	// info("name %d", name)
	// info("glString %s", glString)
	return (*env)->NewStringUTF(env, (const char*)glString);
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL30_nglGenFramebuffers(JNIEnv* env, jclass clazz, jint framebuffers_n, jlong framebuffers, jlong function_pointer)
{
	//setbuffer
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL30_nglGenRenderbuffers(JNIEnv* env, jclass clazz, jint renderbuffers_n, jlong renderbuffers, jlong function_pointer)
{
	//setbuffer
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL30_nglBindFramebuffer(JNIEnv* env, jclass clazz, jint target, jint framebuffer, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL30_nglFramebufferTexture2D(JNIEnv* env, jclass clazz, jint target, jint attachment, jint textarget, jint texture, jint level, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL30_nglBindRenderbuffer(JNIEnv* env, jclass clazz, jint target, jint renderbuffer, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL30_nglRenderbufferStorage(JNIEnv* env, jclass clazz, jint target, jint internalformat, jint width, jint height, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL30_nglFramebufferRenderbuffer(JNIEnv* env, jclass clazz, jint target, jint attachment, jint renderbuffertarget, jint renderbuffer, jlong function_pointer)
{
}

JNIEXPORT jint JNICALL Java_org_lwjgl_opengl_GL30_nglCheckFramebufferStatus(JNIEnv* env, jclass clazz, jint target, jlong function_pointer)
{
	return GL_FRAMEBUFFER_COMPLETE;
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL30_nglDeleteRenderbuffers(JNIEnv* env, jclass clazz, jint renderbuffers_n, jlong renderbuffers, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL30_nglDeleteFramebuffers(JNIEnv* env, jclass clazz, jint framebuffers_n, jlong framebuffers, jlong function_pointer)
{
}
