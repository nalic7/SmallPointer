#ifndef NALI_NETWORK_LINUX_CLIENT_F_H
#define NALI_NETWORK_LINUX_CLIENT_F_H

#define NALI_LCF_DATA_FP_BL 4
extern void (*nlcf_data_fp[NALI_LCF_DATA_FP_BL])(uint8_t *);

void lcf_add_u(uint8_t *data_p);
void lcf_sync_u(uint8_t *data_p);
void lcf_add_m(uint8_t *data_p);
void lcf_rm_m(uint8_t *data_p);

#endif