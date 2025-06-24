// NALI_LB_UT lcu_bl = 0;
// NALI_LB_UT *lcu_p;
// float *lcu_rt_p;
// NALI_LB_CT *lcu_c_p;

NALI_LB_UT lcu_hi_bl = 0;
NALI_LB_CHT *lcu_hi_p;
NALI_LB_UT *lcu_hbl_p;
NALI_LB_UT **lcu_h_p;

void lcu_set()
{
	// lcu_p = malloc(0);
	// lcu_rt_p = malloc(0);
	// lcu_c_p = malloc(0);

	lcu_hi_p = malloc(0);
	lcu_h_p = malloc(0);
	lcu_hbl_p = malloc(0);
}

void lcu_re()
{
	// lcu_bl = 0;
	// lcu_p = realloc(lcu_p, 0);
	// lcu_rt_p = realloc(lcu_rt_p, 0);
	// lcu_c_p = realloc(lcu_c_p, 0);

	lcu_hi_bl = 0;
	lcu_hi_p = realloc(lcu_hi_p, 0);
	lcu_h_p = realloc(lcu_h_p, 0);
	lcu_hbl_p = realloc(lcu_hbl_p, 0);
}

void lcu_free()
{
	// lcu_bl = 0;
	// free(lcu_p);
	// free(lcu_rt_p);
	// free(lcu_c_p);

	lcu_hi_bl = 0;
	free(lcu_hi_p);
	free(lcu_h_p);
	free(lcu_hbl_p);
}