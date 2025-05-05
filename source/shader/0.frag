#version 450

#define NALI_COLOR_SIZE 8

#ifdef NALI_TEXTURE
	layout(location = 0) in float f_t;
	layout(set = 0, binding = 5) uniform sampler2D ubo_s;
#else
	layout(location = 0) in flat uint f_c;
	layout(std430, set = 0, binding = 5) readonly buffer SSBOC
	{
		vec4 ssboc_c[NALI_COLOR_SIZE];
	};
#endif

layout(location = 0) out vec4 o_c;

void main()
{
	#ifdef NALI_TEXTURE
		o_c = texture(ubo_s, f_t);
	#else
		o_c = ssboc_c[f_c];
	#endif
}