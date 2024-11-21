#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <fstream>
#include <vector>
#include <cstring>


extern VkRenderPass renderPass;
extern VkPipelineLayout pipelineLayout;
extern VkPipeline graphicsPipeline;


void createRenderPass(VkDevice plogicaldevice, VkFormat swapimageformat);

void createGraphicsPipeline(VkDevice plogicaldevice);

VkShaderModule createShaderModule(VkDevice plogicaldevice, const std::vector<char>& code);
