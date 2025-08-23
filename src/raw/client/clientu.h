#ifndef RCU_H
#define RCU_H

extern NALI_LB_CHT *lcu_ch_p;
extern uint8_t lcu_ch_bl;
//[3 * 3 * 3][3]
extern uint8_t *lcu_xyz_p;

extern uint8_t lcu_rt_frame;
extern float lcu__rt_p[3 + 2];
extern float lcu_rt_p[3 + 2];
extern LB_U lcu_lb_u;

extern uint8_t lcu_k;
extern float lcu_xy_p[2];

void lcu_set();
void lcu_update();
void lcu_send();
void lcu_read();
void lcu_free();

#endif
