#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include <vector>
#include <iostream>


const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class vkContext;


/// <summary>
/// 
/// </summary>
/// <param name="createInfo"></param>
void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);


/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool checkValidationLayerSupport();

/// <summary>
/// 
/// </summary>
/// <param name="pinst"></param>
void setupDebugMessenger(VkInstance pinst);
void cleanupDebugMessenger(VkInstance pinst);
