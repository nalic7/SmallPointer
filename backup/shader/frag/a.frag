#version 450

//layout(location = 0) in vec3 f_c;
layout(location = 0) in vec2 f_t;
//layout(location = 0) in ivec2 f_t;

//line
layout(set = 0, binding = 1) uniform sampler2D ubo_s;
//near
/*layout(set = 0, binding = 1, rgba8) uniform readonly image2D ubo_i;
layout(set = 0, binding = 2) uniform UBO
{
	vec2 wh;
} ubo;*/

layout(location = 0) out vec4 o_c;

void main()
{
	//o_c = vec4(f_c, 1.0);
	o_c = texture(ubo_s, f_t);
	//o_c = imageLoad(ubo_i, ivec2(f_t * ubo.wh));
	//o_c = imageLoad(ubo_i, f_t);
	//o_c = imageLoad(ubo_i, ivec2(vec2(1.0F, 1.0F) * 512));
}