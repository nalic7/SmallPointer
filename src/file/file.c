void *f_read(const char *c_p, uint32_t *bl_p)
{
#ifdef SMPT_CM_ST_ANDROID
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
	SMPT_DB_N2L("fopen %p", file_p)
	return f_read1(file_p, bl_p);
#endif
}

void *f_read1(FILE *file_p, uint32_t *bl_p)
{
	SMPT_DB_R2L("fseek %d", fseek(file_p, 0, SEEK_END))
	SMPT_DB_R2L("ftell %d", *bl_p = ftell(file_p))
	SMPT_DB_R2L("fseek %d", fseek(file_p, 0, SEEK_SET))

	void *p = malloc(*bl_p);
	SMPT_DB_R2L("fread %ld", fread(p, *bl_p, 1, file_p))

	SMPT_DB_R2L("fclose %d", fclose(file_p))

	return p;
}