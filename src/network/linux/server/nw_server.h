#ifndef NALI_NETWORK_SERVER_H
#define NALI_NETWORK_SERVER_H

#define NALI_MAX_EPOLL_EVENT 4
#define NALI_MAX_CLIENT 4

#define NALI_NET_SERVER_INIT 1
#define NALI_NET_SERVER_FAIL 2
extern uint8_t m_net_server_state;

void nws_init();

#endif