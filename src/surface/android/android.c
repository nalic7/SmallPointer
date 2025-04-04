ANativeWindow *m_anativewindow_p = NULL;

static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
{
	nali_log("window %p", window);
	m_anativewindow_p = window;
}

static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{
	nali_log("window 0");
	m_anativewindow_p = NULL;
}

void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
	nali_log("ANativeActivity_onCreate")
	scene_init();
	activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
	activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
}