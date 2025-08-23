#ifndef RC_H
#define RC_H

//.c max fps/refresh rate
#define NALI_LC_MAX_F 144.0F
#define NALI_LC_D 1/NALI_LC_MAX_F

extern NALI_LB_PT lc_net_bl;
extern uint8_t lc_net_p[NALI_LB_NET_BL];

// extern float lc_delta;

void lc_set();
void lc_vk();
void lc_read();
void lc_freeloop();
void lc_freeVk(uint32_t device);
void lc_free();

#endif
