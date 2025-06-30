#ifndef NALI_NETWORK_LINUX_SERVER_M_H
#define NALI_NETWORK_LINUX_SERVER_M_H

extern NALI_LB_MIT lsm_i_p[NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL];
extern LB_M **lsm_lb_m_p;
extern NALI_LB_MIT *lsm_bl_p;
extern NALI_LB_MIT lsm_bl;

void lsm_ad_m(NALI_LB_CHT ch, NALI_LB_MT m);
void lsm_update();
void lsm_send(NALI_LB_UT u);
void lsm_open();
void lsm_save();
void lsm_free();

#endif