#version 450

layout(location = 0) in vec2 a_v;

layout(set = 0, binding = 0) uniform UBO
{
	mat4 m;
	mat4 v;
	mat4 p;
} ubo;

void main()
{
	gl_Position = ubo.p * ubo.v * ubo.m * vec4(a_v, 0.0, 1.0);
}