#ifndef NALI_NETWORK_LINUX_SERVER_U_H
#define NALI_NETWORK_LINUX_SERVER_U_H

#define NALI_LSU_EPSILON 45.0F

void lsu_update();
void lsu_send(NALI_LB_UT u);
void lsu_read(NALI_LB_UT u);
void lsu_open();
void lsu_save();

#endif