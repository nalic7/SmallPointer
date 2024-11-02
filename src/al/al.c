ALCdevice *m_alcdevice;
ALCcontext *alccontext;

void al_init()
{
	info("run_initAL")

	// Initialize OpenAL
	m_alcdevice = alcOpenDevice(NULL); // Open the default device
	if (!m_alcdevice)
	{
		error("alcOpenDevice")
	}

	alccontext = alcCreateContext(m_alcdevice, NULL);
	if (!alccontext)
	{
		error("alcCreateContext")
		// alcCloseDevice(device);
	}

	if (!alcMakeContextCurrent(alccontext))
	{
		error("alcMakeContextCurrent")
	}

	// // Create a buffer and source
	// ALuint buffer;
	// ALuint source;
	// alGenBuffers(1, &buffer);
	// alGenSources(1, &source);

	// // Load and set up audio data here (omitted for brevity)

	// // Play the sound
	// alSourcePlay(source);

	// // Clean up
	// alDeleteSources(1, &source);
	// alDeleteBuffers(1, &buffer);
	// alcMakeContextCurrent(NULL);
	// alcDestroyContext(context);
	// alcCloseDevice(device);
}
