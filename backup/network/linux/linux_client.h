#ifndef NALI_NETWORK_LINUX_CLIENT_H
#define NALI_NETWORK_LINUX_CLIENT_H

#define NALI_NLC_TIMEOUT &(struct timeval){.tv_sec = 5, .tv_usec = 0}

#define NALI_NC_IP "127.0.0.1"
#define NALI_NLC_ID 0

#define NALI_NC_INIT 1
#define NALI_NC_FAIL 2
extern uint8_t nlc_state;

void nlc_set();
void nlc_send();

#endif