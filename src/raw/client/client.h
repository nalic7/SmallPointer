#ifndef _RC_H
#define _RC_H

//.c max fps/refresh rate
#define _RC_MAX_F 144.0F
#define _RC_D 1/_RC_MAX_F

extern _RB_PT lc_net_bl;
extern uint8_t lc_net_p[_RB_NET_BL];

// extern float lc_delta;

void lc_set();
void lc_vk();
void lc_read();
void lc_freeloop();
void lc_freeVk(uint32_t device);
void lc_free();

#endif
