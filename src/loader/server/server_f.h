#ifndef NALI_NETWORK_LINUX_SERVER_F_H
#define NALI_NETWORK_LINUX_SERVER_F_H

#define NALI_LSF_DATA_FP_BL 1
extern void (*nlsf_data_fp[NALI_LSF_DATA_FP_BL])(NALI_LB_UT ui, uint8_t *);

void lsf_add_u(NALI_LB_UT u);
void lsf_rm_u(NALI_LB_UT ui);

void lsf_key_user(NALI_LB_UT ui, uint8_t *data_p);

#endif