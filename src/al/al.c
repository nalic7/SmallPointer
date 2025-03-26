ALCdevice *m_alcdevice_p;
ALCcontext *alccontext_p;

void al_init()
{
	info("run_initAL")

	m_alcdevice_p = alcOpenDevice(NULL);
	if (!m_alcdevice_p)
	{
		error("alcOpenDevice")
	}

	info("ALC_DEVICE_SPECIFIER %s", alcGetString(m_alcdevice_p, ALC_DEVICE_SPECIFIER))

	alccontext_p = alcCreateContext(m_alcdevice_p, NULL);
	if (!alccontext_p)
	{
		error("alcCreateContext")
		// alcCloseDevice(device);
	}

	if (!alcMakeContextCurrent(alccontext_p))
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
	alcDestroyContext(alccontext_p);
	alcCloseDevice(m_alcdevice_p);
}