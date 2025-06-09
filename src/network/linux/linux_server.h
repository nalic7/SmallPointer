#ifndef NALI_NETWORK_LINUX_SERVER_H
#define NALI_NETWORK_LINUX_SERVER_H

//max get
#define NALI_NLS_MAX_EPOLL_EVENT 1

#define NALI_NLS_TIMEOUT &(struct timeval){.tv_sec = 5, .tv_usec = 0}

#define NALI_NLS_INIT 1
#define NALI_NLS_FAIL 2
extern uint8_t nls_state;

extern NALI_LB_UT nls_u_bl;
extern NALI_LB_UT *nls_u_p;
//NALI_LB_MAX_CLIENT * (3+3)
extern float *nls_u_rt_p;
//NALI_LB_MAX_CLIENT * 3
extern NALI_LB_CT *nls_u_c_p;

void nls_set();
void nls_send(NALI_LB_UT u, uint8_t *data_p, uint16_t data_bl);

#endif