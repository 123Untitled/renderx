#version 450

// -- S K Y B O X  F R A G M E N T  S H A D E R -------------------------------

/* image */
layout(set = 0, binding = 0) uniform texture2D tex;


// -- input from vertex shader ------------------------------------------------

layout(location = 0) in vec3 in_texcoord;


// -- output to framebuffer ---------------------------------------------------

layout(location = 0) out vec4 out_color;

void main(void) {

}
