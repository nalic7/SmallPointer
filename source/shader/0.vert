#version 420

#define NALI_LCP_BONE_BL 52

layout(location = 0) in vec3 a_v;
layout(location = 1) in uint a_c1j1;

layout(std140, set = 0, binding = 0) uniform UBOS
{
	mat4 v;
	mat4 p;
} ubos;

struct PB
{
	mat4 i_bindpose;
	mat4 bindpose;
};
layout(std140, set = 0, binding = 1) uniform UBOB
{
	PB pb[NALI_LCP_BONE_BL];
} ubob;

struct PA
{
	vec4 s;//w1-2_start w3-4_end
	vec4 r;
	vec4 t;//w1-4_b
};
layout(std140, set = 0, binding = 2) uniform UBOA
{
	PA pa[NALI_LCP_BONE_BL];
	// mat4 m;
} uboa;

//layout(std430, set = 0, binding = 2) readonly buffer SSBOAS
//{
//	//vec4
//	vec3 ssboas_s[NALI_LCP_BONE_BL];
//};

layout(location = 0) out uint f_c;
// #ifdef NALI_TEXTURE
// 	layout(location = 1) out uint f_t;
// #endif

mat4 s2mat4(vec3 s)
{
	return mat4
	(
		s.x, 0.0, 0.0, 0.0,
		0.0, s.y, 0.0, 0.0,
		0.0, 0.0, s.z, 0.0,
		0.0, 0.0, 0.0, 1.0
	);
}

mat4 r2mat4(vec4 q)
{
	float x = q.x;
	float y = q.y;
	float z = q.z;
	float w = q.w;

	float xx = x * x;
	float yy = y * y;
	float zz = z * z;
	float xy = x * y;
	float xz = x * z;
	float yz = y * z;
	float wx = w * x;
	float wy = w * y;
	float wz = w * z;

	return mat4
	(
		1.0 - 2.0 * (yy + zz),	2.0 * (xy - wz),	2.0 * (xz + wy),	0.0,

		2.0 * (xy + wz),	1.0 - 2.0 * (xx + zz),	2.0 * (yz - wx),	0.0,

		2.0 * (xz - wy),	2.0 * (yz + wx),	1.0 - 2.0 * (xx + yy),	0.0,

		0.0,			0.0,			0.0,			1.0
	);
}

mat4 t2mat4(vec3 t)
{
	return mat4
	(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		t.x, t.y, t.z, 1.0
	);
}

void main()
{
	vec4 l_v = vec4(a_v, 1);
	uint l_j = (a_c1j1 >> 8) & 0xFFu;

	//floatBitsToUint(ssbob_s[l_0 / 4].w)
	//l_v *= vec4(ssbob_s[l_j].xyz, 1);

	//if (((floatBitsToUint(ssbob_t[0].w) >> 8) & 0xFFu) == 1)
	//if ((floatBitsToUint(ssbob_t[0].w) & 0xFFu) == 0)
	//if (((floatBitsToUint(ssbob_t[1].w) >> 8) & 0xFFu) == 3)
	//if ((floatBitsToUint(ssbob_t[1].w) & 0xFFu) == 1)
	//if (((floatBitsToUint(ssbob_t[2].w) >> 8) & 0xFFu) == 6)
	//if ((floatBitsToUint(ssbob_t[2].w) & 0xFFu) == 3)
	//if (floatBitsToUint(ssbob_t[0].w) == 0)
	//if (ssbob_t[0].w == 0.0F)
//0 1 0 2 1 0
	//uint l_0_ = 5;
	//if (((floatBitsToUint(ssbob_s[l_0_ / 4].w) >> l_0_ % 4 * 8) & 0xFFu) == 0)
	//if (((floatBitsToUint(ssbob_s[0].w) >> (8+8+8)) & 0xFFu) == 1)
	//if (l_j < 22)
//	{
//		l_v *= 0;
//	}

	// for (uint l_0 = floatBitsToUint(ssbob_t[l_j].w) & 0xFFu; l_0 < ((floatBitsToUint(ssbob_t[l_j].w) >> 8) & 0xFFu); ++l_0)
	// //for (uint l_0 = ((floatBitsToUint(ssbob_t[l_j].w) >> 8) & 0xFFu) - 1; l_0 > (floatBitsToUint(ssbob_t[l_j].w) & 0xFFu) - 1; --l_0)
	// {
	// 	mat4 l_bp_mat4 = mat4(1);
	// 	for (uint l_1 = l_0; l_1 < ((floatBitsToUint(ssbob_t[l_j].w) >> 8) & 0xFFu); ++l_1)
	// 	//for (uint l_1 = ((floatBitsToUint(ssbob_t[l_j].w) >> 8) & 0xFFu); l_1 > l_0 - 1; --l_1)
	// 	{
	// 		uint l_1_0 = (floatBitsToUint(ssbob_s[l_1 / 4].w) >> l_1 % 4 * 8) & 0xFFu;
	// 		l_bp_mat4 *= s2mat4(ssbob_s[l_1_0].xyz);
	// 		l_bp_mat4 *= r2mat4(ssbob_r[l_1_0]);
	// 		l_bp_mat4 *= t2mat4(ssbob_t[l_1_0].xyz);
	// 	}
	// 	uint l_0_0 = (floatBitsToUint(ssbob_s[l_0 / 4].w) >> l_0 % 4 * 8) & 0xFFu;

	// 	//l_v = inverse(l_bp_mat4) * l_v;
	// 	//l_v = l_bp_mat4 * t2mat4(ssboat_t[l_0_0]) * r2mat4(ssboar_r[l_0_0]) * s2mat4(ssboas_s[l_0_0]) * inverse(l_bp_mat4) * l_v;
	// 	//l_v = inverse(l_bp_mat4 * s2mat4(ssboas_s[l_0_0]) * r2mat4(ssboar_r[l_0_0]) * t2mat4(ssboat_t[l_0_0])) * l_bp_mat4 * l_v;
	// 	l_v = l_bp_mat4 * s2mat4(ssboas_s[l_0_0]) * r2mat4(ssboar_r[l_0_0]) * t2mat4(ssboat_t[l_0_0]) * inverse(l_bp_mat4) * l_v;
	// 	//l_v = l_bp_mat4 * s2mat4(ssboas_s[l_0_0]) * t2mat4(ssboat_t[l_0_0]) * inverse(l_bp_mat4) * l_v;
	// 	//l_v = inverse(l_bp_mat4) * t2mat4(ssboat_t[l_0_0]) * r2mat4(ssboar_r[l_0_0]) * s2mat4(ssboas_s[l_0_0]) * l_bp_mat4 * l_v;
	// 	//l_v = l_bp_mat4 * l_v;
	// }
	// //weight 1
	// //l_v *= float((a_c1j1 >> ?) & 0xFFu);

	// mat4 l_m = mat4(1);

//	//t. s0-test
//	if ((floatBitsToUint(uboa.pa[51].s.w) & 0xFFFFu) == 284 && ((floatBitsToUint(uboa.pa[51].s.w) >> (8+8)) & 0xFFFFu) == 292)
//	{
//		//l_v *= 0;
//	}
//	//52*4==208
//	//need 208 < 291
//	//291 -> 291-52*2+1 -> 188
//	if (((floatBitsToUint(uboa.pa[291 / 4].t.w) >> 291 % 4 * 8) & 0xFFu) == 0)
//	{
//		l_v *= 0;
//	}
//	//t. e0-test
//	uint t_l_j = 40;
//	for (uint l_0 = floatBitsToUint(uboa.pa[t_l_j].s.w) & 0xFFFFu; l_0 < ((floatBitsToUint(uboa.pa[t_l_j].s.w) >> (8+8)) & 0xFFFFu); ++l_0)
//	{
//		uint t_l_0_0 = (floatBitsToUint(uboa.pa[l_0 / 4].t.w) >> l_0 % 4 * 8) & 0xFFu;
//		if (t_l_0_0 == 255)
//			l_v *= 0;
//	}
	uint l_b = floatBitsToUint(uboa.pa[l_j].s.w);
	uint l_be = (l_b >> (8+8)) & 0xFFFFu;
	if (l_be != 0)
	{
		l_v = ubob.pb[l_j].bindpose * t2mat4(uboa.pa[l_j].t.xyz) * r2mat4(uboa.pa[l_j].r) * s2mat4(uboa.pa[l_j].s.xyz) * ubob.pb[l_j].i_bindpose * l_v;
		uint l_bs = l_b & 0xFFFFu;
		for (uint l_0 = l_bs; l_0 < l_be; ++l_0)
		{
			uint l_0_0 = (floatBitsToUint(uboa.pa[l_0 / 4].t.w) >> l_0 % 4 * 8) & 0xFFu;
			// l_m = ubob.bindpose[l_0_0] * s2mat4(ubob.s[l_0_0].xyz) * r2mat4(ubob.r[l_0_0]) * t2mat4(ubob.t[l_0_0].xyz) * ubob.i_bindpose[l_0_0] * l_m;
			// l_m = ubob.i_bindpose[l_0_0] * s2mat4(ubob.s[l_0_0].xyz) * r2mat4(ubob.r[l_0_0]) * t2mat4(ubob.t[l_0_0].xyz) * ubob.bindpose[l_0_0] * l_m;
			// l_v = l_m * l_v;
			// l_v = inverse(l_m) * l_v;
			// l_v = ubob.bindpose[l_0_0] * ubob.i_bindpose[l_0_0] * l_v;
			// l_v = ubob.i_bindpose[l_0_0] * s2mat4(ubob.s[l_0_0].xyz) * r2mat4(ubob.r[l_0_0]) * t2mat4(ubob.t[l_0_0].xyz) * ubob.bindpose[l_0_0] * l_v;
			// l_v = inverse(ubob.bindpose[l_0_0] * s2mat4(ubob.s[l_0_0].xyz) * r2mat4(ubob.r[l_0_0]) * t2mat4(ubob.t[l_0_0].xyz)) * ubob.bindpose[l_0_0] * l_v;

			l_v = ubob.pb[l_0_0].bindpose * t2mat4(uboa.pa[l_0_0].t.xyz) * r2mat4(uboa.pa[l_0_0].r) * s2mat4(uboa.pa[l_0_0].s.xyz) * ubob.pb[l_0_0].i_bindpose * l_v;
			//if (l_0_0 > 0)
			//if (l_0_0 != 51)
			//	l_v *= 0;
			//l_v = ubob.pb[l_0_0].bindpose * ubob.pb[l_0_0].i_bindpose * l_v;
		}
	}
	l_v = ubob.pb[0].bindpose * t2mat4(uboa.pa[0].t.xyz) * r2mat4(uboa.pa[0].r) * s2mat4(uboa.pa[0].s.xyz) * ubob.pb[0].i_bindpose * l_v;

	gl_Position = ubos.p * ubos.v * l_v;
	//gl_Position = ubos.p * ubos.v * (l_v + vec4(0, 0, -3, 0));
	// gl_Position = ubos.p * ubos.v * uboa.m * l_v;

	f_c = a_c1j1 & 0xFFu;
	//use f_c
	// #ifdef NALI_TEXTURE
	// 	f_t = (a_c1j1 >> 16) & 0xFFFFu;
	// #endif
}
