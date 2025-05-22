Display* display;
Window root;
GLXContext glx_context;
XVisualInfo* visual_info;
XSetWindowAttributes swa;
Window win;
Colormap cmap;

void initOpenGL()
{
	// Connect to X server
	display = XOpenDisplay(NULL);
	if (!display)
	{
		error("XOpenDisplay")
	}

	root = DefaultRootWindow(display);

	// Get a visual
	static int visual_attribs[] =
	{
		GLX_X_RENDERABLE, True,
		GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
		GLX_RENDER_TYPE, GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_ALPHA_SIZE, 8,
		None
	};

	GLXFBConfig* fbconfigs;
	int fbcount;

	fbconfigs = glXChooseFBConfig(display, DefaultScreen(display), visual_attribs, &fbcount);
	if (!fbconfigs)
	{
		error("glXChooseFBConfig")
	}

	visual_info = glXGetVisualFromFBConfig(display, fbconfigs[0]);

	// Create a colormap
	cmap = XCreateColormap(display, root, visual_info->visual, AllocNone);

	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;

	// Create a window
	win = XCreateWindow(display, root, 0, 0, 1, 1, 0, visual_info->depth, InputOutput, visual_info->visual, CWColormap | CWEventMask, &swa);
	XMapWindow(display, win);

	// Create an OpenGL context
	glx_context = glXCreateContext(display, visual_info, NULL, GL_TRUE);
	if (!glx_context)
	{
		error("glXCreateContext")
	}

	// Make the context current
	if (!glXMakeCurrent(display, win, glx_context))
	{
		error("glXMakeCurrent")
	}

	// // Your OpenGL rendering code here

	// // Cleanup
	// glXDestroyContext(display, glx_context);
	// XDestroyWindow(display, win);
	// XCloseDisplay(display);

	// return 0;
	XUnmapWindow(display, win);
	XFlush(display);
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_GLContext_nLoadOpenGLLibrary(JNIEnv* env, jclass clazz)
{
	// //init vulkan
	// //avoid gl
	// info("run_nLoadOpenGLLibrary_0")
	initOpenGL();

	// gl11_target_p = malloc(0);
	// gl11_level_p = malloc(0);
	// gl11_internalformat_p = malloc(0);
	// gl11_width_p = malloc(0);
	// gl11_height_p = malloc(0);
	// gl11_border_p = malloc(0);
	// gl11_format_p = malloc(0);
	// gl11_type_p = malloc(0);
	// gl11_pixels_p = malloc(0);
	gl11_modify_texture_p = malloc(0);
	gl11_texture_p = malloc(0);
	// gl11_clone_char_p = malloc(0);
	// info("gl11_clone_char_p %p", gl11_clone_char_p)

	gl11_int8_pixels = malloc(0);
	gl11_width = malloc(0);
	gl11_height = malloc(0);
	gl11_type = malloc(0);

	surface_init();
	vk_init();
	al_set();
}

// void* extgl_GetProcAddress(const char* name)
// {
//	 //set name as address
//	 // void* t = eglGetProcAddress(name);

//	 // if ( t == NULL ) {
// 	// 	t = dlsym(lib_gl_handle, name);
// 	// 	if ( t == NULL )
//	 //		 infoDebug("Could not locate symbol %s", name);
//	 // }

// 	// return t;
//	 // return (void*)-1;
//	 return 0;
// }

JNIEXPORT jlong JNICALL Java_org_lwjgl_opengl_GLContext_ngetFunctionAddress(JNIEnv* env, jclass clazz, jlong function_name)
{
	// //avoid gl
	// info("run_GLContext$ngetFunctionAddress_0")
	// return (jlong)(intptr_t)extgl_GetProcAddress((char*)(intptr_t)function_name);
	return -1;
}
