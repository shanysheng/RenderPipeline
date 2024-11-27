#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

class vkContext;


void createImage(vkContext& contextref, uint32_t width, uint32_t height, VkFormat format,
                VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
                VkImage& image, VkDeviceMemory& imageMemory);

void createTextureImage(vkContext& contextref, const std::string& image_path);

void createTextureImageView(vkContext& contextref);

void createTextureSampler(vkContext& contextref);

VkImageView createImageView(vkContext& contextref, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
