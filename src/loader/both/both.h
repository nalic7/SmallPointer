#ifndef NALI_LOADER_BOTH_H
#define NALI_LOADER_BOTH_H

//max connect
#define NALI_LB_MAX_CLIENT 1

//max connect type
#define NALI_LB_UT uint8_t
//void user
#define NALI_LB_UN 255

//package
#define NALI_LB_PT uint8_t
#define NALI_LB_MAX_TICK 20
#define NALI_LB_NET_BL 255

//model slot
#define NALI_LB_MST uint8_t

//model animation
#define NALI_LB_MAT uint8_t
//model animation line
#define NALI_LB_MALT uint8_t

//model
#define NALI_LB_MT uint8_t
//model index
#define NALI_LB_MIT uint16_t
#define NALI_LB_M8BL 256/8
//file/chunk
#define NALI_LB_CT uint8_t
#define NALI_LB_CIBL 16
//xyz
#define NALI_LB_CFBL 1024.0F

//s0-data
//stage 1-2 data shader
//joint first ...
// 1 2 star0 land0

#define NALI_LB_N_MAX 1
extern uint8_t lb_ms_p[NALI_LB_N_MAX];
extern uint8_t lb_ms_a_p[NALI_LB_N_MAX];
extern uint8_t *lb_ms_ap_p[NALI_LB_N_MAX];
extern uint8_t lb_ms_abl_p[NALI_LB_N_MAX];
extern VkDeviceSize lb_ms_vkdevicesize_p[NALI_LB_N_MAX];
//e0-data

//s0-net
//s1-client
#define NALI_LB_C_DATA_FP_T uint8_t

#define NALI_LB_C_ADD_U 0
#define NALI_LB_C_SYNC_ALL_U2NEW_U 1
#define NALI_LB_C_ADD_M 2
#define NALI_LB_C_RM_M 3
#define NALI_LB_C_SYNC_ALL_M_C 4
//e1-client

//s1-server
#define NALI_LB_S_DATA_FP_T uint8_t

#define NALI_LB_S_KEY_U 0

//s2-key
#define NALI_LB_S_KEY_W 1
#define NALI_LB_S_KEY_A 1 << 1
#define NALI_LB_S_KEY_S 1 << 2
#define NALI_LB_S_KEY_D 1 << 3
#define NALI_LB_S_KEY_SPACE 1 << 4
#define NALI_LB_S_KEY_CTRL 1 << 5
#define NALI_LB_S_KEY_LEFT_CLICK 1 << 6
#define NALI_LB_S_KEY_LEFT 1 << 7
#define NALI_LB_S_KEY_RIGHT 1 << 8
#define NALI_LB_S_KEY_UP 1 << 9
#define NALI_LB_S_KEY_DOWN 1 << 10
#define NALI_LB_S_KEY_RIGHT_CLICK 1 << 11
//e2-key
//e1-server
//e0-net


#define NALI_LB_CACHE_P_BL sizeof(void *) * 4
//client
#define NALI_LB_CACHE_P_BS_P (((uint8_t ***)lb_cache_p)[0])
#define NALI_LB_CACHE_P_BE_P (((uint8_t ***)lb_cache_p)[1])

//both
#define NALI_LB_CACHE_P_D_P (((uint8_t **)lb_cache_p)[2])
#define NALI_LB_CACHE_P_D_BL_P (((uint32_t **)lb_cache_p)[3])

extern mtx_t *lb_mtx_t_p;

extern void *lb_cache_p;

void lb_set();
void lb_loop();
void lb_free0();
void lb_free1();

#endif