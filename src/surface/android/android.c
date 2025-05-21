ANativeWindow *m_anativewindow_p = NULL;
ANativeActivity *m_anativeactivity_p;
AInputQueue *m_ainputqueue_p = NULL;
//static int32_t orientation;

static uint8_t a_state = 0;
#define A_STATE_WAIT 1
#define A_STATE_READY 2

static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
{
	nali_log("window %p", window)
	s_width = ANativeWindow_getWidth(window);
	s_height = ANativeWindow_getHeight(window);
	m_anativewindow_p = window;
}

static void onNativeWindowResized(ANativeActivity* activity, ANativeWindow* window)
{
	nali_log("window resize")
	s_width = ANativeWindow_getWidth(window);
	s_height = ANativeWindow_getHeight(window);
	s_surface_state |= NALI_SURFACE_C_S_RE;
}

static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{
	nali_log("window 0")
	m_anativewindow_p = NULL;
	s_surface_state |= NALI_SURFACE_C_S_RE;
}

//static void onConfigurationChanged(ANativeActivity* activity)
//{
//	nali_log("onConfigurationChanged")
//
//	AConfiguration *aconfiguration_p = AConfiguration_new();
//	AConfiguration_fromAssetManager(aconfiguration_p, activity->assetManager);
//
//	orientation = AConfiguration_getOrientation(aconfiguration_p);
//
//	nali_log("orientation %d", orientation)
////	if (orientation == ACONFIGURATION_ORIENTATION_PORT)
////	{
////	}
////	else if (orientation == ACONFIGURATION_ORIENTATION_LAND)
////	{
////	}
////	else
////	{
////	}
//
//	AConfiguration_delete(aconfiguration_p);
//}

static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue)
{
	m_ainputqueue_p = queue;
}

static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
{
	m_ainputqueue_p = NULL;
}

void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
	nali_log("ANativeActivity_onCreate")
	if (!(a_state & A_STATE_READY))
	{
		a_state |= A_STATE_READY;
		scene_init();
	}
	activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
	activity->callbacks->onNativeWindowResized = onNativeWindowResized;
	activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
	activity->callbacks->onInputQueueCreated = onInputQueueCreated;
	activity->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;
//	activity->callbacks->onConfigurationChanged = onConfigurationChanged;
	m_anativeactivity_p = activity;

//	SLObjectItf slobjectitf;
//	nali_info("slCreateEngine %d", slCreateEngine(&slobjectitf, 0, NULL, 0, NULL, NULL))
}

void a_wait()
{
	while (!m_anativewindow_p)
	{
		a_state |= A_STATE_WAIT;
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	if (a_state & A_STATE_WAIT)
	{
//		lc_init();
//		vk_init();
////		al_init();
//		lc_vk();

//		vk_freeDevice();
//		vk_freeQueue();
		VK_freeSurface
		VK_makeSurface
//		vk_initQueue();
//		vk_initDevice();
//		vk_setQueue(m_device);
//		vk_makeDevice(m_device);
//		vk_getQueue(m_device);

//		m_surface_state |= NALI_SURFACE_C_S_CLEAN;
		s_surface_state |= NALI_SURFACE_C_S_RE;
		a_state &= 0xFFu - A_STATE_WAIT;
	}
}

//AAudioStreamDataCallbackResult data_callback(AAudioStream *stream, void *userData, void *audioData, int32_t numFrames) {
//	// Fill audioData with the samples to be played
//	// For this example, we'll just produce silence (zeros)
//	float *buffer = (float*)audioData;
//	for (int i = 0; i < numFrames; i++) {
//		buffer[i] = 0.0f;  // Silence
//	}
//	return AAUDIO_STREAM_DATA_CALLBACK_RESULT_CONTINUE;
//}
//
//void play_audio() {
//	AAudioStreamBuilder *builder = NULL;
//	AAudioStream *stream = NULL;
//
//	// Create the AAudio stream builder
//	AAudio_createStreamBuilder(&builder);
//
//	// Set the callback function
//	AAudioStreamBuilder_setDataCallback(builder, data_callback);
//
//	// Configure the stream parameters (e.g., format, channels, sample rate)
//	AAudioStreamBuilder_setFormat(builder, AAUDIO_FORMAT_PCM_FLOAT);
//	AAudioStreamBuilder_setChannelCount(builder, 1);  // Mono
//	AAudioStreamBuilder_setSampleRate(builder, 44100); // 44.1 kHz
//
//	// Open the stream
//	AAudio_createStream(builder, &stream);
//
//	// Start the stream for playback
//	AAudioStream_requestStart(stream);
//
//	// Let the audio play for a few seconds (e.g., 5 seconds)
//	usleep(5000000);  // 5 seconds in microseconds
//
//	// Stop and release the stream
//	AAudioStream_requestStop(stream);
//	AAudioStream_close(stream);
//}