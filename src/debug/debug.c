static mtx_t *mtx_t_p = &(mtx_t){};
static FILE *file_p;

void smpt_db_set()
{
	int l0 = mtx_init(mtx_t_p, mtx_plain);
	int l1 = mkdir(NALI_F_SAVE, S_IRUSR | S_IWUSR | S_IXUSR);
	int l2 = remove(NALI_F_SAVE_LOG);
	file_p = fopen(NALI_F_SAVE_LOG, "ab");

	SMPT_DB_N2L("mtx_init %d", l0)
	SMPT_DB_N2L("mkdir %d", l1)
	SMPT_DB_N2L("remove %d", l2)
	SMPT_DB_N2L("fopen %p", file_p)

	SMPT_DB_N2L("_SC_OPEN_MAX %ld", sysconf(_SC_OPEN_MAX))

	char cwd_p[PATH_MAX];
	SMPT_DB_N2L("getcwd %d", getcwd(cwd_p, sizeof(cwd_p)))
	SMPT_DB_N2L("cwd_p %s", cwd_p)
}

void smpt_db_write(const char *format_p, ...)
{
	mtx_lock(mtx_t_p);

	char lc_p[1024];
	va_list lva_list;
	va_start(lva_list, format_p);
	int l0 = vsnprintf(lc_p, sizeof(lc_p), format_p, lva_list);
	va_end(lva_list);

	fwrite(lc_p, 1, l0, file_p);
	fwrite("\n", 1, 1, file_p);

	//force write
	fflush(file_p);
	mtx_unlock(mtx_t_p);
}

void smpt_db_free()
{
	mtx_destroy(mtx_t_p);
	fclose(file_p);
}
