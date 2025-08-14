#version 420

#define NALI_COLOR_BL 8

#ifdef NALI_TEXTURE
	#define NALI_TEXTURE_BL 1
	// layout(location = 1) in flat uint f_t;
	layout(set = 0, binding = 4) uniform sampler2D ubo_s[NALI_TEXTURE_BL];
	//use c as uv
	// layout(std140, set = 0, binding = 5) uniform UBOT
	// {
	// 	vec4 uv[NALI_TEXTURE_BL];
	// } uboc;
#endif

layout(location = 0) in flat uint f_c;

layout(std140, set = 0, binding = 3) uniform UBOC
{
	vec4 c[NALI_COLOR_BL];
} uboc;

layout(std140, set = 0, binding = 4) uniform UBOSC
{
	vec4 c;
} ubosc;

layout(location = 0) out vec4 o_c;

void main()
{
	// 	//use f_c
	// #ifdef NALI_TEXTURE
	// 	// if (!f_t)
	// 	// 	o_c = texture(ubo_s[f_c], uv[f_t].xy);
	// 	// else
	// #endif
	o_c = uboc.c[f_c] * ubosc.c;
}
