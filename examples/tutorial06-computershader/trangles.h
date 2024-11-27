#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include "vkVertexBuffer.h"

#include <vector>
#include <array>
#include <random>

const uint32_t PARTICLE_COUNT = 8192;


struct UniformBufferObject {
    float deltaTime = 1.0f;
};



