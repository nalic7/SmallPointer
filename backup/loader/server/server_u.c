LSU *lsu_p;

NALI_LB_UT *lsu_h1_p;

NALI_LB_UT lsu_h1_bl = 0;

void lsu_set()
{
	lsu_p = malloc(0);

	lsu_h1_p = malloc(0);
}

void lsu_re()
{
	lsu_p = realloc(lsu_p, 0);

	lsu_h1_p = realloc(lsu_h1_p, 0);

	lsu_h1_bl = 0;
}

void lsu_free()
{
	free(lsu_p);

	free(lsu_h1_p);

	lsu_h1_bl = 0;
}