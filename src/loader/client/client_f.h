#ifndef NALI_NETWORK_LINUX_CLIENT_F_H
#define NALI_NETWORK_LINUX_CLIENT_F_H

#define NALI_NLC_DATA_FP_SIZE 3
extern void (*nlcf_data_fp[NALI_NLC_DATA_FP_SIZE])(uint8_t *);

void lcf_read_data(uint8_t *data_p);
void lcf_sync_user(uint8_t *data_p);
void lcf_add_model(uint8_t *data_p);
void lcf_rm_model(uint8_t *data_p);

#endif