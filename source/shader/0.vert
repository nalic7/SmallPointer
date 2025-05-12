#version 450

#define NALI_BONE_SIZE 43
#define NALI_JOINT_SIZE 22

layout(location = 0) in vec3 a_v;
//use j1w1c1t1 t1->uv1 4+4 bit 15|15 1 c1->t1
#ifdef NALI_TEXTURE
	layout(location = 1) in float a_t;
	layout(location = 2) in uint a_j1w1;
#else
	layout(location = 1) in uint a_j1w1c1;
#endif

layout(set = 0, binding = 0) uniform UBO
{
	mat4 mvp;
} ubo;

layout(std430, set = 0, binding = 1) readonly buffer SSBOB
{
	uint ssbob_bs[NALI_JOINT_SIZE];
	uint ssbob_b[NALI_BONE_SIZE];
	uint ssbob_be[NALI_JOINT_SIZE];

	vec3 ssbob_s[NALI_JOINT_SIZE];
	vec4 ssbob_r[NALI_JOINT_SIZE];
	vec3 ssbob_t[NALI_JOINT_SIZE];
};

layout(std430, set = 0, binding = 2) readonly buffer SSBOAS
{
	vec3 ssboas_s[NALI_JOINT_SIZE];
};
layout(std430, set = 0, binding = 3) readonly buffer SSBOAR
{
	vec4 ssboar_r[NALI_JOINT_SIZE];
};
layout(std430, set = 0, binding = 4) readonly buffer SSBOAT
{
	vec3 ssboat_t[NALI_JOINT_SIZE];
};

#ifdef NALI_TEXTURE
	layout(location = 0) out float f_t;
#else
	layout(location = 0) out uint f_c;
#endif

void main()
{
	vec4 l_v = vec4(a_v, 1);
	uint l_j = (a_j1w1c1 >> 32) & 0xFF;
	for (uint i = ssbob_bs[l_j]; i < l_j + ssbob_be[l_j]; ++i)
	{
		l_v *= vec4(ssbob_s[ssbob_b[i]], 1);
		l_v *= ssbob_r[ssbob_b[i]];
		l_v *= vec4(ssbob_t[ssbob_b[i]], 1);

		l_v *= vec4(ssboas_s[ssbob_b[i]], 1);
		l_v *= ssboar_r[ssbob_b[i]];
		l_v *= vec4(ssboat_t[ssbob_b[i]], 1);

		l_v /= vec4(ssbob_t[ssbob_b[i]], 1);
		l_v /= ssbob_r[ssbob_b[i]];
		l_v /= vec4(ssbob_s[ssbob_b[i]], 1);
	}
	l_v *= float((a_j1w1c1 >> 16) & 0xFF);

	//gl_Position = ubo.mvp * l_v;
	gl_Position = ubo.mvp * vec4(a_v, 1);

	#ifdef NALI_TEXTURE
		f_t = a_t;
	#else
		f_c = (a_j1w1c1 >> 8) & 0xFF;
	#endif
}