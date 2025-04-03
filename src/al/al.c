ALCdevice *m_alcdevice_p = NULL;
static ALCcontext *alccontext_p = NULL;

void al_init()
{
	nali_log("run_initAL")

	nali_info("alcOpenDevice %p", m_alcdevice_p = alcOpenDevice(NULL))

	nali_log("ALC_DEVICE_SPECIFIER %s", alcGetString(m_alcdevice_p, ALC_DEVICE_SPECIFIER))

	nali_info("alcCreateContext %p", alccontext_p = alcCreateContext(m_alcdevice_p, NULL))

	nali_info("alcMakeContextCurrent %d", alcMakeContextCurrent(alccontext_p))

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
	alccontext_p = NULL;
	alcCloseDevice(m_alcdevice_p);
	m_alcdevice_p = NULL;
}