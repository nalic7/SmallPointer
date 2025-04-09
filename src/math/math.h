#ifndef NALI_MATH_H
#define NALI_MATH_H

#define MATH_D2R(v) ((v) * M_PI / 180.0)
#define MATH_R2D(v) ((v) * 180.0 / M_PI)

#define MATH_4E2S(dst, data, offset) dst = ((data)[offset] << 24) | ((data)[offset + 1] << 16) | ((data)[offset + 2] << 8) | (data)[offset + 3];

#define MATH_LENGTH(number) ((number) == 0 ? 1 : log10(number) + 1)
#define MATH_MIPMAP(width, height) (uint32_t)(log2(((width) > (height)) ? (width) : (height))) + 1

#endif