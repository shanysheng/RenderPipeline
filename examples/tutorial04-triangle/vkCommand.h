#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

extern VkCommandPool commandPool;
extern VkCommandBuffer commandBuffer;


void createCommandPool(VkDevice plogicaldevice);
void createCommandBuffer(VkDevice plogicaldevice);