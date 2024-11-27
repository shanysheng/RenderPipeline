#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class vkContext;

VkImageView createImageView(vkContext& contextref, VkImage image, VkFormat format);

