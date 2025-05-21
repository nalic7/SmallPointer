void *lb_cache_p;

void lb_init()
{
	lb_cache_p = malloc(NALI_CACHE_P_BL);
	NALI_CACHE_P_D_BL_P = malloc(sizeof(uint32_t) * 2);
	NALI_CACHE_P_D_BL_P[1] = 0;
	NALI_CACHE_P_D_P = f_read(NALI_HOME "asset.bin", NALI_CACHE_P_D_BL_P);
}

void lb_free()
{
	free(NALI_CACHE_P_D_BL_P);
	free(NALI_CACHE_P_D_P);
	free(lb_cache_p);
}