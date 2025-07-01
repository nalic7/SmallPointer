#ifndef NALI_NETWORK_LINUX_CLIENT_M_H
#define NALI_NETWORK_LINUX_CLIENT_M_H

extern void (*lcm_fp[NALI_LB_N_MAX])();

extern LB_M **lcm_lb_m_p;
extern float lcm__rt_p[NALI_LB_MIM][3 + 2];
extern NALI_LB_MIT *lcm_bl_p;

extern NALI_LB_MIT lsm__update_p[NALI_LB_MIM];

void lcm_set();
void lcm_update();
void lcm_read();
void lcm_re();
void lcm_free();

#endif