#version 450

#define NALI_BONE_SIZE 22

layout(location = 0) in vec3 a_v;
//use j1c1->j1t1u1v1
layout(location = 1) in uint a_j1c1;

layout(std140, set = 0, binding = 0) uniform UBOS
{
	mat4 v;
	mat4 p;
} ubos;

layout(std140, set = 0, binding = 1) uniform UBOB
{
	mat4 i_bindpose[NALI_BONE_SIZE];
	mat4 bindpose[NALI_BONE_SIZE];
	vec4 s[NALI_BONE_SIZE];//w1_start w2_end
	vec4 r[NALI_BONE_SIZE];
	vec4 t[NALI_BONE_SIZE];//w1-4_b
} ubob;

/*layout(std430, set = 0, binding = 2) readonly buffer SSBOAS
{
	//vec4
	vec3 ssboas_s[NALI_BONE_SIZE];
};*/

layout(location = 0) out uint f_c;

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
		1.0 - 2.0 * (yy + zz),	2.0 * (xy - wz),		2.0 * (xz + wy),		0.0,

		2.0 * (xy + wz),		1.0 - 2.0 * (xx + zz),	2.0 * (yz - wx),		0.0,

		2.0 * (xz - wy),		2.0 * (yz + wx),		1.0 - 2.0 * (xx + yy),	0.0,

		0.0,					0.0,					0.0,					1.0
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
	uint l_j = a_j1c1 & 0xFFu;

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
	// //l_v *= float((a_j1c1 >> ?) & 0xFFu);

	// mat4 l_m = mat4(1);

	for (uint l_0 = floatBitsToUint(ubob.s[l_j].w) & 0xFFu; l_0 < ((floatBitsToUint(ubob.s[l_j].w) >> 8) & 0xFFu); ++l_0)
	{
		uint l_0_0 = (floatBitsToUint(ubob.t[l_0 / 4].w) >> l_0 % 4 * 8) & 0xFFu;
		// l_m = ubob.bindpose[l_0_0] * s2mat4(ubob.s[l_0_0].xyz) * r2mat4(ubob.r[l_0_0]) * t2mat4(ubob.t[l_0_0].xyz) * ubob.i_bindpose[l_0_0] * l_m;
		// l_m = ubob.i_bindpose[l_0_0] * s2mat4(ubob.s[l_0_0].xyz) * r2mat4(ubob.r[l_0_0]) * t2mat4(ubob.t[l_0_0].xyz) * ubob.bindpose[l_0_0] * l_m;
		// l_v = l_m * l_v;
		// l_v = inverse(l_m) * l_v;
		// l_v = ubob.bindpose[l_0_0] * ubob.i_bindpose[l_0_0] * l_v;
		l_v = ubob.bindpose[l_0_0] * t2mat4(ubob.t[l_0_0].xyz) * r2mat4(ubob.r[l_0_0]) * s2mat4(ubob.s[l_0_0].xyz) * ubob.i_bindpose[l_0_0] * l_v;
		// l_v = ubob.i_bindpose[l_0_0] * s2mat4(ubob.s[l_0_0].xyz) * r2mat4(ubob.r[l_0_0]) * t2mat4(ubob.t[l_0_0].xyz) * ubob.bindpose[l_0_0] * l_v;
		// l_v = inverse(ubob.bindpose[l_0_0] * s2mat4(ubob.s[l_0_0].xyz) * r2mat4(ubob.r[l_0_0]) * t2mat4(ubob.t[l_0_0].xyz)) * ubob.bindpose[l_0_0] * l_v;
	}

	gl_Position = ubos.p * ubos.v * l_v;

	f_c = (a_j1c1 >> 8) & 0xFFu;
}