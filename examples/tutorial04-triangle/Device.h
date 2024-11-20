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

#include "APILayer.h"

extern VkPhysicalDevice physicalDevice;
extern VkDevice logicaldevice;
extern VkQueue graphicsQueue;


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
/// <param name="pinst"></param>
void pickPhysicalDevice(VkInstance pinst);

/// <summary>
/// 
/// </summary>
/// <param name="device"></param>
/// <returns></returns>
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice pphysicalDev);


/// <summary>
/// 
/// </summary>
void createLogicalDevice();
void cleanupLogicalDevice();

