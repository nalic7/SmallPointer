#ifndef _RS_H
#define _RS_H

//.c tps/read write time
#define _RS_MAX_RW 20

extern FILE *ls_file_p;

extern _RB_PT ls_net_bl;
extern uint8_t ls_net_p[_RB_NET_BL];

void ls_set();
void ls_read(_RB_UT u);
void ls_open();
void ls_save();
#ifdef _CM_CLIENT
	int ls_loop(void *p);
#else
	void ls_loop();
#endif
void ls_free();

#endif
