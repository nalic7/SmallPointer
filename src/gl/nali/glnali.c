#ifdef NALI_LWJGL3
	typedef void (APIENTRY *glGetIntegervPROC) (jint, uintptr_t);
	typedef void (APIENTRY *glGenVertexArraysPROC) (jint, uintptr_t);
	typedef void (APIENTRY *glBindVertexArrayPROC) (jint);
	typedef void (APIENTRY *glDrawElementsPROC) (jint, jint, jint, uintptr_t);
	static glGetIntegervPROC glGetIntegerv3;
	static glBindVertexArrayPROC glBindVertexArray;
	static glGenVertexArraysPROC glGenVertexArrays;
	static glDrawElementsPROC glDrawElements3;
#endif
#ifdef NALI_LWJGL2
	static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
	static PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
#endif

JNIEXPORT void JNICALL Java_com_nali_NaliGL_init(JNIEnv *__env, jclass clazz)
{
	#ifdef NALI_LWJGL3
		glGetIntegerv3 = (glGetIntegervPROC)tlsGetFunction(96);
		glGenVertexArrays = (glGenVertexArraysPROC)tlsGetFunction(633);
		glBindVertexArray = (glBindVertexArrayPROC)tlsGetFunction(631);
		glDrawElements3 = (glDrawElementsPROC)tlsGetFunction(63);
	#endif
	#ifdef NALI_LWJGL2
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)GETPROCADDRESS("glGenVertexArrays");
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)GETPROCADDRESS("glBindVertexArray");
	#endif
}

JNIEXPORT jint JNICALL Java_com_nali_NaliGL_glVertexArrayBinding(JNIEnv *env, jclass clazz)
{
	#ifdef NALI_LWJGL3
		int params;
		uintptr_t params_ar = (uintptr_t)&params;
		glGetIntegerv3((jint)GL_VERTEX_ARRAY_BINDING, params_ar);
	#endif
	#ifdef NALI_LWJGL2
		GLint params;
		glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &params);
	#endif
	return (jint)params;
}

JNIEXPORT jint JNICALL Java_com_nali_NaliGL_glGenVertexArrays(JNIEnv *env, jclass clazz)
{
	#ifdef NALI_LWJGL3
		int vao;
		uintptr_t vao_ar = (uintptr_t)&vao;
		glGenVertexArrays((jint)1, vao_ar);
	#endif
	#ifdef NALI_LWJGL2
		GLuint vao;
		glGenVertexArrays(1, &vao);
	#endif
	return (jint)vao;
}

JNIEXPORT void JNICALL Java_com_nali_NaliGL_glBindVertexArray(JNIEnv *env, jclass clazz, jint array)
{
	#ifdef NALI_LWJGL3
		glBindVertexArray(array);
	#endif
	#ifdef NALI_LWJGL2
		glBindVertexArray((GLuint)array);
	#endif
}

JNIEXPORT void JNICALL Java_com_nali_NaliGL_glDrawElementsTUi0(JNIEnv *env, jclass clazz, jint indices_count)
{
	#ifdef NALI_LWJGL3
		glDrawElements3((jint)GL_TRIANGLES, indices_count, (jint)GL_UNSIGNED_INT, 0);
	#endif
	#ifdef NALI_LWJGL2
		glDrawElements(GL_TRIANGLES, (GLsizei)indices_count, GL_UNSIGNED_INT, 0);
	#endif
}

