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

	void createSwapchain(kContext& contextref, VkExtent2D extent, VkRenderPass renderpass);

	void cleanupSwapChain(kContext& contextref);
	void recreateSwapChain(kContext& contextref, VkExtent2D extent, VkRenderPass renderpass);

	VkSwapchainKHR getSwapchain() { return swapChain; }
	VkFramebuffer getFramebuffer(int index) { return swapChainFramebuffers[index]; }


protected:
	void createFramebuffers(kContext& contextref, VkRenderPass renderpass);
	void createSwapchainImageViews(kContext& contextref);
	void createDepthResources(kContext& contextref);


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

