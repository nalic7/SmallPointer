#ifndef NALI_LOADER_SERVER_H
#define NALI_LOADER_SERVER_H

//.c tps/read write time
#define NALI_LS_MAX_RW 20

extern FILE *ls_file_p;

extern NALI_LB_PT ls_net_bl;
extern uint8_t ls_net_p[NALI_LB_NET_BL];

void ls_set();
void ls_read(NALI_LB_UT u);
void ls_open();
void ls_save();
#ifdef C_NALI_CLIENT
	int ls_loop(void *p);
#else
	void ls_loop();
#endif
void ls_free();

#endif
