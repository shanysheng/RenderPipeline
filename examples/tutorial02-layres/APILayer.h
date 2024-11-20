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

/// <summary>
/// 
/// </summary>
/// <param name="instance"></param>
/// <param name="pCreateInfo"></param>
/// <param name="pAllocator"></param>
/// <param name="pDebugMessenger"></param>
/// <returns></returns>
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, 
                                        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
                                        const VkAllocationCallbacks* pAllocator, 
                                        VkDebugUtilsMessengerEXT* pDebugMessenger);

/// <summary>
/// 
/// </summary>
/// <param name="instance"></param>
/// <param name="debugMessenger"></param>
/// <param name="pAllocator"></param>
void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);


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


void setupDebugMessenger(VkInstance pinst);
void cleanupDebugMessenger(VkInstance pinst);
