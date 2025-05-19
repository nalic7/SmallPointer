ALCdevice *m_alcdevice_p = NULL;
static ALCcontext *alccontext_p = NULL;

static ALuint buffer, source;

void al_init()
{
	nali_log("run_initAL")

	nali_info("alcOpenDevice %p", m_alcdevice_p = alcOpenDevice(NULL))

	nali_log("ALC_DEVICE_SPECIFIER %s", alcGetString(m_alcdevice_p, ALC_DEVICE_SPECIFIER))

	nali_info("alcCreateContext %p", alccontext_p = alcCreateContext(m_alcdevice_p, NULL))

	nali_info("alcMakeContextCurrent %d", alcMakeContextCurrent(alccontext_p))

	nali_info_t("alcGetError %d", alcGetError(m_alcdevice_p))

	int sample_rate, nb_channels;
	ffmpeg_read(NALI_HOME NALI_HOME_SOUND "/bgm.ogg");

	uint32_t data_bl;
	uint8_t *data_p = ffmpeg_ogg(&sample_rate, &nb_channels, &data_bl);
	ffmpeg_free();

	nali_log("nb_channels %d", nb_channels)
	ALenum format;
	if (nb_channels == 1)
		format = AL_FORMAT_MONO16;
	else if (nb_channels == 2)
		format = AL_FORMAT_STEREO16;

	alGenBuffers(1, &buffer);
	alGenSources(1, &source);

	alBufferData(buffer, format, data_p, data_bl, sample_rate);

	alSourcei(source, AL_BUFFER, buffer);
	alSourcei(source, AL_LOOPING, AL_TRUE);
	alSourcef(source, AL_GAIN, 1.0F);

	alSourcePlay(source);
}

void al_clean()
{
	alSourceStop(source);

	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);

	alcMakeContextCurrent(NULL);
	alcDestroyContext(alccontext_p);
	alccontext_p = NULL;
	alcCloseDevice(m_alcdevice_p);
	m_alcdevice_p = NULL;
}