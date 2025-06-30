#ifndef NALI_NETWORK_LINUX_CLIENT_M_H
#define NALI_NETWORK_LINUX_CLIENT_M_H

extern LB_M **lcm_lb_m_p;
extern float ***lcm__rt_p;
extern NALI_LB_MIT *lcm_bl_p;

void lcm_set();
void lcm_update();
void lcm_read();
void lcm_re();
void lcm_free();

#endif