#ifndef _RSU_H
#define _RSU_H

#define NALI_LSU_EPSILON 45.0F

void lsu_update();
void lsu_send(_RB_UT u);
void lsu_read(_RB_UT u);
void lsu_open();
void lsu_save();

#endif
