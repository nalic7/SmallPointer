LCC_U *lcc_u_p;
NALI_LB_UT lcc_u_bl = 0;

LCC_M *lcc_m_p;
NALI_LB_MIT lcc_m_bl = 0;

void lcc_set()
{
	lcc_u_p = malloc(0);
	lcc_m_p = malloc(0);
}

void lcc_free()
{
	free(lcc_u_p);
	free(lcc_m_p);
}