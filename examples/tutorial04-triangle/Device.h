#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>

#include "APILayer.h"

/// <summary>
/// 
/// </summary>
/// <param name="pinst"></param>
void pickPhysicalDevice(VkInstance pinst);


/// <summary>
/// 
/// </summary>
void createLogicalDevice();
void cleanupLogicalDevice();

