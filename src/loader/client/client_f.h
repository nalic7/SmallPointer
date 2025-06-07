#ifndef NALI_NETWORK_LINUX_CLIENT_F_H
#define NALI_NETWORK_LINUX_CLIENT_F_H

#define NALI_NLC_DATA_FP_SIZE 3
extern void (*nlcf_data_fp[NALI_NLC_DATA_FP_SIZE])(uint8_t *);

void nlcf_read_data(uint8_t *data_p);
void nlcf_sync_player(uint8_t *data_p);
void nlcf_add_model(uint8_t *data_p);
void nlcf_rm_model(uint8_t *data_p);

#endif