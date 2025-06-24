#ifndef NALI_NETWORK_LINUX_CLIENT_N_H
#define NALI_NETWORK_LINUX_CLIENT_N_H

#define NALI_LCF_DATA_FP_BL 6
extern void (*nlcf_data_fp[NALI_LCF_DATA_FP_BL])(uint8_t *);

void lcf_add_u_c(uint8_t *data_p);
void lcf_sync_all_u_c2new_u(uint8_t *data_p);
void lcf_rm_u_c(uint8_t *data_p);
void lcf_add_m_c(uint8_t *data_p);
void lcf_sync_all_m_c2new_u(uint8_t *data_p);
void lcf_rm_m_c(uint8_t *data_p);

#endif