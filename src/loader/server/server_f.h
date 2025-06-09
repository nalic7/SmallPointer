#ifndef NALI_NETWORK_LINUX_SERVER_F_H
#define NALI_NETWORK_LINUX_SERVER_F_H

#define NALI_NLS_DATA_FP_SIZE 1
extern void (*nlsf_data_fp[NALI_NLS_DATA_FP_SIZE])(NALI_LB_UT ui, uint8_t *);

void lsf_new_user(NALI_LB_UT ui);
void lsf_key_user(NALI_LB_UT ui, uint8_t *data_p);

#endif