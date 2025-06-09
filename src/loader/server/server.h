#ifndef NALI_LOADER_SERVER_H
#define NALI_LOADER_SERVER_H

// extern mtx_t *ls_mtx_t_p;

extern NALI_LB_MIT ls_m_bl;
extern NALI_LB_MT *ls_m_p;
// extern NALI_LB_MIT *ls_m_i_p;
extern NALI_LB_CT *ls_m_c_p;
extern float *ls_m_rt_p;

// extern NALI_LB_MIT ls_r_m_bl;
// extern NALI_LB_MIT *ls_r_m_i_p;

extern NALI_LB_PT *ls_net_bl_p;
extern uint8_t *ls_net_p;

void ls_set();
int ls_loop(void *p);
void ls_free();

#endif