#ifndef NALI_LOADER_CLIENT_U_H
#define NALI_LOADER_CLIENT_U_H

extern NALI_LB_CHT *lcu_ch_p;
extern uint8_t lcu_ch_bl;

extern uint8_t lcu_rt_frame;
extern float lcu__rt_p[3 + 2];
extern float lcu_rt_p[3 + 2];
extern LB_U lcu_lb_u;

extern uint8_t lcu_k;
extern float lcu_xy_p[2];

void lcu_update();
void lcu_send();
void lcu_read();

#endif