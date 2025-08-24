static float
	x00 = 0, y00 = 0,
	x01 = 0, y01 = 0;

static int s1_set(void *p)
{
	lb_set();
	#if _CM_SERVER
		ls_set();
	#endif
	#ifdef _CM_CLIENT
		lc_set();

		_vk_set();
	//! audio android
//		al_set();
		lc_vk();
	#endif

	while (1)
	{
		AInputEvent *ainputevent_p = NULL;
		while (sa_ainputqueue_p != NULL && AInputQueue_getEvent(sa_ainputqueue_p, &ainputevent_p) >= 0)
		{
			if (AInputQueue_preDispatchEvent(sa_ainputqueue_p, ainputevent_p))
			{
				continue;
			}
			if (AInputEvent_getType(ainputevent_p) == AINPUT_EVENT_TYPE_MOTION)
			{
				size_t pointer_count = AMotionEvent_getPointerCount(ainputevent_p);
//				if (pointer_count == 1)
//				{
//					NALI_D_LOG("AINPUT_EVENT_TYPE_MOTION")
				int32_t action = AMotionEvent_getAction(ainputevent_p);
				int32_t actionType = action & AMOTION_EVENT_ACTION_MASK;

				float l_x = AMotionEvent_getX(ainputevent_p, 0);
				float l_y = AMotionEvent_getY(ainputevent_p, 0);

				if (actionType == AMOTION_EVENT_ACTION_MOVE)
				{
					lcu_xy_p[0] = l_x - x00;
					lcu_xy_p[1] = l_y - y00;
				}
				else
				{
					lcu_xy_p[0] = 0;
					lcu_xy_p[1] = 0;
				}
//					else if (/*actionType == AMOTION_EVENT_ACTION_DOWN || */actionType == AMOTION_EVENT_ACTION_UP)
//					{
//
//					}
				x00 = l_x;
				y00 = l_y;
//				}

				if (pointer_count == 2)
				{
					l_x = AMotionEvent_getX(ainputevent_p, 1);
					l_y = AMotionEvent_getY(ainputevent_p, 1);

					if (actionType == AMOTION_EVENT_ACTION_MOVE)
					{
						float l_x01 = l_x - x01;
						float l_y01 = l_y - y01;

						lcu_k |= l_y01 < -2.0F ? NALI_LB_K_W :
							l_y01 > 2.0F ? NALI_LB_K_S : 0;
						lcu_k &= l_y01 < -2.0F ? 0xFFu - NALI_LB_K_S :
							l_y01 > 2.0F ? 0xFFu - NALI_LB_K_W : 0xFFu;

						lcu_k |= l_x01 < -2.0F ? NALI_LB_K_A :
							l_x01 > 2.0F ? NALI_LB_K_D : 0;
						lcu_k &= l_x01 < -2.0F ? 0xFFu - NALI_LB_K_D :
							l_x01 > 2.0F ? 0xFFu - NALI_LB_K_A : 0xFFu;
					}

					x01 = l_x;
					y01 = l_y;
				}
			}
			AInputQueue_finishEvent(sa_ainputqueue_p, ainputevent_p, 1);
		}
	}
	return 0;
}
//JNIEXPORT void JNICALL Java_com_nali_scene_Scene_runC(JNIEnv *jnienv_p, jobject jobject)

ANativeWindow *sa_anativewindow_p = NULL;
ANativeActivity *sa_anativeactivity_p;
AInputQueue *sa_ainputqueue_p = NULL;
//static int32_t orientation;

static uint8_t a_state = 0;
#define A_STATE_WAIT 1
#define A_STATE_READY 2

static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
{
	NALI_D_LOG("window %p", window)
	_sf_width = ANativeWindow_getWidth(window);
	_sf_height = ANativeWindow_getHeight(window);
	sa_anativewindow_p = window;
}

static void onNativeWindowResized(ANativeActivity* activity, ANativeWindow* window)
{
	NALI_D_LOG("window resize")
	_sf_width = ANativeWindow_getWidth(window);
	_sf_height = ANativeWindow_getHeight(window);
	_sf_state |= _SF_S_RE;
}

static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{
	NALI_D_LOG("window 0")
	sa_anativewindow_p = NULL;
	_sf_state |= _SF_S_RE;
}

//static void onConfigurationChanged(ANativeActivity* activity)
//{
//	NALI_D_LOG("onConfigurationChanged")
//
//	AConfiguration *aconfiguration_p = AConfiguration_new();
//	AConfiguration_fromAssetManager(aconfiguration_p, activity->assetManager);
//
//	orientation = AConfiguration_getOrientation(aconfiguration_p);
//
//	NALI_D_LOG("orientation %d", orientation)
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
	sa_ainputqueue_p = queue;
}

static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
{
	sa_ainputqueue_p = NULL;
}

void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
	#ifdef NALI_D_FILE
		d_set();
	#endif

	NALI_D_LOG("ANativeActivity_onCreate")
	if (!(a_state & A_STATE_READY))
	{
		a_state |= A_STATE_READY;
		NALI_D_LOG("scene")
		NALI_D_INFO("thrd_create %d", thrd_create(&(thrd_t){}, s1_set, NULL))
	}
	activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
	activity->callbacks->onNativeWindowResized = onNativeWindowResized;
	activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
	activity->callbacks->onInputQueueCreated = onInputQueueCreated;
	activity->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;
//	activity->callbacks->onConfigurationChanged = onConfigurationChanged;
	sa_anativeactivity_p = activity;

//	SLObjectItf slobjectitf;
//	NALI_D_INFO("slCreateEngine %d", slCreateEngine(&slobjectitf, 0, NULL, 0, NULL, NULL))
}

void sa_wait()
{
	while (!sa_anativewindow_p)
	{
		a_state |= A_STATE_WAIT;
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	if (a_state & A_STATE_WAIT)
	{
//		lc_set();
//		vk_init();
////		al_set();
//		lc_vk();

//		vk_freeDevice();
//		vk_freeQueue();
		_vk_sf_free();
		_vk_sf_make();
//		vk_initQueue();
//		vk_initDevice();
//		vk_setQueue(vk_device);
//		vk_makeDevice(vk_device);
//		vk_getQueue(vk_device);

//		m_surface_state |= _SF_S_EXIT;
		_sf_state |= _SF_S_RE;
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
