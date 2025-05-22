#ifndef NALI_VIEW_H
#define NALI_VIEW_H

extern uint8_t
	**v_a_p,
	v_a_bl;

extern VkDeviceSize v_a_vkdevicesize_array[1];

extern uint32_t *v_i_p;

void v_set();
void v_loop();
void v_free();

#endif