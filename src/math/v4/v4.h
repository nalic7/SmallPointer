#ifndef NALI_MATH_V4_H
#define NALI_MATH_V4_H

#define M_V4_qi(p, n) \
	p[n] = -p[n]; \
	p[n + 1] = -p[n + 1]; \
	p[n + 2] = -p[n + 2];

void m_v4_q(float x, float y, float z, float w[4]);
void m_v4_q2m(const float q[4], float w[16]);
void m_v4_m(const float a[4], const float b[4], float w[4]);
void m_v4_m4(const float a[16], const float b[4], float w[4]);

#endif