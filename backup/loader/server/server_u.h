#ifndef NALI_NETWORK_LINUX_SERVER_U_H
#define NALI_NETWORK_LINUX_SERVER_U_H

typedef struct
{
	uint8_t s;
	NALI_LB_CHT c;
	float rt[6];
} LSU;

#define NALI_LSU_S_CONNECT 1
extern LSU *lsu_p;

extern NALI_LB_UT *lsu_h1_p;

extern NALI_LB_UT lsu_h1_bl;

void lsu_set();
void lsu_re();
void lsu_free();

#endif