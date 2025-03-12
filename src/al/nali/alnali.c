static ALCdevice* alcdevice;
static ALCcontext* alccontext;

JNIEXPORT void JNICALL Java_com_nali_NaliAL_init(JNIEnv* __env, jclass clazz)
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

JNIEXPORT jint JNICALL Java_com_nali_NaliAL_alGenSources(JNIEnv* __env, jclass clazz)
{
	ALuint i;
	alGenSources(1, &i);
	return (jint)i;
}

JNIEXPORT jint JNICALL Java_com_nali_NaliAL_alGenBuffers(JNIEnv* __env, jclass clazz)
{
	ALuint i;
	alGenBuffers(1, &i);
	return (jint)i;
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alBufferData(JNIEnv* __env, jclass clazz, jint buffer, jint format, jlong data, jint data_size, jint freq)
{
	ALvoid* data_ptr = (ALvoid* )(intptr_t)data;
	alBufferData((ALuint)buffer, (ALenum)format, data_ptr, (ALsizei)data_size, (ALsizei)freq);
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alSourcef(JNIEnv* __env, jclass clazz, jint source, jint pname, jfloat value)
{
	alSourcef((ALuint)source, (ALenum)pname, (ALfloat)value);
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alSourcei(JNIEnv* __env, jclass clazz, jint source, jint pname, jint value)
{
	alSourcei((ALuint)source, (ALenum)pname, (ALint)value);
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alSourcePlay(JNIEnv* __env, jclass clazz, jint source)
{
	alSourcePlay((ALuint)source);
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alSourceStop(JNIEnv* __env, jclass clazz, jint source)
{
	alSourceStop((ALuint)source);
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alSourcePause(JNIEnv* __env, jclass clazz, jint source)
{
	alSourcePause((ALuint)source);
}

JNIEXPORT jint JNICALL Java_com_nali_NaliAL_alGetSourcei(JNIEnv* __env, jclass clazz, jint source, jint pname)
{
	ALint i;
	alGetSourcei((ALuint)source, (ALenum)pname, &i);
	return (jint)i;
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alDeleteSources(JNIEnv* __env, jclass clazz, jint source)
{
	alDeleteSources(1, (ALuint*)&source);
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alSource3f(JNIEnv* __env, jclass clazz, jint source, jint pname, jfloat v1, jfloat v2, jfloat v3)
{
	alSource3f((ALuint)source, (ALenum)pname, (ALfloat)v1, (ALfloat)v2, (ALfloat)v3);
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alDeleteBuffers(JNIEnv* __env, jclass clazz, jint buffer)
{
	alDeleteBuffers(1, (ALuint*)&buffer);
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alListener3f(JNIEnv* __env, jclass clazz, jint pname, jfloat v1, jfloat v2, jfloat v3)
{
	alListener3f((ALenum)pname, (ALfloat)v1, (ALfloat)v2, (ALfloat)v3);
}

JNIEXPORT void JNICALL Java_com_nali_NaliAL_alListenerfv(JNIEnv* __env, jclass clazz, jint pname, jlong value)
{
	ALfloat* value_ptr = (ALfloat*)(intptr_t)value;
	alListenerfv((ALenum)pname, value_ptr);
}
