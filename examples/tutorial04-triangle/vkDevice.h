#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <set>

#include "vkLayer.h"

class vkContext;


uint32_t findMemoryType(vkContext& contextref, uint32_t typeFilter, VkMemoryPropertyFlags properties);


struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};


/// <summary>
/// 
/// </summary>
/// <param name="device"></param>
/// <returns></returns>
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice pphysicalDev, VkSurfaceKHR psurface);


/// <summary>
/// 
/// </summary>
/// <param name="pinst"></param>
void pickPhysicalDevice(vkContext& contextref);


/// <summary>
/// 
/// </summary>
void createLogicalDevice(vkContext& contextref);


struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};


SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice pphysicalDev, VkSurfaceKHR psurface);


void createBuffer(vkContext& contextref, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

VkImageView createImageView(vkContext& contextref, VkImage image, VkFormat format);
