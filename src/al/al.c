ALCdevice* m_alcdevice;
ALCcontext* alccontext;

void al_init()
{
	info("run_initAL")

	m_alcdevice = alcOpenDevice(NULL);
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

	// ALuint buffer;
	// ALuint source;
	// alGenBuffers(1, &buffer);
	// alGenSources(1, &source);

	// alSourcePlay(source);

	// alDeleteSources(1, &source);
	// alDeleteBuffers(1, &buffer);
}

void al_clean()
{
	alcMakeContextCurrent(NULL);
    alcDestroyContext(alccontext);
    alcCloseDevice(m_alcdevice);
}