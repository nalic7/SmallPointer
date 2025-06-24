#ifndef NALI_MATH_H
#define NALI_MATH_H

#define M_MIN(a, b) ((a) < (b) ? (a) : (b))
#define M_MAX(a, b) ((a) > (b) ? (a) : (b))

#define M_D2R(v) ((v) * M_PI / 180.0)
#define M_R2D(v) ((v) * 180.0 / M_PI)

#define M_4E2S(dst, data, offset) dst = ((data)[offset] << 24) | ((data)[offset + 1] << 16) | ((data)[offset + 2] << 8) | (data)[offset + 3];

#define M_LENGTH(number) ((number) == 0 ? 1 : log10(number) + 1)
#define M_MIPMAP(width, height) (uint32_t)(log2(((width) > (height)) ? (width) : (height))) + 1

#define M_LERP(a, b, t) (a) + ((b) - (a)) * (t)

//((yaw + 180) % 360 + 360) % 360 - 180
#define M_NORMALIZE(v, f) fmodf(fmodf((v) + (f) / 2, (f)) + (f), (f)) - (f) / 2

#define M_H3(x, y, z, m) x * m * m + y * m + z
#define M_H3X(hi, m) hi / (m * m)
#define M_H3Y(hi, m) (hi / m) % m
#define M_H3Z(hi, m) hi % m

#define M_IP(a, b, c, d) a << 24 | b << 16 | c << 8 | d

#endif