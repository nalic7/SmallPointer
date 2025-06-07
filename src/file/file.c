void *f_read(const char *c_p, uint32_t *bl_p)
{
#ifdef C_NALI_S_ANDROID
	AAssetManager *aassetmanager_p = sa_anativeactivity_p->assetManager;
	AAsset *aasset_p = AAssetManager_open(aassetmanager_p, c_p, AASSET_MODE_BUFFER);
	*bl_p = AAsset_getLength(aasset_p);
	const void* data = AAsset_getBuffer(aasset_p);

	void *p = malloc(*bl_p);
	memcpy(p, data, *bl_p);

	AAsset_close(aasset_p);

	return p;
#else
	return f_read1(fopen(c_p, "rb"), bl_p);
#endif
}

void *f_read1(FILE *file_p, uint32_t *bl_p)
{
	NALI_D_LOG("fopen %p", file_p)

	NALI_D_INFO("fseek %d", fseek(file_p, 0, SEEK_END))
	NALI_D_INFO("ftell %d", *bl_p = ftell(file_p))
	NALI_D_INFO("fseek %d", fseek(file_p, 0, SEEK_SET))

	void *p = malloc(*bl_p);
	NALI_D_INFO("fread %ld", fread(p, *bl_p, 1, file_p))

	NALI_D_INFO("fclose %d", fclose(file_p))

	return p;
}