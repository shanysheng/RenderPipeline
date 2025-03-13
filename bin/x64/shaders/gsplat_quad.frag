#version 450

layout(location = 0) in vec4 color;
layout(location = 1) in vec2 position;

layout(location = 0) out vec4 outColor;

void main() {

    float gaussian_alpha = exp(-0.5f * dot(position, position));
    float alpha = color.a * gaussian_alpha;

    // premultiplied alpha
    outColor = vec4(color.rgb * alpha, alpha);
}
