#ifndef NALI_LOADER_SERVER_H
#define NALI_LOADER_SERVER_H

//u will sync to other u
//-u can has move than 1 c- -> u_rt to find c used
//use struct?
//s0-file
//cache_address u
//index to (struct *)
//u_s
//u_c
//u_rt

//cache_address c
//index to (void *)
//u_max
//*u_h1 / ui
//index to (void *)
//m_max
//*m_h1 / ui
//*m
//*m_rt

//u
//m+a
//i

//ui
//mi+ai
//ii

//uh
//mh
//ih

//im
//mm+am
//um

//save_state
//e0-file

#define NALI_LS_STEP_UH 0

#define NALI_LS_BACK_SS sizeof(uint8_t)
#define NALI_LS_BACK_UM sizeof(NALI_LB_UT)
#define NALI_LS_BACK_MM sizeof(NALI_LB_MT)

#define NALI_LS_SS_DONE 1
extern FILE *ls_file_p;
extern uint32_t ls_file_step;

extern NALI_LB_PT ls_net_bl;
extern uint8_t ls_net_p[NALI_LB_NET_BL];

void ls_set();
void ls_read(NALI_LB_UT ui);
void ls_save();
int ls_loop(void *p);
void ls_free();

#endif