#ifndef NALI_NETWORK_LINUX_SERVER_H
#define NALI_NETWORK_LINUX_SERVER_H

extern const uint32_t ns_u_p[_RB_UM];
typedef struct
{
	struct sockaddr_in client_sockaddr_in;
	socklen_t client_sockaddr_in_bl;

	float _rt_p[3 + 2];
	_RB_CT c_p[3];
	//_RB_CHT *ch_p;
	_RB_CHT ch_p[4];
	uint8_t ch_bl;
	LB_U lb_u;
} NS;
extern NS ns_p[_RB_UM];

void ns_set();
void ns_send(_RB_UT ui);
void ns_get();
void ns_check();
void ns_free();

#endif
