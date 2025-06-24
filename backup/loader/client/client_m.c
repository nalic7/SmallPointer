// NALI_LB_MIT lcm_bl = 0;
// NALI_LB_MT *lcm_p;
// NALI_LB_CT *lcm_c_p;
// float *lcm_rt_p;

NALI_LB_MIT lcm_i_hi_bl = 0;
NALI_LB_CHT *lcm_i_hi_p;
NALI_LB_MIT *lcm_i_hbl_p;
NALI_LB_MIT **lcm_i_h_p;

void lcm_set()
{
	// lcm_p = malloc(0);
	// lcm_c_p = malloc(0);
	// lcm_rt_p = malloc(0);

	lcm_i_hi_p = malloc(0);
	lcm_i_h_p = malloc(0);
	lcm_i_hbl_p = malloc(0);
}

void lcm_re()
{
	// lcm_bl = 0;
	// lcm_p = realloc(lcm_p, 0);
	// lcm_c_p = realloc(lcm_c_p, 0);
	// lcm_rt_p = realloc(lcm_rt_p, 0);

	lcm_i_hi_bl = 0;
	lcm_i_hi_p = realloc(lcm_i_hi_p, 0);
	lcm_i_h_p = realloc(lcm_i_h_p, 0);
	lcm_i_hbl_p = realloc(lcm_i_hbl_p, 0);
}

void lcm_free()
{
	// lcm_bl = 0;
	// free(lcm_p);
	// free(lcm_c_p);
	// free(lcm_rt_p);

	lcm_i_hi_bl = 0;
	free(lcm_i_hi_p);
	free(lcm_i_h_p);
	free(lcm_i_hbl_p);
}