#ifndef _RSM_H
#define _RSM_H

// extern void (*lsm_fp[_RB_N_MAX])(_RB_MIT mi);

extern _RB_MIT *lsm_c_mi_p[_RB_CIBL * _RB_CIBL * _RB_CIBL];
extern LB_M *lsm_c_lb_m_p[_RB_CIBL * _RB_CIBL * _RB_CIBL];
extern _RB_MIT lsm_c_bl_p[_RB_CIBL * _RB_CIBL * _RB_CIBL];

extern _RB_CHT *lsm_m_ch_p;
extern _RB_MIT *lsm_m_i_p;
extern _RB_MIT lsm_m_bl;

extern _RB_MIT *lsm_f_mi_p;
extern _RB_MIT lsm_f_mi_bl;

void lsm_ad_m(_RB_CHT ch/* , _RB_MST ms */);
void lsm_rm_m(_RB_MIT mi);
void lsm_update();
void lsm_send(_RB_UT u);
void lsm_open();
void lsm_save();
void lsm_free();

#endif
