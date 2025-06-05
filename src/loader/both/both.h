#ifndef NALI_LOADER_BOTH_H
#define NALI_LOADER_BOTH_H

//max connect type
#define NALI_LB_PT uint8_t

#define NALI_LB_MT uint8_t
#define NALI_LB_M8BL 256/8
//file/chunk
#define NALI_LB_CT uint8_t
#define NALI_LB_CIBL 16
//xyz
#define NALI_LB_CFBL 1024.0F

//s0-data
//stage 1 data
//stage 2 shader
//stage 3 view
#define NALI_VD_M_POMI0 0
// #define NALI_VD_M_POMI1 1
// #define NALI_VD_M_POMI2 2
#define NALI_VD_M_STAR0 1
#define NALI_VD_M_LAND0 2

#define NALI_VD_M_MAX 3
//e0-data


#define NALI_CACHE_P_BL sizeof(void *) * 4
//client
#define NALI_CACHE_P_BS_P (((uint8_t ***)lb_cache_p)[0])
#define NALI_CACHE_P_BE_P (((uint8_t ***)lb_cache_p)[1])

//both
#define NALI_CACHE_P_D_P (((uint8_t **)lb_cache_p)[2])
#define NALI_CACHE_P_D_BL_P (((uint32_t **)lb_cache_p)[3])

extern void *lb_cache_p;

void lb_set();
void lb_free();

#endif