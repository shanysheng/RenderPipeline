#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <fstream>
#include <vector>
#include <cstring>

#include "vkContext.h"

void createRenderPass(vkContext& contextref);

void createGraphicsPipeline(vkContext& contextref);

void recordCommandBuffer(vkContext& contextref, uint32_t imageIndex);


VkShaderModule createShaderModule(VkDevice plogicaldevice, const std::vector<char>& code);
