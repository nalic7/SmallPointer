#ifndef NALI_VIEW_H
#define NALI_VIEW_H

//c1j1
//c1j0
//t1j1u1v1
//t1j0u1v1
#define NALI_V_A_BL 2

extern uint8_t
	**v_a_p_array[NALI_V_A_BL],
	*v_a_bl1_p_array[NALI_V_A_BL];

extern uint16_t
	v_a_bl0_array[NALI_V_A_BL];
// uint16_t
// 	v_a_bl;

extern uint32_t *v_i_p;

extern VkDeviceSize 
	v_a_vkdevicesize_array[NALI_V_A_BL],
//jN
//default -> UBOB UBOA
	*v_b_vkdevicesize_p_array[NALI_V_A_BL];

extern float **v_s_p_array[NALI_V_A_BL];

void v_set();
void v_free();

#endif