#pragma once


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

class vkContext;


const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};



class kSwapchain
{
public:
	kSwapchain();
	virtual ~kSwapchain();

	void cleanupSwapChain(vkContext& contextref);
	void recreateSwapChain(vkContext& contextref);

	void createSwapChain(vkContext& contextref);
	void createImageViews(vkContext& contextref);
	void createFramebuffers(vkContext& contextref);

	VkSwapchainKHR getSwapchain() { return swapChain; }
	VkFramebuffer getFramebuffer(int index) { return swapChainFramebuffers[index]; }
	VkExtent2D getSwapExtent() { return swapChainExtent; }
	VkFormat getSwapchainImageFormat() { return swapChainImageFormat; }


protected:

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(GLFWwindow* pwindow, const VkSurfaceCapabilitiesKHR& capabilities);

protected:
	VkSwapchainKHR				swapChain;
	std::vector<VkImage>		swapChainImages;
	VkFormat					swapChainImageFormat;
	VkExtent2D					swapChainExtent;
	std::vector<VkImageView>	swapChainImageViews;
	std::vector<VkFramebuffer>	swapChainFramebuffers;
};

