void *f_read(const char *c_p, uint32_t *bl_p)
{
#ifdef NALI_S_ANDROID
	AAssetManager *aassetmanager_p = sa_anativeactivity_p->assetManager;
	AAsset *aasset_p = AAssetManager_open(aassetmanager_p, c_p, AASSET_MODE_BUFFER);
	*bl_p = AAsset_getLength(aasset_p);
	const void* data = AAsset_getBuffer(aasset_p);

	void *p = malloc(*bl_p);
	memcpy(p, data, *bl_p);

	AAsset_close(aasset_p);

	return p;
#else
	FILE *file_p = fopen(c_p, "rb");
	nali_log("fopen %p", file_p)

	nali_info("fseek %d", fseek(file_p, 0, SEEK_END))
	nali_info("ftell %d", *bl_p = ftell(file_p))
	nali_info("fseek %d", fseek(file_p, 0, SEEK_SET))

	void *p = malloc(*bl_p);
	nali_info("fread %ld", fread(p, *bl_p, 1, file_p))

	nali_info("fclose %d", fclose(file_p))
	return p;
#endif
}