#ifndef NALI_NETWORK_LINUX_SERVER_H
#define NALI_NETWORK_LINUX_SERVER_H

//max get
#define NALI_NLS_MAX_EPOLL_EVENT 1
//max connect
#define NALI_NLS_MAX_CLIENT 1

#define NALI_NLS_TIMEOUT &(struct timeval){.tv_sec = 5, .tv_usec = 0}

#define NALI_NLS_INIT 1
#define NALI_NLS_FAIL 2
extern uint8_t nls_state;

void nls_set();

#endif