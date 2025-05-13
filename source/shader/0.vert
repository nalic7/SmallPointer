#version 450

#define NALI_JOINT_SIZE 22
//#define NALI_BONE_SIZE 43

layout(location = 0) in vec3 a_v;
//use j1c1->j1t1u1v1
layout(location = 1) in uint a_j1c1;

layout(set = 0, binding = 0) uniform UBO
{
	mat4 mvp;
} ubo;

layout(std430, set = 0, binding = 1) readonly buffer SSBOB
{
	vec4 ssbob_s[NALI_JOINT_SIZE];//z4 b
	vec4 ssbob_r[NALI_JOINT_SIZE];
	vec4 ssbob_t[NALI_JOINT_SIZE];//z4 start end
};

layout(std430, set = 0, binding = 2) readonly buffer SSBOAS
{
	//vec4
	vec3 ssboas_s[NALI_JOINT_SIZE];
};
layout(std430, set = 0, binding = 3) readonly buffer SSBOAR
{
	vec4 ssboar_r[NALI_JOINT_SIZE];
};
layout(std430, set = 0, binding = 4) readonly buffer SSBOAT
{
	//vec4
	vec3 ssboat_t[NALI_JOINT_SIZE];
};

layout(location = 0) out uint f_c;

void main()
{
	vec4 l_v = vec4(a_v, 1);
	uint l_j = a_j1c1 & 0xFF;

	//check bone step
	for (uint l_0 = floatBitsToUint(ssbob_t[l_j].z) & 0xFF; l_0 < l_j + ((floatBitsToUint(ssbob_t[l_j].z) >> 8) & 0xFF); ++l_0)
	{
		uint l_0_0 = (floatBitsToUint(ssbob_s[l_0 / 4].z) >> l_0 % 4 * 8) & 0xFF;

		//l_v *= vec4(ssbob_s[l_0_0].xyz, 1);
		//l_v *= ssbob_r[l_0_0];
		//l_v *= vec4(ssbob_t[l_0_0].xyz, 1);

		//l_v *= vec4(ssboas_s[l_0_0], 1);
		//l_v *= ssboar_r[l_0_0];
		//l_v *= vec4(ssboat_t[l_0_0], 1);

		//l_v /= vec4(ssbob_t[l_0_0].xyz, 1);
		//l_v /= ssbob_r[l_0_0];
		//l_v /= vec4(ssbob_s[l_0_0].xyz, 1);
	}
	//weight 1
	//l_v *= float((a_j1c1 >> ?) & 0xFF);

	gl_Position = ubo.mvp * l_v;

	f_c = (a_j1c1 >> 8) & 0xFF;
}