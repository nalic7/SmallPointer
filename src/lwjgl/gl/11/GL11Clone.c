// uint32_t gl11_current_texture = -1;
// int* gl11_target_p;
// int* gl11_level_p;
// int* gl11_internalformat_p;
// int* gl11_width_p;
// int* gl11_height_p;
// int* gl11_border_p;
// int* gl11_format_p;
// int* gl11_type_p;
// // need to check is address able to reach
// long* gl11_pixels_p;
// // char pixels_able;
// // unsigned char *pixels_able_p;
// unsigned char **gl11_clone_char_p;

// int max_texture = -1;
// uint32_t modify_texture = 0;
// uint32_t* gl11_modify_texture_p = 0;
// long* gl11_texture_p;

// JNIEXPORT jstring JNICALL Java_org_lwjgl_opengl_GL11_nglGetString(JNIEnv* env, jclass clazz, jint name, jlong function_pointer)
// {
//	 // info("run_GL11$nglGetString_0")

//	 const GLubyte* glString = glGetString(name);
//	 // info("run_GL11$nglGetString")
//	 // info("name %d", name)
//	 // info("glString %s", glString)
//	 return (*env)->NewStringUTF(env, (const char*)glString);
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglGetIntegerv(JNIEnv* env, jclass clazz, jint pname, jlong params, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglGetIntegerv_0")

//	 //setbuffer
//	 GLint* paramBuffer = (GLint*)params;
//	 glGetIntegerv((GLenum)pname, paramBuffer);
// }

// JNIEXPORT jint JNICALL Java_org_lwjgl_opengl_GL11_nglGetError(JNIEnv* env, jclass clazz, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglGetError_0")
// 	return 0;
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglClearColor(JNIEnv* env, jclass clazz, jfloat red, jfloat green, jfloat blue, jfloat alpha, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglClearColor_0")
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglClear(JNIEnv* env, jclass clazz, jint mask, jlong function_pointer)
// {
//	 info("max_texture+1 %d", (max_texture + 1))

//	 for (uint32_t i = 0; i < (max_texture + 1) && max_texture > 0; ++i)
//	 {
//		 long address = gl11_pixels_p[i];
//		 info("%d l_address %ld", i, address)
//		 if (address != -1)
//		 {
//			 int* buffer = (int*)(intptr_t)address;
//			 info("nglClear i%d r%d g%d b%d a%d", i, buffer[0], buffer[1], buffer[2], buffer[3])
//		 }

//		 // struct timespec ts = {1, 0};
//		 // thrd_sleep(&ts, NULL);
//	 }

//	 for (uint32_t i = 0; i < (max_texture + 1) && max_texture > 0; ++i)
//	 {
//		 long address = gl11_pixels_p[i];
//		 unsigned char* n_clone_char_p = gl11_clone_char_p[i];
//		 info("%d c_address %p", i, n_clone_char_p)
//		 if (/* n_clone_char_p &&  */address != -1)
//		 {
//			 info("nglClear i%d r%d g%d b%d a%d", i, n_clone_char_p[0], n_clone_char_p[1], n_clone_char_p[2], n_clone_char_p[3])
//		 }

//		 // struct timespec ts = {1, 0};
//		 // thrd_sleep(&ts, NULL);
//	 }

//	 // //avoid gl
//	 // info("run_GL11$nglClear_0")
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTexImage2D(JNIEnv* env, jclass clazz, jint target, jint level, jint internalformat, jint width, jint height, jint border, jint format, jint type, jlong pixels, jlong function_pointer)
// {
//	 if (gl11_current_texture == -1)
//	 {
//		 error("current_texture -1")
//	 }
//	 // //avoid gl
//	 // info("run_GL11$nglTexImage2D_0")

//	 info("gl11_current_texture %d", gl11_current_texture)

//	 info("GL11_nglTexImage2D_target %d", target)
//	 info("GL11_nglTexImage2D_level %d", level)
//	 info("GL11_nglTexImage2D_internalformat %d", internalformat)
//	 info("GL11_nglTexImage2D_width %d", width)
//	 info("GL11_nglTexImage2D_height %d", height)
//	 info("GL11_nglTexImage2D_border %d", border)
//	 info("GL11_nglTexImage2D_format %d", format)
//	 info("GL11_nglTexImage2D_type %d", type)
//	 info("GL11_nglTexImage2D_pixels %ld", pixels)

//	 info("GL_RGBA8 == gl11_internalformat_p[gl11_current_texture] %d", GL_RGBA8 == internalformat);
//	 info("GL_UNSIGNED_BYTE == gl11_type_p[gl11_current_texture] %d", GL_UNSIGNED_BYTE == type);
//	 info("pixels %d", 1 && pixels);
//	 if (/* (GL_RGBA8 == internalformat || GL_RGBA == internalformat) && (GL_UNSIGNED_BYTE == type || GL_UNSIGNED_SHORT_5_6_5 == type) &&  */pixels)
//	 {
//		 unsigned char* char_p = (unsigned char*)(intptr_t)pixels;
//		 // for (int xy = 0; xy < width * height; ++xy)
//		 // {
//		 //	 char pixel = char_p[xy];
//		 // }
//		 size_t length = width * height * 4 * sizeof(unsigned char);//rgba as 4 byte
//		 if (GL_UNSIGNED_BYTE == gl11_type_p[gl11_current_texture])
//		 {

//		 }
//		 if (GL_UNSIGNED_SHORT_5_6_5 == gl11_type_p[gl11_current_texture])
//		 {
//			 length = width * height * 2 * sizeof(unsigned char);//r5bit g6bit b5bit as 2 byte
//		 }
//		 unsigned char* n_clone_char_p = malloc(length);
//		 memcpy(n_clone_char_p, char_p, length);
//		 // pixels_able = 1;
//		 gl11_pixels_p[gl11_current_texture] = pixels;
//		 info("s_gl11_pixels_p[gl11_current_texture] %ld", gl11_pixels_p[gl11_current_texture]);
//		 gl11_clone_char_p[gl11_current_texture] = n_clone_char_p;
//		 info("s_gl11_clone_char_p[gl11_current_texture] %p", gl11_clone_char_p[gl11_current_texture]);
//	 }
//	 else
//	 {
//		 // pixels_able = 0;
//		 gl11_pixels_p[gl11_current_texture] = -1;
//		 info("f_gl11_pixels_p[gl11_current_texture] %ld", gl11_pixels_p[gl11_current_texture]);
//		 gl11_clone_char_p[gl11_current_texture] = realloc(gl11_clone_char_p[gl11_current_texture], 0);
//		 info("f_gl11_clone_char_p[gl11_current_texture] %p", gl11_clone_char_p[gl11_current_texture]);
//	 }

//	 //
//	 //use pixels address as index
//	 gl11_target_p[gl11_current_texture] = target;
//	 gl11_level_p[gl11_current_texture] = level;
//	 gl11_internalformat_p[gl11_current_texture] = internalformat;
//	 gl11_width_p[gl11_current_texture] = width;
//	 gl11_height_p[gl11_current_texture] = height;
//	 gl11_border_p[gl11_current_texture] = border;
//	 gl11_format_p[gl11_current_texture] = format;
//	 gl11_type_p[gl11_current_texture] = type;

//	 info("gl11_internalformat_p[gl11_current_texture] %d", gl11_internalformat_p[gl11_current_texture]);
//	 info("gl11_type_p[gl11_current_texture] %d", gl11_type_p[gl11_current_texture]);
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglGetTexLevelParameteriv(JNIEnv* env, jclass clazz, jint target, jint level, jint pname, jlong params, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglGetTexLevelParameteriv_0")
// }

// // uint32_t texture_id = 0;
// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglGenTextures(JNIEnv* env, jclass clazz, jint textures_n, jlong textures, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglGenTextures_0")

//	 info("gl11_current_texture %d", gl11_current_texture)
//	 info("max_texture+1 %d", max_texture+1)
//	 info("textures_remaining %d", textures_n)
//	 info("g_tex_p %ld", textures)
//	 // ++texture_id;
//	 for (uint32_t i = 0; i < textures_n; ++i)
//	 {
//		 int* buffer = (int*)(intptr_t)textures;
//		 int texture_index;

//		 info("gl11_textures_buffer[%d] -> %d", i, buffer[i])

//		 if (modify_texture > 0)
//		 {
//			 --modify_texture;
//			 texture_index = gl11_modify_texture_p[modify_texture];
//			 gl11_modify_texture_p = realloc(gl11_modify_texture_p, sizeof(uint32_t) * modify_texture);
//		 }
//		 else
//		 {
//			 ++max_texture;
//			 texture_index = max_texture;

//			 size_t long_size = sizeof(long) * (max_texture + 1);
//			 size_t int_size = sizeof(int) * (max_texture + 1);
//			 gl11_texture_p = realloc(gl11_texture_p, long_size);
//			 gl11_target_p = realloc(gl11_target_p, int_size);
//			 gl11_level_p = realloc(gl11_level_p, int_size);
//			 gl11_internalformat_p = realloc(gl11_internalformat_p, int_size);
//			 gl11_width_p = realloc(gl11_width_p, int_size);
//			 gl11_height_p = realloc(gl11_height_p, int_size);
//			 gl11_border_p = realloc(gl11_border_p, int_size);
//			 gl11_format_p = realloc(gl11_format_p, int_size);
//			 gl11_type_p = realloc(gl11_type_p, int_size);
//			 gl11_pixels_p = realloc(gl11_pixels_p, long_size);
//			 gl11_clone_char_p = realloc(gl11_clone_char_p, sizeof(unsigned char*) * (max_texture + 1));
//			 info("o_gl11_clone_char_p[%d] %p", max_texture, gl11_clone_char_p[max_texture])
//			 gl11_clone_char_p[max_texture] = malloc(0);
//			 info("n_gl11_clone_char_p[%d] %p", max_texture, gl11_clone_char_p[max_texture])
//		 }

//		 info("gl11_textures_buffer[%d] <- %d", i, texture_index)

//		 //setbuffer
//		 buffer[i] = texture_index;
//		 // size_t size = sizeof(long) * (texture_index + 1);

//		 // gl11_texture_p[texture_index] = textures;
//	 }
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglDeleteTextures(JNIEnv* env, jclass clazz, jint textures_n, jlong textures, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglDeleteTextures_0")

//	 info("textures_remaining %d", textures_n)
//	 info("d_tex_p %ld", textures)
//	 info("gl11_current_texture %d", gl11_current_texture)
//	 info("max_texture+1 %d", max_texture+1)

//	 int* buffer = (int*)(intptr_t)textures;
//	 for (int i = 0; i < textures_n; ++i)
//	 {
//		 info("gl11_textures_buffer[%d] %d", i, buffer[i])
//		 // free((int*)(intptr_t)gl11_texture_p[buffer[i]]);
//		 // gl11_texture_p[buffer[i]] = 0;
//		 ++modify_texture;
//		 gl11_modify_texture_p = realloc(gl11_modify_texture_p, sizeof(uint32_t) * modify_texture);
//		 gl11_modify_texture_p[modify_texture - 1] = buffer[i];
//		 // if (gl11_clone_char_p[buffer[i]] && gl11_pixels_p[buffer[i]] != -1)
//		 // {
//		 info("buffer[i] %d", buffer[i])
//		 info("max_texture %d", max_texture)
//		 info("max_texture %p", gl11_clone_char_p[buffer[i]])
//		 // free(gl11_clone_char_p[buffer[i]]);
//		 gl11_clone_char_p[buffer[i]] = realloc(gl11_clone_char_p[buffer[i]], 0);
//		 // }
//		 gl11_pixels_p[buffer[i]] = -1;
//	 }

//	 //use textures_n address to get to int as texture_id
//	 // --texture_id;
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglBindTexture(JNIEnv* env, jclass clazz, jint target, jint texture, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglBindTexture_0")

//	 if (target == GL_TEXTURE_2D)
//	 {
//		 //	 info("tex_id %d", texture)
//		 gl11_current_texture = texture;
//	 }
//	 else
//	 {
//		 error("nglBindTexture_not_support %d", target)
//	 }
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTexParameteri(JNIEnv* env, jclass clazz, jint target, jint pname, jint param, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglTexParameteri_0")
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTexParameterfv(JNIEnv* env, jclass clazz, jint target, jint pname, jlong param, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglTexParameterfv_0")
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTexParameterf(JNIEnv* env, jclass clazz, jint target, jint pname, jlong param, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglTexParameterf_0")
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTexSubImage2D(JNIEnv* env, jclass clazz, jint target, jint level, jint xoffset, jint yoffset, jint width, jint height, jint format, jint type, jlong pixels, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglTexSubImage2D_0")
//	 //update pixels / we reach pixels here
//	 // info("GL11_nglTexSubImage2D_pixels %ld", pixels)

//	 if (gl11_current_texture == -1)
//	 {
//		 error("current_texture -1")
//	 }
//	 // //avoid gl
//	 // info("run_GL11$nglTexSubImage2D_0")

//	 info("gl11_current_texture %d", gl11_current_texture)

//	 info("GL11_nglTexSubImage2D_xoffset %d", xoffset)
//	 info("GL11_nglTexSubImage2D_yoffset %d", yoffset)

//	 info("GL11_nglTexSubImage2D_target %d", target)
//	 info("GL11_nglTexSubImage2D_level %d", level)
//	 info("GL11_nglTexSubImage2D_width %d", width)
//	 info("GL11_nglTexSubImage2D_height %d", height)
//	 info("GL11_nglTexSubImage2D_format %d", format)
//	 info("GL11_nglTexSubImage2D_type %d", type)
//	 info("GL11_nglTexSubImage2D_pixels %ld", pixels)

//	 info("gl11_internalformat_p[gl11_current_texture] %d", gl11_internalformat_p[gl11_current_texture]);
//	 info("gl11_type_p[gl11_current_texture] %d", gl11_type_p[gl11_current_texture]);
//	 info("GL_RGBA8 == gl11_internalformat_p[gl11_current_texture] %d", GL_RGBA8 == gl11_internalformat_p[gl11_current_texture]);
//	 info("GL_UNSIGNED_BYTE == gl11_type_p[gl11_current_texture] %d", GL_UNSIGNED_BYTE == gl11_type_p[gl11_current_texture]);
//	 info("pixels %d", 1 && pixels);
//	 if (/* (GL_RGBA8 == gl11_internalformat_p[gl11_current_texture] || GL_RGBA == gl11_internalformat_p[gl11_current_texture]) && (GL_UNSIGNED_BYTE == gl11_type_p[gl11_current_texture] || GL_UNSIGNED_SHORT_5_6_5 == gl11_type_p[gl11_current_texture]) &&  */pixels)
//	 {
//		 unsigned char* char_p = (unsigned char*)(intptr_t)pixels;
//		 // for (int xy = 0; xy < width * height; ++xy)
//		 // {
//		 //	 char pixel = char_p[xy];
//		 // }
//		 size_t length = width * height * 4 * sizeof(unsigned char);//rgba as 4 byte
//		 if (GL_UNSIGNED_BYTE == gl11_type_p[gl11_current_texture])
//		 {

//		 }
//		 if (GL_UNSIGNED_SHORT_5_6_5 == gl11_type_p[gl11_current_texture])
//		 {
//			 length = width * height * 2 * sizeof(unsigned char);//r5bit g6bit b5bit as 2 byte
//		 }
//		 unsigned char* n_clone_char_p = malloc(length);
//		 memcpy(n_clone_char_p, char_p, length);
//		 // pixels_able = 1;
//		 gl11_pixels_p[gl11_current_texture] = pixels;
//		 info("s_gl11_pixels_p[gl11_current_texture] %ld", gl11_pixels_p[gl11_current_texture]);
//		 gl11_clone_char_p[gl11_current_texture] = n_clone_char_p;
//		 info("s_gl11_clone_char_p[gl11_current_texture] %p", gl11_clone_char_p[gl11_current_texture]);
//	 }
//	 else
//	 {
//		 // pixels_able = 0;
//		 gl11_pixels_p[gl11_current_texture] = -1;
//		 gl11_clone_char_p[gl11_current_texture] = realloc(gl11_clone_char_p[gl11_current_texture], 0);
//		 info("f_gl11_pixels_p[gl11_current_texture] %ld", gl11_pixels_p[gl11_current_texture]);
//		 info("f_gl11_clone_char_p[gl11_current_texture] %p", gl11_clone_char_p[gl11_current_texture]);
//	 }
//	 //
//	 //use pixels address as index

//	 // gl11_target_p[gl11_current_texture] = target;
//	 // gl11_level_p[gl11_current_texture] = level;
//	 // gl11_width_p[gl11_current_texture] = width;
//	 // gl11_height_p[gl11_current_texture] = height;
//	 // gl11_format_p[gl11_current_texture] = format;
//	 // gl11_type_p[gl11_current_texture] = type;
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglEnable(JNIEnv* env, jclass clazz, jint cap, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglEnable_0")
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglDepthFunc(JNIEnv* env, jclass clazz, jint func, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglDepthFunc_0")
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglAlphaFunc(JNIEnv* env, jclass clazz, jint func, jfloat ref, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglAlphaFunc_0")
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglMatrixMode(JNIEnv* env, jclass clazz, jint mode, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglMatrixMode_0")
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglLoadIdentity(JNIEnv* env, jclass clazz, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglLoadIdentity_0")
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglViewport(JNIEnv* env, jclass clazz, jint x, jint y, jint width, jint height, jlong function_pointer)
// {
// }

// JNIEXPORT jint JNICALL Java_org_lwjgl_opengl_GL11_nglGenLists(JNIEnv* env, jclass clazz, jint range, jlong function_pointer)
// {
//	 return -1;
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglDisable(JNIEnv* env, jclass clazz, jint cap, jlong function_pointer)
// {
//	 // //avoid gl
//	 // info("run_GL11$nglDisable_0")
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglBlendFunc(JNIEnv* env, jclass clazz, jint sfactor, jint dfactor, jlong function_pointer)
// {
//	 //avoid gl
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglOrtho(JNIEnv* env, jclass clazz, jdouble left, jdouble right, jdouble bottom, jdouble top, jdouble zNear, jdouble zFar, jlong function_pointer)
// {
//	 //avoid gl
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglColor3ub(JNIEnv* env, jclass clazz, jbyte red, jbyte green, jbyte blue, jlong function_pointer)
// {
//	 //avoid gl
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglBegin(JNIEnv* env, jclass clazz, jint mode, jlong function_pointer)
// {
//	 //avoid gl
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTexCoord2f(JNIEnv* env, jclass clazz, jfloat s, jfloat t, jlong function_pointer)
// {
//	 //avoid gl
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglVertex2f(JNIEnv* env, jclass clazz, jfloat x, jfloat y, jlong function_pointer)
// {
//	 //avoid gl
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglEnd(JNIEnv* env, jclass clazz, jlong function_pointer)
// {
//	 //avoid gl
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglPushMatrix(JNIEnv* env, jclass clazz, jlong function_pointer)
// {
//	 //avoid gl
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTranslatef(JNIEnv* env, jclass clazz, jfloat x, jfloat y, jfloat z, jlong function_pointer)
// {
//	 //avoid gl
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglScalef(JNIEnv* env, jclass clazz, jfloat x, jfloat y, jfloat z, jlong function_pointer)
// {
//	 //avoid gl
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglColor4f(JNIEnv* env, jclass clazz, jfloat red, jfloat green, jfloat blue, jfloat alpha, jlong function_pointer)
// {
//	 //avoid gl
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglVertex3f(JNIEnv* env, jclass clazz, jfloat x, jfloat y, jfloat z, jlong function_pointer)
// {
//	 //avoid gl
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglPopMatrix(JNIEnv* env, jclass clazz, jlong function_pointer)
// {
//	 //avoid gl
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglFlush(JNIEnv* env, jclass clazz, jlong function_pointer)
// {
//	 //avoid gl
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglMultMatrixf(JNIEnv* env, jclass clazz, jlong m, jlong function_pointer)
// {
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglRotatef(JNIEnv* env, jclass clazz, jfloat angle, jfloat x, jfloat y, jfloat z, jlong function_pointer)
// {
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglDepthMask(JNIEnv* env, jclass clazz, jboolean flag, jlong function_pointer)
// {
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglVertexPointer(JNIEnv* env, jclass clazz, jint size, jint type, jint stride, jlong pointer, jlong function_pointer)
// {
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglEnableClientState(JNIEnv* env, jclass clazz, jint cap, jlong function_pointer)
// {
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTexCoordPointer(JNIEnv* env, jclass clazz, jint size, jint type, jint stride, jlong pointer, jlong function_pointer)
// {
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglColorPointer(JNIEnv* env, jclass clazz, jint size, jint type, jint stride, jlong pointer, jlong function_pointer)
// {
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglDrawArrays(JNIEnv* env, jclass clazz, jint mode, jint first, jint count, jlong function_pointer)
// {
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglDisableClientState(JNIEnv* env, jclass clazz, jint cap, jlong function_pointer)
// {
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglColorMask(JNIEnv* env, jclass clazz, jboolean red, jboolean green, jboolean blue, jboolean alpha, jlong function_pointer)
// {
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglCopyTexSubImage2D(JNIEnv* env, jclass clazz, jint target, jint level, jint xoffset, jint yoffset, jint x, jint y, jint width, jint height, jlong function_pointer)
// {
// }

// JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglShadeModel(JNIEnv* env, jclass clazz, jint mode, jlong function_pointer)
// {
// }
