#ifndef NALI_NETWORK_LINUX_SERVER_H
#define NALI_NETWORK_LINUX_SERVER_H

extern const uint32_t ns_u_p[SMPTRB_UM];
typedef struct
{
	struct sockaddr_in client_sockaddr_in;
	socklen_t client_sockaddr_in_bl;

	float _rt_p[3 + 2];
	SMPTRB_CT c_p[3];
	//SMPTRB_CHT *ch_p;
	SMPTRB_CHT ch_p[4];
	uint8_t ch_bl;
	LB_U lb_u;
} NS;
extern NS ns_p[SMPTRB_UM];

void ns_set();
void ns_send(SMPTRB_UT ui);
void ns_get();
void ns_check();
void ns_free();

#endif
