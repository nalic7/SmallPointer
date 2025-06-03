#ifndef NALI_LOADER_BOTH_H
#define NALI_LOADER_BOTH_H

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