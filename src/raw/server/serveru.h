#ifndef RSU_H
#define RSU_H

#define NALI_LSU_EPSILON 45.0F

void lsu_update();
void lsu_send(NALI_LB_UT u);
void lsu_read(NALI_LB_UT u);
void lsu_open();
void lsu_save();

#endif
