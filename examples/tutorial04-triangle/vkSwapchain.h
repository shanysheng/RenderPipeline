#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>


#include "vkContext.h"

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};



void createImageViews(vkContext& contextref);
void createFramebuffers(vkContext& contextref);
void createSwapChain(vkContext& contextref);

VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
VkExtent2D chooseSwapExtent(GLFWwindow* pwindow, const VkSurfaceCapabilitiesKHR& capabilities);
SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice pphysicalDev, VkSurfaceKHR psurface);


