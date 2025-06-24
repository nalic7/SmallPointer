#ifndef NALI_NETWORK_LINUX_CLIENT_M_H
#define NALI_NETWORK_LINUX_CLIENT_M_H

// extern NALI_LB_MIT lcm_bl;
// extern NALI_LB_MT *lcm_p;
// extern NALI_LB_CT *lcm_c_p;
// extern float *lcm_rt_p;

extern NALI_LB_MIT lcm_i_hi_bl;
extern NALI_LB_CHT *lcm_i_hi_p;
extern NALI_LB_MIT *lcm_i_hbl_p;
extern NALI_LB_MIT **lcm_i_h_p;

//when player move to new c will re h

void lcm_set();
void lcm_re();
void lcm_free();

#endif