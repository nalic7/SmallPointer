#version 450

layout(location = 0) in vec2 a_v;
layout(location = 1) in vec2 a_t;
//layout(location = 1) in ivec2 a_t;
//layout(location = 1) in vec3 a_c;

layout(set = 0, binding = 0) uniform UBO
{
	mat4 m;
	mat4 v;
	mat4 p;
} ubo;

//layout(location = 0) out vec3 f_c;
layout(location = 0) out vec2 f_t;
//layout(location = 0) out ivec2 f_t;

void main()
{
	gl_Position = ubo.p * ubo.v * ubo.m * vec4(a_v, 0.0, 1.0);
	f_t = a_t;
	//f_color = a_c;
}