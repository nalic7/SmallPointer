#ifdef NALI_D_FILE
mtx_t *d_mtx_t_p = &(mtx_t){};

static FILE *file_p;

void d_set()
{
	int l_i0 = mtx_init(lc_mtx_t_p, mtx_plain);
	int l_i1 = mkdir(NALI_F_SAVE, S_IRUSR | S_IWUSR | S_IXUSR);
	int l_i2 = remove(NALI_F_SAVE_LOG);
	file_p = fopen(NALI_F_SAVE_LOG, "ab");

	NALI_D_LOG("_SC_OPEN_MAX %ld", sysconf(_SC_OPEN_MAX))

	NALI_D_LOG("mtx_init %d", l_i0)
	NALI_D_LOG("mkdir %d", l_i1)
	NALI_D_LOG("remove %d", l_i2)
	NALI_D_LOG("fopen %p", file_p)
}

void d_write(const char *format_p, ...)
{
	mtx_lock(d_mtx_t_p);
	char l_c_p[1024];
	va_list l_va_list;
	va_start(l_va_list, format_p);
	int l_0 = vsnprintf(l_c_p, sizeof(l_c_p), format_p, l_va_list);
	va_end(l_va_list);

	// if (l_0 > 0)
	// {
	fwrite(l_c_p, 1, l_0, file_p);
	fwrite("\n", 1, 1, file_p);
	// }
	mtx_unlock(d_mtx_t_p);
}

void d_free()
{
	mtx_destroy(d_mtx_t_p);
	fclose(file_p);
}

#endif