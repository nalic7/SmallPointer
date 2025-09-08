static mtx_t *Pmtx_t = &(mtx_t){};
static FILE *Pfile;

void smpt_dbMset()
{
	int l0 = mtx_init(Pmtx_t, mtx_plain);
	int l1 = mkdir(NALI_F_SAVE, S_IRUSR | S_IWUSR | S_IXUSR);
	int l2 = remove(NALI_F_SAVE_LOG);
	Pfile = fopen(NALI_F_SAVE_LOG, "ab");

	SMPT_DBmN2L("mtx_init %d", l0)
	SMPT_DBmN2L("mkdir %d", l1)
	SMPT_DBmN2L("remove %d", l2)
	SMPT_DBmN2L("fopen %p", Pfile)

	SMPT_DBmN2L("_SC_OPEN_MAX %ld", sysconf(_SC_OPEN_MAX))

	char cwd_p[PATH_MAX];
	SMPT_DBmN2L("getcwd %d", getcwd(cwd_p, sizeof(cwd_p)))
	SMPT_DBmN2L("cwd_p %s", cwd_p)
}

void smpt_dbMwrite(const char *format_p, ...)
{
	mtx_lock(Pmtx_t);

	char lc_p[1024];
	va_list lva_list;
	va_start(lva_list, format_p);
	int l0 = vsnprintf(lc_p, sizeof(lc_p), format_p, lva_list);
	va_end(lva_list);

	fwrite(lc_p, 1, l0, Pfile);
	fwrite("\n", 1, 1, Pfile);

	//force write
	fflush(Pfile);
	mtx_unlock(Pmtx_t);
}

void smpt_dbMfree()
{
	mtx_destroy(Pmtx_t);
	fclose(Pfile);
}
