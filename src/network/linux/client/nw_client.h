#ifndef NALI_NETWORK_CLIENT_H
#define NALI_NETWORK_CLIENT_H

#define NALI_IP "127.0.0.1"

#define NALI_NET_CLIENT_INIT 1
#define NALI_NET_CLIENT_FAIL 2
extern uint8_t m_net_client_state;

extern int m_client_socket;

void nwc_init();

#endif