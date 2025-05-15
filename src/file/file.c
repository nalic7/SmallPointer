void *f_read(const char *name_char_p, long *size_p)
{
#ifdef NALI_OS_ANDROID
	AAssetManager *aassetmanager_p = m_anativeactivity_p->assetManager;
	AAsset *aasset_p = AAssetManager_open(aassetmanager_p, name_char_p, AASSET_MODE_BUFFER);
	*size_p = AAsset_getLength(aasset_p);
	const void* data = AAsset_getBuffer(aasset_p);

	void *p = malloc(*size_p);
	memcpy(p, data, *size_p);

	AAsset_close(aasset_p);

	return p;
#else
	FILE *file_p = fopen(name_char_p, "rb");
	nali_log("fopen %p", file_p)

	nali_info("fseek %d", fseek(file_p, 0, SEEK_END))
	nali_info("ftell %ld", *size_p = ftell(file_p))
	nali_info("fseek %d", fseek(file_p, 0, SEEK_SET))

	void *p = malloc(*size_p);
	nali_info("fread %ld", fread(p, *size_p, 1, file_p))

	nali_info("fclose %d", fclose(file_p))
	return p;
#endif
}