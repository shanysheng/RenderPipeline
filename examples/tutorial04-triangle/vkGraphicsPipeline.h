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

void recordCommandBuffer(VkRenderPass prenderPass, VkPipeline pgraphicsPipeline, VkFramebuffer pFramebuffer, VkExtent2D renderExtent, VkCommandBuffer commandBuffer, uint32_t imageIndex);


VkShaderModule createShaderModule(VkDevice plogicaldevice, const std::vector<char>& code);
