#ifndef SMPT_NW_UDPhSV
	#define SMPT_NW_UDPhSV

struct NS
{
	struct sockaddr_in client_sockaddr_in;
	socklen_t client_sockaddr_in_bl;

//	float _rt_p[3 + 2];
//	SMPTRB_CT c_p[3];
//	//SMPTRB_CHT *ch_p;
//	SMPTRB_CHT ch_p[4];
//	uint8_t ch_bl;
//	LB_U lb_u;
};
	extern struct NS ns_p[SMPT_NWuU];

	void ns_set();
	void ns_send(SMPT_NWtU u);
	void ns_get();
	void ns_free();
#endif
