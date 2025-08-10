#ifndef NALI_LOADER_SERVER_M_H
#define NALI_LOADER_SERVER_M_H

// extern void (*lsm_fp[NALI_LB_N_MAX])(NALI_LB_MIT mi);

extern NALI_LB_MIT *lsm_c_mi_p[NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL];
extern LB_M *lsm_c_lb_m_p[NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL];
extern NALI_LB_MIT lsm_c_bl_p[NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL];

extern NALI_LB_CHT *lsm_m_ch_p;
extern NALI_LB_MIT *lsm_m_i_p;
extern NALI_LB_MIT lsm_m_bl;

extern NALI_LB_MIT *lsm_f_mi_p;
extern NALI_LB_MIT lsm_f_mi_bl;

void lsm_ad_m(NALI_LB_CHT ch/* , NALI_LB_MST ms */);
void lsm_rm_m(NALI_LB_MIT mi);
void lsm_update();
void lsm_send(NALI_LB_UT u);
void lsm_open();
void lsm_save();
void lsm_free();

#endif
