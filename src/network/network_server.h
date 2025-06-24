#ifndef NALI_NETWORK_LINUX_SERVER_H
#define NALI_NETWORK_LINUX_SERVER_H

//user ip
extern const uint32_t ns_u_p[NALI_LB_UM];
typedef struct
{
	struct sockaddr_in client_sockaddr_in;
	socklen_t client_sockaddr_in_bl;

	//u
	NALI_LB_CHT ch;
	float rt[6];
} NS;
extern NS ns_p[NALI_LB_UM];

void ns_set();
void ns_send(NALI_LB_UT ui);
void ns_get();
void ns_check();
void ns_free();

#endif