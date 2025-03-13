#version 450

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec4 param; // xy is screen size, y is particle count
} ubo;

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec4 obb;

layout(location = 0) out vec4 out_Color;

void main() {
    gl_PointSize = 2.0;
    gl_Position = inPosition;
    out_Color = inColor;
}
