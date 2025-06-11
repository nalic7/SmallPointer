#ifndef NALI_LOADER_SERVER_H
#define NALI_LOADER_SERVER_H

extern mtx_t *ls_mtx_t_p;

extern NALI_LB_UT ls_u_bl;
extern NALI_LB_UT *ls_u_p;
extern float *ls_urt_p;
extern NALI_LB_CT *ls_uc_p;

extern NALI_LB_MIT ls_m_bl;
extern NALI_LB_MT *ls_m_p;
extern NALI_LB_CT *ls_mc_p;
extern float *ls_mrt_p;

extern NALI_LB_PT ls_net_bl;
extern uint8_t ls_net_p[NALI_LB_NET_BL];

void ls_set();
void ls_re();
int ls_loop(void *p);
void ls_free();

#endif