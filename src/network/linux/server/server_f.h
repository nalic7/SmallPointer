#ifndef NALI_NETWORK_LINUX_SERVER_F_H
#define NALI_NETWORK_LINUX_SERVER_F_H

#define NALI_NLS_DATA_FP_SIZE 3
extern void (*nlsf_data_fp[NALI_NLS_DATA_FP_SIZE])(uint8_t *);

void nlsf_read_data(uint8_t *data_p);
void nlsf_new_player(uint8_t *data_p);

#endif