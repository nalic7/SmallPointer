#ifndef NALI_MATH_V4_H
#define NALI_MATH_V4_H

#define V4_qi(p, n) \
	p[n] = -p[n]; \
	p[n + 1] = -p[n + 1]; \
	p[n + 2] = -p[n + 2];

void v4_q(float x, float y, float z, float *w_qv4_float_p);
void v4_qm(float *r_qv4_float_p, float *m4x4_float_p);
void v4_m(float *a, float *b, float *w);

#endif