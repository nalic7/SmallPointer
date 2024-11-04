ALCdevice *m_alcdevice;
ALCcontext *alccontext;

JNIEXPORT void JNICALL Java_com_nali_NaliAL_init(JNIEnv *__env, jclass clazz)
{
	m_alcdevice = alcOpenDevice(NULL);
	if (!m_alcdevice)
	{
		error("alcOpenDevice")
	}

	alccontext = alcCreateContext(m_alcdevice, NULL);
	if (!alccontext)
	{
		error("alcCreateContext")
	}

	if (!alcMakeContextCurrent(alccontext))
	{
		error("alcMakeContextCurrent")
	}
}

JNIEXPORT jint JNICALL Java_com_nali_NaliAL_alGenSources(JNIEnv *__env, jclass clazz)
{
	ALuint i;
	alGenSources(1, &i);
	return (jint)i;
}

JNIEXPORT jint JNICALL Java_com_nali_NaliAL_alGenBuffers(JNIEnv *__env, jclass clazz)
{
	ALuint i;
	alGenBuffers(1, &i);
	return (jint)i;
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alBufferData(JNIEnv *__env, jclass clazz, jint buffer, jint format, jlong data, jint data_size, jint freq)
{
	ALvoid* data_ptr = (ALvoid *)(intptr_t)data;
	alBufferData((ALuint)buffer, (ALenum)format, data_ptr, (ALsizei)data_size, (ALsizei)freq);
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alSourcef(JNIEnv *__env, jclass clazz, jint source, jint pname, jfloat value)
{
	alSourcef((ALuint)source, (ALenum)pname, (ALfloat)value);
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alSourcei(JNIEnv *__env, jclass clazz, jint source, jint pname, jint value)
{
	alSourcei((ALuint)source, (ALenum)pname, (ALint)value);
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alSourcePlay(JNIEnv *__env, jclass clazz, jint source)
{
	alSourcePlay((ALuint)source);
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alSourceStop(JNIEnv *__env, jclass clazz, jint source)
{
	alSourceStop((ALuint)source);
}
