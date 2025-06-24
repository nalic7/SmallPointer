#ifndef NALI_NETWORK_LINUX_CLIENT_C_H
#define NALI_NETWORK_LINUX_CLIENT_C_H

typedef struct
{
	NALI_LB_UT u;
	float rt[6];
} LCC_U;
extern LCC_U *lcc_u_p;
extern NALI_LB_UT lcc_u_bl;

typedef struct
{
	NALI_LB_MT m;
	float rt[6];
} LCC_M;
extern LCC_M *lcc_m_p;
extern NALI_LB_MIT lcc_m_bl;

void lcc_set();
void lcc_free();

#endif