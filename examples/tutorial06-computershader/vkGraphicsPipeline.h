#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <fstream>
#include <vector>
#include <cstring>

class vkContext;

void createGraphicsPipeline(vkContext& contextref);
void createComputePipeline(vkContext& contextref);

void createRenderPass(vkContext& contextref);



