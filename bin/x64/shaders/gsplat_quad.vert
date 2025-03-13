#version 450

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec4 obb;

layout(location = 0) out vec3 out_scale_rot;
layout(location = 1) out vec4 out_color;

void main() {
    gl_Position = vec4(inPosition.xyz, 1.f);
    out_color = inColor;
    out_scale_rot = obb.xyz;
}
