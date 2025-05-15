#version 450

#define NALI_COLOR_SIZE 8

#ifdef NALI_TEXTURE
	layout(location = 0) in float f_t;
	layout(set = 0, binding = 2) uniform sampler2D ubo_s;
#endif

layout(location = 0) in flat uint f_c;

layout(std140, set = 0, binding = 2) uniform UBOC
{
	vec4 c[NALI_COLOR_SIZE];
} uboc;

layout(location = 0) out vec4 o_c;

void main()
{
	#ifdef NALI_TEXTURE
		o_c = texture(ubo_s, f_t);
	#else
		o_c = uboc.c[f_c];
	#endif
}