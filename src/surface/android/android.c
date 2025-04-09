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

//	SLObjectItf slobjectitf;
//	nali_info("slCreateEngine %d", slCreateEngine(&slobjectitf, 0, NULL, 0, NULL, NULL))
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