#ifndef NALI_NETWORK_LINUX_SERVER_C_H
#define NALI_NETWORK_LINUX_SERVER_C_H

#define NALI_LSC_CHT uint16_t
extern NALI_LB_UT lsc_uhi_bl;
extern NALI_LSC_CHT *lsc_uhi_p;

extern NALI_LB_UT *lsc_uhbl_p;
extern NALI_LB_UT **lsc_uh_p;

extern NALI_LB_MIT lsc_mihi_bl;
extern NALI_LSC_CHT *lsc_mihi_p;

extern NALI_LB_MIT *lsc_mihbl_p;
extern NALI_LB_MIT **lsc_mih_p;

NALI_LSC_CHT lsc_new_c_h(NALI_LB_CT x, NALI_LB_CT y, NALI_LB_CT z);

void lsc_set();
void lsc_sync_all_m2new_u(NALI_LB_UT ui);
void lsc_add_m2u(NALI_LSC_CHT mih);
void lsc_free();

#endif