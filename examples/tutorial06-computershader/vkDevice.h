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



/// <summary>
/// 
/// </summary>
struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsAndComputeFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsAndComputeFamily.has_value() && presentFamily.has_value();
    }
};


/// <summary>
/// 
/// </summary>
/// <param name="contextref"></param>
/// <param name="typeFilter"></param>
/// <param name="properties"></param>
/// <returns></returns>
uint32_t findMemoryType(vkContext& contextref, uint32_t typeFilter, VkMemoryPropertyFlags properties);


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
