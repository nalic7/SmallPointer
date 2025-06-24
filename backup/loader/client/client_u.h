#ifndef NALI_NETWORK_LINUX_CLIENT_U_H
#define NALI_NETWORK_LINUX_CLIENT_U_H

// extern NALI_LB_UT lcu_bl;
// extern NALI_LB_UT *lcu_p;
// extern float *lcu_rt_p;
// extern NALI_LB_CT *lcu_c_p;

extern NALI_LB_UT lcu_hi_bl;
extern NALI_LB_CHT *lcu_hi_p;
extern NALI_LB_UT *lcu_hbl_p;
extern NALI_LB_UT **lcu_h_p;

void lcu_set();
void lcu_re();
void lcu_free();

#endif