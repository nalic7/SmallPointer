#version 450

layout(set = 0, binding = 1) uniform UBO
{
	vec4 c;
} ubo;

layout(location = 0) out vec4 o_c;

void main()
{
	o_c = ubo.c;
}