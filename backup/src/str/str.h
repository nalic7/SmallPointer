#ifndef NALI_MATH_STR_H
#define NALI_MATH_STR_H

void m_str_p(char **data_p, const char *e_p[], uint8_t bl);
void m_str_c2c(char **data_p, char **c_p, uint32_t *bl_p, const char *s_p, const char *e_p);
void m_str_c2f(char **data_p, float **w_p, uint32_t *bl_p, const char *s_p, const char *e_p);
void m_str_c2i(char **data_p, int32_t **w_p, uint32_t *bl_p, const char *s_p, const char *e_p);

#endif