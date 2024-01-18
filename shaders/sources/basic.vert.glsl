
// simple exemple of vertex shader (GLSL/vulkan)

#version 450

layout(location = 0) in vec3 inPosition;

layout(location = 0) out vec3 outColor;

void main() {
	gl_Position = vec4(inPosition, 1.0);
	outColor = inPosition;
}
