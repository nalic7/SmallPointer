#ifndef NALI_NETWORK_LINUX_CLIENT_H
#define NALI_NETWORK_LINUX_CLIENT_H

#define NALI_NC_IP NALI_M_IP(127, 0, 0, 1)

void nc_set();
void nc_send();
void nc_get();
void nc_check();
void nc_free();

#endif