uint32_t gl11_gl_texture_2d = 0;
uint32_t* gl11_modify_texture_p = 0;
long* gl11_texture_p;

uint32_t max_texture = 0;
uint32_t modify_texture = 0;
uint32_t png = 0;

void save_png(const char* filename/* , intptr_t image */, uint32_t* img, int width, int height/* , int size */, int type)
{
	FILE* fp = fopen(filename, "wb");
	if (!fp)
	{
		error("fopen")
	}

	png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png)
	{
		error("png_create_write_struct")
	}

	png_infop info = png_create_info_struct(png);
	if (!info)
	{
		error("png_create_info_struct")
	}

	if (setjmp(png_jmpbuf(png)))
	{
		error("png_jmpbuf")
	}

	png_init_io(png, fp);

	png_set_IHDR
	(
		png,
		info,
		width, height,
		8,
		/* size == 3 ? PNG_COLOR_TYPE_RGB :  */PNG_COLOR_TYPE_RGBA,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT
	);

	png_write_info(png, info);

	// png_bytep rows[height];
	png_bytep* rows;
	if (type == GL_UNSIGNED_INT_8_8_8_8_REV)
	{
		info("GL_UNSIGNED_INT_8_8_8_8_REV");
		// uint32_t* img = (uint32_t*)image;
		rows = (png_bytep*)malloc(height * sizeof(png_bytep));

		for (int y = 0; y < height; y++)
		{
			rows[y] = (png_bytep)malloc(width * 4); // 4 bytes per pixel (RGBA)
			for (int x = 0; x < width; x++)
			{
				uint32_t pixel = img[y * width + x];

				// Extract components in ABGR order
				uint8_t a = (pixel >> 24) & 0xFFu;
				uint8_t b = (pixel >> 16) & 0xFFu;
				uint8_t g = (pixel >> 8) & 0xFFu;
				uint8_t r = pixel & 0xFFu;

				// // Store in RGBA order
				// rows[y][x * 4 + 0] = r;
				// rows[y][x * 4 + 1] = g;
				// rows[y][x * 4 + 2] = b;
				// rows[y][x * 4 + 3] = a;

				rows[y][x * 4 + 0] = b;
				rows[y][x * 4 + 1] = g;
				rows[y][x * 4 + 2] = r;
				rows[y][x * 4 + 3] = a;
			}
		}
	}
	/*else if (type == GL_UNSIGNED_SHORT_5_6_5)
	{
		info("GL_UNSIGNED_SHORT_5_6_5")
		png_bytep n_rows[height];
		rows = n_rows;
		unsigned char* img = (unsigned char*)image;
		unsigned char png_pixels[width * height * 3 * sizeof(unsigned char)];
		for (int i = 0; i < width * height; i++)
		{
			unsigned char pixel = img[i];

			unsigned char red = (pixel >> 11) & 0x1F;  // 5 bits
			red = (red * 255) / 31;					// Scale to 8 bits

			unsigned char green = (pixel >> 5) & 0x3F; // 6 bits
			green = (green * 255) / 63;				// Scale to 8 bits

			unsigned char blue = pixel & 0x1F;		 // 5 bits
			blue = (blue * 255) / 31;				  // Scale to 8 bits

			png_pixels[i * 3 + 0] = red;
			png_pixels[i * 3 + 1] = green;
			png_pixels[i * 3 + 2] = blue;
		}
		for (int i = 0; i < height; ++i)
		{
			// rows[i] = png_pixels + (i * width * size);
			rows[i] = png_pixels + (i * width * 4);
		}
	} */
	// else if (type == GL_UNSIGNED_BYTE)
	// {
	//	 info("GL_UNSIGNED_BYTE")
	//	 rows = (png_bytep*)malloc(height * sizeof(png_bytep));
	//	 unsigned char* img = (unsigned char*)image;
	//	 for (int i = 0; i < height; ++i)
	//	 {
	//		 // rows[i] = image + (i * width * size);
	//		 rows[i] = img + (i * width * 4);
	//	 }
	// }
	else
	{
		error("TYPE %d", type)
	}

	png_set_rows(png, info, rows);
	png_write_image(png, rows);

	png_write_end(png, info);

	free(rows);
	png_destroy_write_struct(&png, &info);
	fclose(fp);
}

JNIEXPORT jstring JNICALL Java_org_lwjgl_opengl_GL11_nglGetString(JNIEnv* env, jclass clazz, jint name, jlong function_pointer)
{
	const GLubyte* glString = glGetString(name);
	return (*env)->NewStringUTF(env, (const char*)glString);
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglGetIntegerv(JNIEnv* env, jclass clazz, jint pname, jlong params, jlong function_pointer)
{
	GLint* paramBuffer = (GLint*)params;
	glGetIntegerv((GLenum)pname, paramBuffer);
}

JNIEXPORT jint JNICALL Java_org_lwjgl_opengl_GL11_nglGetError(JNIEnv* env, jclass clazz, jlong function_pointer)
{
	return 0;
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglClearColor(JNIEnv* env, jclass clazz, jfloat red, jfloat green, jfloat blue, jfloat alpha, jlong function_pointer)
{
	// //avoid gl
	// info("run_GL11$nglClearColor_0")
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglClear(JNIEnv* env, jclass clazz, jint mask, jlong function_pointer)
{
	// //avoid gl
	// info("run_GL11$nglClear_0")
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTexImage2D(JNIEnv* env, jclass clazz, jint target, jint level, jint internalformat, jint width, jint height, jint border, jint format, jint type, jlong pixels, jlong function_pointer)
{
	if (pixels && gl11_gl_texture_2d > 0)
	{
		error("Java_org_lwjgl_opengl_GL11_nglTexImage2D")
	}
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglGetTexLevelParameteriv(JNIEnv* env, jclass clazz, jint target, jint level, jint pname, jlong params, jlong function_pointer)
{
	// //avoid gl
	// info("run_GL11$nglGetTexLevelParameteriv_0")
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglGenTextures(JNIEnv* env, jclass clazz, jint textures_n, jlong textures, jlong function_pointer)
{
	for (uint32_t i = 0; i < textures_n; ++i)
	{
		int* int_p = (int*)(intptr_t)textures;
		int texture_index;

		info("g_gl11_textures_buffer[%d] -> %d", i, int_p[i])

		if (modify_texture > 0)
		{
			--modify_texture;
			texture_index = gl11_modify_texture_p[modify_texture];
			gl11_modify_texture_p = realloc(gl11_modify_texture_p, sizeof(uint32_t) * modify_texture);
		}
		else
		{
			++max_texture;
			texture_index = max_texture;

			size_t long_size = sizeof(long) * max_texture;
			size_t int_size = sizeof(int) * max_texture;
			gl11_texture_p = realloc(gl11_texture_p, long_size);
		}

		info("g_gl11_textures_buffer[%d] <- %d", i, texture_index)

		int_p[i] = texture_index;
	}
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglDeleteTextures(JNIEnv* env, jclass clazz, jint textures_n, jlong textures, jlong function_pointer)
{
	int* buffer = (int*)(intptr_t)textures;
	for (int i = 0; i < textures_n; ++i)
	{
		info("d_gl11_textures_buffer[%d] -> %d", i, buffer[i])
		++modify_texture;
		gl11_modify_texture_p = realloc(gl11_modify_texture_p, sizeof(uint32_t) * modify_texture);
		gl11_modify_texture_p[modify_texture - 1] = buffer[i];
	}
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglBindTexture(JNIEnv* env, jclass clazz, jint target, jint texture, jlong function_pointer)
{
	if (target == GL_TEXTURE_2D)
	{
		gl11_gl_texture_2d = texture;
	}
	else
	{
		error("Java_org_lwjgl_opengl_GL11_nglBindTexture")
	}
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTexParameteri(JNIEnv* env, jclass clazz, jint target, jint pname, jint param, jlong function_pointer)
{
	// //avoid gl
	// info("run_GL11$nglTexParameteri_0")
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTexParameterfv(JNIEnv* env, jclass clazz, jint target, jint pname, jlong param, jlong function_pointer)
{
	// //avoid gl
	// info("run_GL11$nglTexParameterfv_0")
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTexParameterf(JNIEnv* env, jclass clazz, jint target, jint pname, jlong param, jlong function_pointer)
{
	// //avoid gl
	// info("run_GL11$nglTexParameterf_0")
}

// long *gl11_pixels;
uint32_t **gl11_int8_pixels;
int *gl11_width;
int *gl11_height;
int *gl11_type;
uint32_t max_pixels = 0;

// int img_loop(void* v)
// {
//	 struct timespec ts = {60, 0};
//	 thrd_sleep(&ts, NULL);

//	 //detect img leak
//	 // for (uint32_t i = 0; i < max_pixels; ++i)
//	 // {
//	 //	 uint32_t num = get_num_digits(png);
//	 //	 char* num_char_p = malloc(num + 1);
//	 //	 snprintf(num_char_p, num + 1, "%d", png++);
//	 //	 char* mid_char_p = combine("output/", num_char_p);
//	 //	 char* final_char_p = combine(mid_char_p, ".png");
//	 //	 save_png(final_char_p, (intptr_t)gl11_pixels[i], gl11_width[i], gl11_height[i], gl11_type[i]);
//	 //	 free(final_char_p);
//	 //	 free(mid_char_p);
//	 //	 free(num_char_p);
//	 // }

//	 for (uint32_t i = 0; i < max_pixels; ++i)
//	 {
//		 uint32_t num = get_num_digits(png);
//		 char* num_char_p = malloc(num + 1);
//		 snprintf(num_char_p, num + 1, "%d", png++);
//		 char* mid_char_p = combine("output/", num_char_p);
//		 char* final_char_p = combine(mid_char_p, ".png");
//		 save_png(final_char_p, gl11_int8_pixels[i], gl11_width[i], gl11_height[i], gl11_type[i]);
//		 free(final_char_p);
//		 free(mid_char_p);
//		 free(num_char_p);
//	 }
//	 return 0;
// }

//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 10, 10, GL_RGBA, GL_UNSIGNED_BYTE, newPixelData); update 0 0 - 10 10
char start = 0;
JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTexSubImage2D(JNIEnv* env, jclass clazz, jint target, jint level, jint xoffset, jint yoffset, jint width, jint height, jint format, jint type, jlong pixels, jlong function_pointer)
{
	if (pixels && gl11_gl_texture_2d > 0)
	{
		uint32_t index = max_pixels;
		gl11_int8_pixels = realloc(gl11_int8_pixels, sizeof(long*) * ++max_pixels);
		gl11_width = realloc(gl11_width, sizeof(int) * max_pixels);
		gl11_height = realloc(gl11_height, sizeof(int) * max_pixels);
		gl11_type = realloc(gl11_type, sizeof(int) * max_pixels);

		size_t length = width * height * 4;
		uint32_t* n_clone_char_p = malloc(length);
		memcpy(n_clone_char_p, (uint32_t*)(intptr_t)pixels, length);
//		 // pixels_able = 1;
//		 gl11_pixels_p[gl11_current_texture] = pixels;
//		 info("s_gl11_pixels_p[gl11_current_texture] %ld", gl11_pixels_p[gl11_current_texture]);
//		 gl11_clone_char_p[gl11_current_texture] = n_clone_char_p;
//		 info("s_gl11_clone_char_p[gl11_current_texture] %p", gl11_clone_char_p[gl11_current_texture]);

		gl11_int8_pixels[index] = n_clone_char_p;
		// gl11_pixels[index] = pixels;
		gl11_width[index] = width;
		gl11_height[index] = height;
		gl11_type[index] = type;
		// uint32_t num = get_num_digits(png);
		// char* num_char_p = malloc(num + 1);
		// snprintf(num_char_p, num + 1, "%d", png++);
		// char* mid_char_p = combine("output/", num_char_p);
		// char* final_char_p = combine(mid_char_p, ".png");
		// save_png(final_char_p, (intptr_t)pixels, width, height, type);
		// free(final_char_p);
		// free(mid_char_p);
		// free(num_char_p);
	}

	// if (!start)
	// {
	//	 thrd_t thread;
	//	 int result = thrd_create(&thread, img_loop, NULL);
	//	 if (result != thrd_success)
	//	 {
	//		 error("thrd_create")
	//	 }
	//	 start = 1;
	// }
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglEnable(JNIEnv* env, jclass clazz, jint cap, jlong function_pointer)
{
	// //avoid gl
	// info("run_GL11$nglEnable_0")
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglDepthFunc(JNIEnv* env, jclass clazz, jint func, jlong function_pointer)
{
	// //avoid gl
	// info("run_GL11$nglDepthFunc_0")
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglAlphaFunc(JNIEnv* env, jclass clazz, jint func, jfloat ref, jlong function_pointer)
{
	// //avoid gl
	// info("run_GL11$nglAlphaFunc_0")
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglMatrixMode(JNIEnv* env, jclass clazz, jint mode, jlong function_pointer)
{
	// //avoid gl
	// info("run_GL11$nglMatrixMode_0")
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglLoadIdentity(JNIEnv* env, jclass clazz, jlong function_pointer)
{
	// //avoid gl
	// info("run_GL11$nglLoadIdentity_0")
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglViewport(JNIEnv* env, jclass clazz, jint x, jint y, jint width, jint height, jlong function_pointer)
{
}

JNIEXPORT jint JNICALL Java_org_lwjgl_opengl_GL11_nglGenLists(JNIEnv* env, jclass clazz, jint range, jlong function_pointer)
{
	return -1;
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglDisable(JNIEnv* env, jclass clazz, jint cap, jlong function_pointer)
{
	// //avoid gl
	// info("run_GL11$nglDisable_0")
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglBlendFunc(JNIEnv* env, jclass clazz, jint sfactor, jint dfactor, jlong function_pointer)
{
	//avoid gl
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglOrtho(JNIEnv* env, jclass clazz, jdouble left, jdouble right, jdouble bottom, jdouble top, jdouble zNear, jdouble zFar, jlong function_pointer)
{
	//avoid gl
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglColor3ub(JNIEnv* env, jclass clazz, jbyte red, jbyte green, jbyte blue, jlong function_pointer)
{
	//avoid gl
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglBegin(JNIEnv* env, jclass clazz, jint mode, jlong function_pointer)
{
	//avoid gl
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTexCoord2f(JNIEnv* env, jclass clazz, jfloat s, jfloat t, jlong function_pointer)
{
	//avoid gl
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglVertex2f(JNIEnv* env, jclass clazz, jfloat x, jfloat y, jlong function_pointer)
{
	//avoid gl
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglEnd(JNIEnv* env, jclass clazz, jlong function_pointer)
{
	//avoid gl
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglPushMatrix(JNIEnv* env, jclass clazz, jlong function_pointer)
{
	//avoid gl
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTranslatef(JNIEnv* env, jclass clazz, jfloat x, jfloat y, jfloat z, jlong function_pointer)
{
	//avoid gl
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglScalef(JNIEnv* env, jclass clazz, jfloat x, jfloat y, jfloat z, jlong function_pointer)
{
	//avoid gl
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglColor4f(JNIEnv* env, jclass clazz, jfloat red, jfloat green, jfloat blue, jfloat alpha, jlong function_pointer)
{
	//avoid gl
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglVertex3f(JNIEnv* env, jclass clazz, jfloat x, jfloat y, jfloat z, jlong function_pointer)
{
	//avoid gl
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglPopMatrix(JNIEnv* env, jclass clazz, jlong function_pointer)
{
	//avoid gl
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglFlush(JNIEnv* env, jclass clazz, jlong function_pointer)
{
	//avoid gl
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglMultMatrixf(JNIEnv* env, jclass clazz, jlong m, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglRotatef(JNIEnv* env, jclass clazz, jfloat angle, jfloat x, jfloat y, jfloat z, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglDepthMask(JNIEnv* env, jclass clazz, jboolean flag, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglVertexPointer(JNIEnv* env, jclass clazz, jint size, jint type, jint stride, jlong pointer, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglEnableClientState(JNIEnv* env, jclass clazz, jint cap, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglTexCoordPointer(JNIEnv* env, jclass clazz, jint size, jint type, jint stride, jlong pointer, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglColorPointer(JNIEnv* env, jclass clazz, jint size, jint type, jint stride, jlong pointer, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglDrawArrays(JNIEnv* env, jclass clazz, jint mode, jint first, jint count, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglDisableClientState(JNIEnv* env, jclass clazz, jint cap, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglColorMask(JNIEnv* env, jclass clazz, jboolean red, jboolean green, jboolean blue, jboolean alpha, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglCopyTexSubImage2D(JNIEnv* env, jclass clazz, jint target, jint level, jint xoffset, jint yoffset, jint x, jint y, jint width, jint height, jlong function_pointer)
{
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GL11_nglShadeModel(JNIEnv* env, jclass clazz, jint mode, jlong function_pointer)
{
}
