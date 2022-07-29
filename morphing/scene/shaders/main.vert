#version 330

#extension GL_ARB_explicit_uniform_location : enable

layout (location = 0) in vec2 pos_a;
layout (location = 1) in vec2 pos_b;
layout (location = 2) uniform float t;
layout (location = 3) uniform mat4 proj;

void main() {
    gl_Position = proj * vec4 ( t * pos_a + ( 1 - t ) * pos_b , 0.0, 1.0 );
}
