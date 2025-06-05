#ifndef NALI_LOADER_SERVER_H
#define NALI_LOADER_SERVER_H

extern float ls_p_rt_p[NALI_NLS_MAX_CLIENT][3+3];
extern NALI_LB_CT ls_p_c_p[NALI_NLS_MAX_CLIENT][3];

extern NALI_LB_MT ls_m_bl_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX];
extern NALI_LB_MT ls_m_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX][NALI_LB_M8BL];
extern float *ls_m_rt_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX];

extern NALI_LB_MT ls_re_m_bl_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX];
extern NALI_LB_MT *ls_re_m_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX];

void ls_set();
void ls_loop();
void ls_free();

#endif