#ifndef NALI_VK_CMD_DRAW_H
#define NALI_VK_CMD_DRAW_H

extern void (**vk_cmd_d_fp)();
extern uint16_t vk_cmd_d_fp_bl;

// extern mtx_t *m_mtx_t_draw_p;

void vk_cmd_draw_set();
int vk_cmd_draw_loop(void *arg);

#endif