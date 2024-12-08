#pragma once


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

class kContext;




class kSwapchain
{
public:
	kSwapchain();
	virtual ~kSwapchain();

	void createSwapchain(kContext& contextref, VkExtent2D extent);
	void createFramebuffers(kContext& contextref, VkRenderPass renderpass);

	void cleanupSwapChain(kContext& contextref);
	void recreateSwapChain(kContext& contextref, VkExtent2D extent, VkRenderPass renderpass);

	VkSwapchainKHR getSwapchain() { return swapChain; }
	VkFramebuffer getFramebuffer(int index) { return swapChainFramebuffers[index]; }
	VkExtent2D getSwapExtent() { return swapChainExtent; }
	VkFormat getSwapchainImageFormat() { return swapChainImageFormat; }
	VkFormat getDepthFormat() { return depthFormat; }

protected:
	void createSwapchainImageViews(kContext& contextref);
	void createDepthResources(kContext& contextref);

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


	VkImage						depthImage;
	VkFormat					depthFormat;
	VkDeviceMemory				depthImageMemory;
	VkImageView					depthImageView;
};

