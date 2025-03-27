#ifndef NALI_MATH_H
#define NALI_MATH_H

#define MATH_D2R(v) ((v) * M_PI / 180.0)
#define MATH_R2D(v) ((v) * 180.0 / M_PI)

// char *math_combine(const char *str1, const char *str2);
uint32_t math_length(uint32_t number);
uint32_t math_mipmap(uint32_t width, uint32_t height);
// char *math_get(uint32_t number);
// void math_set(uint32_t number, char *c_p);

#endif