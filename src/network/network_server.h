#ifndef NALI_NETWORK_LINUX_SERVER_H
#define NALI_NETWORK_LINUX_SERVER_H

//user ip
extern const uint32_t ns_u_p[NALI_LB_UM];
typedef struct
{
	struct sockaddr_in client_sockaddr_in;
	socklen_t client_sockaddr_in_bl;

	float _rt_p[3 + 2];
	NALI_LB_CT c_p[3];
	NALI_LB_CHT *ch_p;
	uint8_t ch_bl;
	LB_U lb_u;
} NS;
extern NS ns_p[NALI_LB_UM];

void ns_set();
void ns_send(NALI_LB_UT ui);
void ns_get();
void ns_check();
void ns_free();

#endif