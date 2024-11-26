JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL20_nglCreateShader(JNIEnv* env, jclass clazz, jint type, jlong function_pointer)
{
	//setbuffer
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL20_nglShaderSource(JNIEnv* env, jclass clazz, jint shader, jint count, jlong string, jint string_length, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL20_nglCompileShader(JNIEnv* env, jclass clazz, jint shader, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL20_nglGetShaderiv(JNIEnv* env, jclass clazz, jint shader, jint pname, jlong params, jlong function_pointer)
{
	//setbuffer
}

JNIEXPORT jint JNICALL Java_org_lwjgl_opengl_GL20_nglCreateProgram(JNIEnv* env, jclass clazz, jlong function_pointer)
{
	return 1;
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL20_nglAttachShader(JNIEnv* env, jclass clazz, jint program, jint shader, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL20_nglLinkProgram(JNIEnv* env, jclass clazz, jint program, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL20_nglGetProgramiv(JNIEnv* env, jclass clazz, jint program, jint pname, jlong params, jlong function_pointer)
{
	//setbuffer
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL20_nglGetUniformLocation(JNIEnv* env, jclass clazz, jint program, jlong name, jlong function_pointer)
{
	//setbuffer
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL20_nglGetAttribLocation(JNIEnv* env, jclass clazz, jint program, jlong name, jlong function_pointer)
{
	//setbuffer
}
