#ifndef NALI_LOADER_SERVER_H
#define NALI_LOADER_SERVER_H

extern float ls_u_rt_p[NALI_LB_MAX_CLIENT][3+3];
extern NALI_LB_CT ls_u_c_p[NALI_LB_MAX_CLIENT][3];

extern NALI_LB_MT ls_m_bl_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX];
extern NALI_LB_MT ls_m_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX][NALI_LB_M8BL];
extern float *ls_m_rt_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX];

extern NALI_LB_MT ls_re_m_bl_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX];
extern NALI_LB_MT *ls_re_m_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX];

#define NALI_LS_MAX_TICK 20
#define NALI_LS_NET_BL 1024
extern uint16_t ls_net_bl_p[NALI_LB_MAX_CLIENT];
extern uint8_t ls_net_p[NALI_LB_MAX_CLIENT][sizeof(uint16_t) + sizeof(float) * (3 + 3) + sizeof(NALI_LB_CT) * 3 + NALI_LS_NET_BL];

void ls_set();
int ls_loop(void *p);
void ls_free();

#endif