#ifndef NALI_NETWORK_LINUX_SERVER_M_H
#define NALI_NETWORK_LINUX_SERVER_M_H

extern NALI_LB_MIT lsm_i_p[NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL];
extern LB_M **lsm_lb_m_p;
extern NALI_LB_MIT *lsm_bl_p;
extern NALI_LB_MIT lsm_bl;

void lsm_set();
void lsm_ad_m(NALI_LB_CHT ch, NALI_LB_MT m, float *rt_p);
void lsm_update_m();
void lsm_send_m_c2u_c(NALI_LB_PT ls_net_bl);
void lsm_free();

#endif